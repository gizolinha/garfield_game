/* definicoes para os obstaculos */
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <allegro5/allegro.h>
#include "game_def.h"
#include "player.h"

#define MAX_OBSTACLES 10

typedef struct {
    float x,y;
    float width, height;
    float vel_x;      // velocidade
    float min_x;      // limite a esquerda
    float max_x;      // limite a direita
    int type;         // sprite
    bool active;    
    int current_frame; //animacao
    int frame_timer;
    int max_frames;
} obstacle;

extern obstacle obstacles[MAX_OBSTACLES];
extern int n_obstacles;

void obstacles_init();
void obstacles_update();
void obstacles_draw(float camera_offset_x);
bool obst_colisao(player* p);

#endif /* OBSTACLE_H*/