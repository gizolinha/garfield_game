/* definicoes das plataformas */
#ifndef PLATAFORM_H
#define PLATAFORM_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "game_def.h"

#define MAX_PLATAFORMS 20
#define CHAO_NIVEL (ALTURA_TELA - 50.0f)
#define GROUND_Y_OFFSET -16.0f //para o player ficar certinho em cima da plataforma
#define SMALL_Y_OFFSET -30.0f
#define MED_Y_OFFSET -24.0f

/* tipo de plataforma para o sprite */
typedef enum {
    PLATAFORM_GROUND,
    PLATAFORM_SMALL,
    PLATAFORM_MED,
    PLATAFORM_CAI,
} plataformtype;

/* estrutura da plataforma */
typedef struct {
    float x, y;   //posicao     
    float width, height;  //largura
    plataformtype type; 

    float start_y; //onde ela começa para reiniciar
    bool pisada; //se pisou
    int timer; //qunto tempo antes de cair 
} plataform;

extern plataform plataforms[MAX_PLATAFORMS];
extern int n_plataforms;

void plataform_init();
void plataform_draw(float camera_offset_x);
void plataform_update();
plataform* plat_colisao(float px, float py, float pwidth, float pheight, float pvel_y);

#endif /* PLATAFORM_H */