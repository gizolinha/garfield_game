#include <stdio.h>
#include <stdlib.h> 
#include <allegro5/allegro.h> 
#include "player.h"
#include "game_def.h"
#include "plataform.h"
#include "resources.h"


/*inicializa o player */
player* player_create() {
    //aloca memória para a estrutura player
    player* p = (player*)malloc(sizeof(player));
    if (!p) {
        perror("ERRO: Falha ao alocar memória para o Player.\n");
        return NULL;
    }

    p->x = LARGURA_TELA / 3.0f; //posicao inicial
    p->y = ALTURA_TELA - 300.0f; 
    p->vel_x = 0.0f;
    p->vel_y = 0.0f;
    p->state = PARADO;
    p->on_ground = true;
    p->current_frame = 0;
    p->frame_timer = 0;
    p->anim_direct = 1;
    p->direct = DIREITA;

    /* dimensoes baseadas no primeiro sprite */
    if (assets.player_parado[0]) {
        p->width = al_get_bitmap_width(assets.player_parado[0]) * ESCALA_PLAYER;
        p->height = al_get_bitmap_height(assets.player_parado[0]) *ESCALA_PLAYER;
    } else {
        /* caso nao carregue */
        perror("ERRO: Sprite principal do player não carregado!\n");
        p->width = 50; 
        p->height = 50;
    }

    return p;
}

/*desaloca memoria do player */
void player_destroy(player* p) {
    if (p) 
      free(p);
}

/* atualiza o player */
void player_update(player* p) {

    /* animação sprites player parado */
    if (p->state == PARADO) {
        p->frame_timer++;

        /* animacao ping pong */
        if (p->frame_timer >= FPS_PARADO) { 
            p->frame_timer = 0;
            p->current_frame += p->anim_direct;
            
            if (p->current_frame >= FRAMES_PARADO -1) {
                p->anim_direct = -1;
                p->current_frame = FRAMES_PARADO - 1;
            }
            else if (p->current_frame <= 0) {
                p->anim_direct = 1;
                p->current_frame = 0;
            }
        }
    }

    /* animacao de sprites player andando */
    if(p->state == ANDANDO) {
        p->frame_timer++;

        if(p->frame_timer >= FPS_ANDANDO) {
            p->frame_timer = 0;

            p->current_frame++;

            //se chegou ao ultimo frame, volta para o primeiro
            if(p->current_frame >= FRAMES_ANDANDO) {
                p->current_frame = 0;
            }
        }
    } 

    /* animacao de sprites player pulando */
    if(p->state == PULANDO) {
        p->frame_timer++;

        if(p->frame_timer >= FPS_PULANDO) {
            p->frame_timer = 0;
            p->current_frame++;

            /* se estiver no ultimo frame, fiz nele */
            if(p->current_frame >= FRAMES_PULANDO)
                p->current_frame = FRAMES_PULANDO - 1;
        }
    }

    /* animacao sprites player abaixado */
    if(p->state == ABAIXADO) {
        /* se estiver parado roda a animacao */
        if(p->vel_x == 0.0f) {
            p->frame_timer++;

            if(p->frame_timer >= FPS_ABAIXADO) {
                p->frame_timer = 0;
                p->current_frame++;

                if(p->current_frame >= FRAMES_ABAIXADO)
                    p->current_frame = 0;
    
            }
        }
        else 
            /* se agachar trava o frame*/
            p->current_frame = 0;
    }


    /* dash do player */

    /* diminui o cooldown do dash */
    if (p->dash_cooldown > 0) {
        p->dash_cooldown--;
    }
    /* estado do dash */
    if (p->state == DASH) {
        p->dash_timer--;
        
        /* vel-x constante */
        if(p->direct == DIREITA) p->vel_x = 12.0f;
        else p->vel_x = -12.0f;
        
        /* volta a vel normal quando acaba*/
        if (p->dash_timer <= 0) {
            p->state = PARADO; 
            p->vel_x = 0;
        }
        
        p->x += p->vel_x; 
        
        return; 
    }


    /* limites do mundo */
    /* nova posicao em x */
    float next_x = p->x + p->vel_x;

    /* limite maximo a esquerda na tela */
    float min_x = p->width /2.0f;

    if(next_x < min_x) {
        p->x = min_x;
        p->vel_x = 0.0f; //nao consegue mais andar se chegar no limite esquerdo

    }
    /* verifica o lado direito */
    else {
        /* pega o tamanho total da imagem do fundo */
        float map_width = 0.0f;
        if(assets.fundo_game)
            map_width = al_get_bitmap_width(assets.fundo_game);
        else 
            map_width = LARGURA_TELA;

        float max_x = map_width - p->width / 2.0f;


        if (next_x > max_x) {
            p->x = max_x;       
            p->vel_x = 0.0f; //nao consegue mais andar se chegar no limite direito
        }
        /* se nao estiver no limite continua andando*/
        else {
            p->x = next_x; 
        }

    }
    /* logica gravidade/pulo/queda */

    /* aplica gravidade se o player nao estiver no chao */
    if(p->on_ground == false) 
        p->vel_y += GRAVIDADE;

    /* limita a velocidade da queda */
    if(p->vel_y > MAX_VEL_QUEDA)
        p->vel_y = MAX_VEL_QUEDA;

    p->y += p->vel_y;

    /* logica de estados pulando */
    if(p->on_ground == false) {
        if(p->state != PULANDO) {
            p->state = PULANDO;
            p->current_frame = 0;
            p->frame_timer = 0;
        }
    }

    /* logica de colisao com plataformas */
    /* evita bugs com os sprites */
    
    /* se o player colidiu com alguma plataforma */
    plataform* colisao = plat_colisao(p->x, p->y, p->width, p->height, p->vel_y);

    /* se colidir*/
    if (colisao != NULL) {
        
        if (colisao->type == PLATAFORM_CAI) {
            colisao->pisada = true; // ativar queda
        }
       
        /* ajusta para ficar rente a plataforma (novo chao) */
        float new_ground_y = colisao->y - (p->height / 2.0f);
        p->y = new_ground_y;
        p->vel_y = 0.0f; 

        /* atualiza o estado do chao */
        if (p->on_ground == false) {
            p->on_ground = true;
            
            /* novo estado do player */
            if (p->vel_x != 0.0f) {
                p->state = ANDANDO;
            } else {
                p->state = PARADO;
            }
            p->current_frame = 0;
            p->frame_timer = 0;
        }
    
    } else {
        p->on_ground = false; //nao colidiu
    }
}

/* desenha o sprite do player */
void player_draw(player* p, float camera_offset_x) {
    if (!p) 
        return; 
    
    ALLEGRO_BITMAP *current_sprite = NULL;
    float escala_extra = 1.0f;
    float ajuste_y = 0.0f;

    switch (p->state) {
        case PARADO:
            current_sprite = assets.player_parado[p->current_frame]; 
            break;
            
        case ANDANDO:
            current_sprite = assets.player_andando[p->current_frame];
            break;
       
        case PULANDO:
            int frame_to_draw = p->current_frame;
            if (frame_to_draw >= FRAMES_PULANDO) {
                frame_to_draw = FRAMES_PULANDO - 1;
            }
            current_sprite = assets.player_pulando[frame_to_draw];
            break;

        case ABAIXADO:
            current_sprite = assets.player_abaixado[p->current_frame];
            /* sprite fica menor */
            escala_extra = 0.7f;
            break;
            
        case DASH:
            current_sprite = assets.player_dash;
            escala_extra = 2.7f;
            break;
        default:
            current_sprite = assets.player_parado[0];
            break;
    }


    /*  inverte a direcao dos sprite e animacao */
    int inver = 0;
    /* se o player estiver pra esquerda, inverte */
    if(p->direct == ESQUERDA) 
        inver = ALLEGRO_FLIP_HORIZONTAL;

    if (current_sprite) {
        
        float sprite_w_og = al_get_bitmap_width(current_sprite);
        float sprite_h_og = al_get_bitmap_height(current_sprite);

        /* novo tamanho do personagem */
        float draw_w = sprite_w_og * ESCALA_PLAYER * escala_extra;
        float draw_h = sprite_h_og * ESCALA_PLAYER * escala_extra;

        /* nova hitbox */
        float hit = p->height;

        /* calcula novo x para centralizar o sprite */
        float draw_x = (p->x + camera_offset_x) - (draw_w / 2.0f);
        
        /* calcula novo y*/
        float draw_y = (p->y + (hit / 2.0f)) - draw_h + ajuste_y;

        al_draw_scaled_bitmap(current_sprite, 0, 0, sprite_w_og, sprite_h_og, draw_x, draw_y, draw_w, draw_h, inver);
    }
}

/* movimentacao de desvio do player */
void player_dash(player* p) {
    /* dash se nao estiver em dash ou cd*/
    if (p->state != DASH && p->dash_cooldown <= 0) {
        p->state = DASH;
        p->dash_timer = 20;      
        p->dash_cooldown = 60;   
        
        /* aumenta a velocidade para um direcao especifica */
        if (p->direct == DIREITA) 
            p->vel_x = 12.0f; 
        else 
            p->vel_x = -12.0f;
            
        p->vel_y = 0; // zera a gravidade
    }

}

/* funcoes de input teclado */
void player_jump(player* p) { 
    /* so pula se estiver no chao */
    if(p->on_ground == true) {
        p->vel_y = VELOCIDADE_PULO; // para cima
        p->on_ground = false; // sai do chao
        p->state = PULANDO; //sprites
    }
}

void player_right(player* p) { 
    /* velocidade do player andando para direita*/
    p->direct = DIREITA;
    p->state = ANDANDO;
    p->vel_x = NORMAL_SPEED;
    
}
void player_left(player* p) { 
    /* velocidade do player andando para esquerda (negativa)*/
    p->direct = ESQUERDA;
    p->state = ANDANDO;
    p->vel_x = -NORMAL_SPEED;

}

void player_stop(player* p){
    /* zera a valocidade quando solta a tecla*/
    p->vel_x = 0.0f;
    p->state = PARADO;
    p->current_frame = 0;
}

void player_down_start(player* p) {
    if(p->state != PULANDO)
        p->state = ABAIXADO;
}

void player_down_stop(player* p) {
    if(p->state == ABAIXADO)
        p->state = PARADO;
}

