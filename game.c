#include <stdio.h>
#include "game.h"
#include "game_def.h"
#include "player.h"
#include "resources.h"
#include "obstacle.h"
#include "plataform.h"
#include "itens.h"

/* nao criamos o player ainda */
static player* p = NULL;
static int vidas = 3;

/* o jogo sempre comeca no menu */
gamestate current_state = MENU;

/* botao do menu comeca no iniciar */
menu current_select = OPCAO_INICIAR;

/* variavel para rolling background */
float camera_offset_x = 0.0f; 

/* inicializa os recursos */
bool game_init() {
    p = player_create();
    if (!p) {
        return false;
    }
    /* inicializa as plataformas */
    plataform_init();
    /*inicializa obstaculos */
    obstacles_init();
    /* iniciliza os itens */
    item_init();

    /* toca musica do menu*/
    if(assets.musica_menu)
        al_set_audio_stream_playing(assets.musica_menu, true);

    return true;
}

/* destroi recursos alocados */
void game_end() {
    if (p) { 
        player_destroy(p);
        p = NULL; 
    }
}

/* atualiza a logica do jogo */
gamestate game_update() {
    /* maquina de estados */
    switch(current_state) {
    case MENU:         
        break;

    case JOGANDO:
        /* atualiza o player */
        player_update(p);
        /* atualiza obstaculos*/
        obstacles_update();
        /* para queda da plataforma */
        plataform_update();

        /* itens */
        int item_hit = item_colisao(p); 
        
        if (item_hit == LASANHA_VITORIA) {
            current_state = VITORIA;
            /* para de tocar a musica do jogo */
            if(assets.musica_jogo) 
                al_set_audio_stream_playing(assets.musica_jogo, false);

        }
        else if (item_hit == URSO_VIDA) {
            vidas += 2;
            if (vidas > 5) vidas = 5; //max de vidas

        }

        /* colisao com obstaculos */
        if (obst_colisao(p)) {
            vidas--; 

            if(vidas <= 0) {
                current_state = FIM_DE_JOGO;

                /* troca as musicas */
                if(assets.musica_menu) 
                    al_set_audio_stream_playing(assets.musica_menu, false); 
                    
                if(assets.musica_jogo) {
                    al_rewind_audio_stream(assets.musica_jogo); 
                    al_set_audio_stream_playing(assets.musica_jogo, false);  
                }
            } 
            /* reinicia a fase*/
            else {
                player_destroy(p);      
                p = player_create();    
                camera_offset_x = 0.0f; 
                   
            }
        }
        /* queda das plataformas */
        if (p->y > QUEDA_MORTE) {
            vidas--; 

            if(vidas <= 0) {
                current_state = FIM_DE_JOGO;
                /* troca as musicas */
                if(assets.musica_menu) 
                    al_set_audio_stream_playing(assets.musica_menu, false); 
                    
                if(assets.musica_jogo) {
                    al_rewind_audio_stream(assets.musica_jogo); 
                    al_set_audio_stream_playing(assets.musica_jogo, false);  
                }
            } 
            else {
                player_destroy(p);
                p = player_create(); 
                camera_offset_x = 0.0f;
                
            }
        }

        /* deslocamento da camera */
        camera_offset_x = LARGURA_TELA / 2.0f - p->x;

        /* limites da camera para impedir de sair do mapa*/
        /* limite para nao sair do mapa na esquerda */
        if (camera_offset_x > 0) {
            camera_offset_x = 0; 
        }

        float map_width = al_get_bitmap_width(assets.fundo_game);
        /* limite da camera a esquerda */
        float max_offset = LARGURA_TELA - map_width; 
        
        /* limite para direita */
        if (camera_offset_x < max_offset) {
            camera_offset_x = max_offset;
        }
        break;
            
    case FIM_DE_JOGO:
        break;

    case VITORIA:
        break;
            
    case PAUSE:
        break;

    case SAIR:
        break;
    }
    return current_state;
}

/* desenha os elementos na tela */
void game_draw() {
    switch (current_state) {
    case MENU:
         /* imagem de fundo do menu*/
        if(assets.fundo_menu) 
            /* desenha a imagem */
            al_draw_bitmap(assets.fundo_menu, 0, 0, 0);

        /* visualizacao dos botoes + navegacao */
        if(assets.bt_iniciar && assets.bt_sair) {
            /* cores de destaque */
            ALLEGRO_COLOR cor_select = al_map_rgb(255, 219, 187); 
            ALLEGRO_COLOR cor_not = al_map_rgb(255, 255, 255); 

            /* altura na tela*/
            float start_y = ALTURA_TELA / 3.0f - 50.0f; 
            float exit_y = start_y + 200.0f;

            /* centraliza iniciar */
            float w_iniciar = al_get_bitmap_width(assets.bt_iniciar);
            float center_x_ini = LARGURA_TELA / 2.0f - w_iniciar / 2.0f;

            /* botao inciar */
            al_draw_tinted_bitmap(assets.bt_iniciar, 
                                (current_select == OPCAO_INICIAR) ? cor_select : cor_not,
                                center_x_ini, start_y, 0);

            /*centraliza sair */  
            float w_sair = al_get_bitmap_width(assets.bt_sair);
            float center_x_sair = LARGURA_TELA / 2.03f - w_sair / 2.0f;           
            
            /* botao sair */
            al_draw_tinted_bitmap(assets.bt_sair, 
                                (current_select == OPCAO_SAIR) ? cor_select : cor_not,
                                center_x_sair, exit_y, 0);
        }

        break;
            
    case JOGANDO:
        /* desenha o cenario do fundo */
        if(assets.fundo_game) 
            al_draw_bitmap(assets.fundo_game, camera_offset_x, 0, 0);

        /* desenha os obstaculos */
        obstacles_draw(camera_offset_x);

        /* desenha o player */
        player_draw(p, camera_offset_x);

        /* desenha as plataformas */
        plataform_draw(camera_offset_x);

        /* desenha os itens */
        item_draw(camera_offset_x);

        /* desenho da vida do jogador */
        if(vidas > 0) {
            /* sprites de 0 a 4*/
            int i = vidas - 1;

            ALLEGRO_BITMAP* vida_atual = assets.sprites_vida[i];

            /* desenha o sprite */
            if(vida_atual)
                al_draw_bitmap(vida_atual, 10.0f, 10.0f, 0);
        }
        break;
            
    case FIM_DE_JOGO:
        /* imagem de fim de jogo*/
        if(assets.fundo_gameover) 
            al_draw_bitmap(assets.fundo_gameover, 0, 0, 0);

        /* visualizacao dos botoes + navegacao */
        if(assets.bt_menu && assets.bt_sair) {
            /* cores de destaque */
            ALLEGRO_COLOR cor_select = al_map_rgb(255, 219, 187); 
            ALLEGRO_COLOR cor_not = al_map_rgb(255, 255, 255); 

            /* altura na tela*/
            float menu_y = ALTURA_TELA / 2.4f - 50.0f; 
            float exit_y = menu_y + 180.0f;

            float escala_bt = 0.78f;

            float w_og = al_get_bitmap_width(assets.bt_menu);
            float h_og = al_get_bitmap_height(assets.bt_menu);

            float w_new = w_og * escala_bt;
            float h_new = h_og * escala_bt;

            /* centraliza menu */
            float center_x_menu = LARGURA_TELA / 1.93f - w_new / 1.9f;

            /* botao menu */
            al_draw_tinted_scaled_bitmap(assets.bt_menu, 
                                (current_select == OPCAO_MENU) ? cor_select : cor_not,
                                0, 0,           
                                w_og, h_og, 
                                center_x_menu, menu_y, 
                                w_new, h_new,         
                                0                     
                               );

            /*centraliza sair */  
            float w_sair = al_get_bitmap_width(assets.bt_sair);
            float center_x_sair = LARGURA_TELA / 2.03f - w_sair / 2.0f;           
            
            /* botao sair */
            al_draw_tinted_bitmap(assets.bt_sair, 
                                (current_select == OPCAO_SAIR) ? cor_select : cor_not,
                                center_x_sair, exit_y, 0);
        }
        break;

    case VITORIA:
        /* imagem de vitoria*/
        if(assets.fundo_vitoria) 
            /* desenha a imagem */
            al_draw_bitmap(assets.fundo_vitoria, 0, 0, 0);

        /* visualizacao dos botoes + navegacao */
        if(assets.bt_menu && assets.bt_sair) {
            /* cores de destaque */
            ALLEGRO_COLOR cor_select = al_map_rgb(255, 219, 187); 
            ALLEGRO_COLOR cor_not = al_map_rgb(255, 255, 255); 

            /* altura na tela*/
            float menu_y = ALTURA_TELA / 2.2f - 50.0f; 
            float exit_y = menu_y + 180.0f;

            float escala_bt = 0.78f;

            float w_og = al_get_bitmap_width(assets.bt_menu);
            float h_og = al_get_bitmap_height(assets.bt_menu);

            float w_new = w_og * escala_bt;
            float h_new = h_og * escala_bt;

            /* centraliza menu */
            float center_x_menu = LARGURA_TELA / 1.93f - w_new / 1.9f;

            /* botao menu */
            al_draw_tinted_scaled_bitmap(assets.bt_menu, 
                                (current_select == OPCAO_MENU) ? cor_select : cor_not,
                                0, 0,           
                                w_og, h_og, 
                                center_x_menu, menu_y, 
                                w_new, h_new,         
                                0                     
                               );

            /*centraliza sair */  
            float w_sair = al_get_bitmap_width(assets.bt_sair);
            float center_x_sair = LARGURA_TELA / 2.03f - w_sair / 2.0f;           
            
            /* botao sair */
            al_draw_tinted_bitmap(assets.bt_sair, 
                                (current_select == OPCAO_SAIR) ? cor_select : cor_not,
                                center_x_sair, exit_y, 0);
        }
        break;

    case PAUSE:
        /* desenha a tela de pause do jogo */
        if(assets.fundo_pause) 
            /* desenha a imagem */
            al_draw_bitmap(assets.fundo_pause, 0, 0, 0);
        break;
    
    case SAIR:
        break;
    }
}

/* inputs de teclado*/
void game_input(ALLEGRO_EVENT event) {

    /* pause dentro da fase */
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            if (current_state == JOGANDO) {
                current_state = PAUSE; // pausa 
                /* pausa a musica */
                if(assets.musica_jogo)
                al_set_audio_stream_playing(assets.musica_jogo, false);
                return;  //retorna para evitar alterar o estado do jogo
            } else if (current_state == PAUSE) {
                current_state = JOGANDO; // despausa 
                if(assets.musica_jogo)
                al_set_audio_stream_playing(assets.musica_jogo, true);
                return;
            }
        }
    }

    /* inputs da selecao de botoes do menu */
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (current_state == MENU) {

            if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                current_select = OPCAO_SAIR;
            } 
            /* duas teclas para cima*/
            else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                current_select = OPCAO_INICIAR;
            } 
            /* seleciona a opcao*/
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (current_select == OPCAO_INICIAR) {

                    /* troca as musicas */
                    if(assets.musica_menu) 
                        al_set_audio_stream_playing(assets.musica_menu, false); 
                    
                    if(assets.musica_jogo) {
                        al_rewind_audio_stream(assets.musica_jogo); 
                        al_set_audio_stream_playing(assets.musica_jogo, true);  
                    }

                    current_state = JOGANDO;

                    /* reseta o player */
                    vidas = 3;
                    player_destroy(p);
                    p = player_create();
                    camera_offset_x = 0.0f;
                    item_init();       
                    obstacles_init();
                    
                } else if (current_select == OPCAO_SAIR) {
                    current_state = SAIR;
                }
            }
        }
    }
    /* clique na janela sempre sai */
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        current_state = SAIR;
    }

    /* inputs da selecao de botoes da tela game over */
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (current_state == FIM_DE_JOGO) {

            if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                current_select = OPCAO_SAIR;
            } 
            else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                current_select = OPCAO_MENU;
            } 
            /* seleciona a opcao*/
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (current_select == OPCAO_MENU) {
                    current_state = MENU;
                    vidas = 3;
                    current_select = OPCAO_INICIAR;

                    if(assets.musica_jogo) 
                        al_set_audio_stream_playing(assets.musica_jogo, false);
        
                    if(assets.musica_menu) {
                        al_rewind_audio_stream(assets.musica_menu); //reinicia a musica do menu
                        al_set_audio_stream_playing(assets.musica_menu, true);
                    }

                } else if (current_select == OPCAO_SAIR) {
                    current_state = SAIR;
                }
            }
        }
    }

    /* inputs da tela de vitoria */
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (current_state == VITORIA) {
            if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                current_select = OPCAO_SAIR;
            } 
            else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                current_select = OPCAO_MENU;

            } 
            /* seleciona a opcao*/
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (current_select == OPCAO_MENU) {
                    
                    if(assets.musica_jogo) 
                        al_set_audio_stream_playing(assets.musica_jogo, false);
                    
                    if(assets.musica_menu) {
                        al_rewind_audio_stream(assets.musica_menu); //reinicia a musica do menu
                        al_set_audio_stream_playing(assets.musica_menu, true);
                    }
                    
                    current_state = MENU;
                    vidas = 3;
                    current_select = OPCAO_INICIAR;

                } else if (current_select == OPCAO_SAIR) {
                    current_state = SAIR;
                }
            }
        }
    }
    
    /* player andando dentro do jogo*/
    if(current_state == JOGANDO) {
        /* quando as teclas sao pressionadas */
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if(event.keyboard.keycode == ALLEGRO_KEY_D) 
                player_right(p);

            else if(event.keyboard.keycode == ALLEGRO_KEY_A) 
                player_left(p);
            
            else if(event.keyboard.keycode == ALLEGRO_KEY_W) 
                player_jump(p);
            
            else if(event.keyboard.keycode == ALLEGRO_KEY_S) 
                player_down_start(p);

            else if(event.keyboard.keycode == ALLEGRO_KEY_RSHIFT)
                player_dash(p);
            
        }
        /* quando as teclas sao soltas */
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {
            /* se soltar umas das duas teclas, player para */
            if(event.keyboard.keycode == ALLEGRO_KEY_D || 
                event.keyboard.keycode == ALLEGRO_KEY_A)
                player_stop(p);
            else if(event.keyboard.keycode == ALLEGRO_KEY_S)
                player_down_stop(p);      
        }
    }  
}

