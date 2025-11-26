#include "plataform.h"
#include "player.h"
#include "game_def.h" 
#include "resources.h"

plataform plataforms[MAX_PLATAFORMS];
int n_plataforms = 0;

/* inicializacao das plataformas */
void plataform_init() {
    /* zera a cada inicializacao */
    n_plataforms = 0;

   /* chao inicial */
   if(n_plataforms < MAX_PLATAFORMS) {
      plataform *plat = &plataforms[n_plataforms];
      
      plat->x = 0.0f; //posicao
      plat->width = 970.0f; //tamanho
      plat->y = CHAO_NIVEL; //diferenca do chao
      plat->height = 50.0f; //altura
      plat->type = PLATAFORM_GROUND;
      n_plataforms++;
   }

   /* plataforma (aerea buraco) */
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 1130.0f; 
        plat->width = 270.0f; 
        plat->y = CHAO_NIVEL - 150.0f; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }

    /* plataforma (prim aerea chao)) */
    if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 1820.0f; 
        plat->width = 450.0f; 
        plat->y = CHAO_NIVEL - 150.0f; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }

    /* plataforma (segunda aerea chao)*/
     if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 1970.0f; 
        plat->width = 97.0f; 
        plat->y = CHAO_NIVEL - 300.0f; 
        plat->height = 20.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }

   /* plataforma (segundo chao)*/
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        plat->x = 1560.0f; 
        plat->width = 935.0f; 
        plat->y = CHAO_NIVEL; 
        plat->height = 50.0f;
        plat->type = PLATAFORM_GROUND;
        n_plataforms++;
    }

    /* plataforma que cai */
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 2700.0f; 
        plat->width = 290.0f; 
        plat->y = CHAO_NIVEL - 150.0f; 
        plat->height = 60.0f;
        /*queda*/
        plat->type = PLATAFORM_CAI;
        plat->start_y = plat->y; //posicao original 
        plat->pisada = false;  
        plat->timer = 0;
        n_plataforms++;
    }

    /* plataforma (terceiro chao)*/
    if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 3150.0f; //
        plat->width = 1000.0f; 
        plat->y = CHAO_NIVEL; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_GROUND;
        n_plataforms++;
    }

    /* plataforma (aerea 1) */
    if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 3400.0f; 
        plat->width = 500.0f; 
        plat->y = CHAO_NIVEL - 150.0f; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_MED;
        n_plataforms++;
    }

    /* plataforma (aerea 2)*/
    if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 3900.0f; 
        plat->width = 98.0f; 
        plat->y = CHAO_NIVEL - 260.0f; 
        plat->height = 20.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }
    
    /* plataforma (aerea 3)*/
    if(n_plataforms < MAX_PLATAFORMS) {
        plataform* plat = &plataforms[n_plataforms];
        
        plat->x = 4110.0f;
        plat->width = 98.0f;
        plat->y = CHAO_NIVEL - 160.0f;
        plat->height = 20.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }    

     /* plataforma (aerea 4) */
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 4340.0f; 
        plat->width = 100.0f; 
        plat->y = CHAO_NIVEL - 260.0f; 
        plat->height = 60.0f;
        /*queda*/
        plat->type = PLATAFORM_CAI;
        plat->start_y = plat->y; //posicao original 
        plat->pisada = false;  //parada
        plat->timer = 0;
        n_plataforms++;
    }

     /* plataforma (aerea 5) */
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 4600.0f; 
        plat->width = 270.0f; 
        plat->y = CHAO_NIVEL - 150.0f; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_SMALL;
        n_plataforms++;
    }

    /* plataforma (ultima aerea) */
   if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];

        plat->x = 5050.0f; 
        plat->width = 100.0f; 
        plat->y = CHAO_NIVEL - 110.0f; 
        plat->height = 60.0f;
        /*queda*/
        plat->type = PLATAFORM_CAI;
        plat->start_y = plat->y; //posicao original 
        plat->pisada = false;  //parada
        plat->timer = 0;
        n_plataforms++;
    }

    /* plataforma 8 (ultimo chao)*/
    if (n_plataforms < MAX_PLATAFORMS) {
        plataform *plat = &plataforms[n_plataforms];
        
        plat->x = 5270.0f; //
        plat->width = 700.0f; 
        plat->y = CHAO_NIVEL; 
        plat->height = 60.0f;
        plat->type = PLATAFORM_GROUND;
        n_plataforms++;
    }

}

/* atualiza a posicao da plataforma (para as quedas)*/
void plataform_update() {
    for (int i = 0; i < n_plataforms; i++) {
        plataform *plat = &plataforms[i];

        /* so cai se for o tipo e estiver pisada */
        if (plat->type == PLATAFORM_CAI && plat->pisada) {
            
            plat->timer++;

            /* espera antes de cair */
            if (plat->timer < 50) {
            }
            else {
                plat->y += 5.0f; // velocidade de queda
            }

            /* reseta e volta a posicao original */
            if (plat->y > ALTURA_TELA + 100) {
                plat->y = plat->start_y;
                plat->pisada = false;
                plat->timer = 0;
            }
        }
    }
}


/* desenhar as plataformas */
void plataform_draw(float camera_offset_x) {

    for (int i = 0; i < n_plataforms; i++) {
        plataform *plat = &plataforms[i];
        
        ALLEGRO_BITMAP *sprite_to_draw = NULL;
        float y_offset = 0.0f; //offset do chao

        /* seleciona o sprite e offset do chao correto */
        switch (plat->type) {
            case PLATAFORM_GROUND:
                sprite_to_draw = assets.plataform_ground;
                y_offset = GROUND_Y_OFFSET; //offset em relacao ao chao
                break;
            case PLATAFORM_SMALL:
                sprite_to_draw = assets.plataform_small;
                y_offset = SMALL_Y_OFFSET;
                break;
            case PLATAFORM_MED:
                sprite_to_draw = assets.plataform_med;
                y_offset = MED_Y_OFFSET;
                break;
            case PLATAFORM_CAI:
                sprite_to_draw = assets.plataform_small; 
                y_offset = SMALL_Y_OFFSET;
                break;
        }
        
        if (!sprite_to_draw) 
            continue; 

        float tile_w = al_get_bitmap_width(sprite_to_draw);
        float start_x = plat->x + camera_offset_x;

        // posicao y
        float hitbox_y = plat->y; 

        //posicao de desenho com hitbox e offset
        float draw_y = hitbox_y + y_offset;

        for (float current_x = start_x; current_x < start_x + plat->width; current_x += tile_w) {
            al_draw_bitmap(sprite_to_draw, current_x, draw_y, 0 );
        }
    }
}

/* funcao de colisao nas plataformas */
plataform* plat_colisao(float px, float py, float pwidth, float pheight, float pvel_y) {
    
    /* ve se o persongaem esta caindo*/
    if (pvel_y < 0) {
        return NULL;
    }
    
    /* coordenadas do player */
    float player_left = px - pwidth / 2.0f;
    float player_right = px + pwidth / 2.0f;
    float player_ground = py + pheight / 2.0f;
    float player_ant_ground = (py - pvel_y) + pheight / 2.0f; //altura na antiga plataforma 
    
    
    for (int i = 0; i < n_plataforms; i++) { 
        plataform *plat = &plataforms[i]; 
        
        /* coordenadas da plataforma */
        float plat_left = plat->x;
        float plat_right = plat->x + plat->width;
        float plat_top = plat->y;

        /* sobrepoe x */
        bool x_overlap = (player_right > plat_left) && (player_left < plat_right);
        /* cai em y */
        bool y_landing = (player_ground >= plat_top) && (player_ant_ground <= plat_top);
        
        if (x_overlap && y_landing) {
            return plat; //colide com a plataforma
        }
    }
    return NULL; //nao colide
}