/* definicoes dos itens coletaveis do jogo */
#ifndef ITENS_H
#define ITENS_H

#include <allegro5/allegro.h>
#include "game_def.h"
#include "player.h"

/* Tipos de itens */
typedef enum {
    LASANHA_VITORIA, 
    URSO_VIDA,
} itens_type;

typedef struct {
    float x, y;
    int width, height;
    bool active;
    itens_type type;
} itens;

#define MAX_ITENS 2

extern itens item[MAX_ITENS];
extern int n_itens;

void item_init();
void item_draw(float camera_offset_x);
int item_colisao(player* p);

#endif /* ITENS_H */