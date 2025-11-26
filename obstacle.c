#include "obstacle.h"
#include "resources.h"
#include "plataform.h"
#include <stdio.h>

obstacle obstacles[MAX_OBSTACLES];
int n_obstacles = 0;

/* pega o sprite do obstaculo e a quantidade de frames */
ALLEGRO_BITMAP* get_sprite(int type, int frame) {
    switch (type) {
        case OBS_TYPE_GREEN:
            if (frame < FRAMES_GREEN) 
                return assets.obst_green[frame];
            break;

        case OBS_TYPE_FLOWY:
            if (frame < FRAMES_FLOWY)  
                return assets.obst_flowy[frame];
            break;

        case OBS_TYPE_CLOCK:
            if (frame < FRAMES_CLOCK) 
                return assets.obst_clock[frame];
            break;
    }
    return NULL;
}

/* criar um obstaculo */
void obst_create(float x, float y, float dist, int type) {
    if(n_obstacles >= MAX_OBSTACLES)
        return;

    obstacle* obs = &obstacles[n_obstacles];

    obs->x = x;
    obs->y = y;
    obs->type = type;
    obs->active = true;
    /* movimentacao */
    obs->min_x = x;
    obs->max_x = x + dist;

    if (dist == 0) 
        obs->vel_x = 0.0f; 
    else 
        obs->vel_x = 2.0f; 
    
    /* animacao sprite */
    obs->current_frame = 0;
    obs->frame_timer = 0;

    /* limite de frames de acordo com o sprite*/
    switch (type) {
        case OBS_TYPE_GREEN: obs->max_frames = FRAMES_GREEN; 
            break;
        case OBS_TYPE_FLOWY: obs->max_frames = FRAMES_FLOWY; 
            break;
        case OBS_TYPE_CLOCK: obs->max_frames = FRAMES_CLOCK; 
            break;
        default: obs->max_frames = 1; 
            break;
    }

    /* hitbox dos obstaculos (com primeiro frame) */
    ALLEGRO_BITMAP* frame = get_sprite(type, 0);
    if(frame) {
        obs->width = al_get_bitmap_width(frame) * ESCALA_OBST;
        obs->height = al_get_bitmap_height(frame) * ESCALA_OBST;
    } else {
        //define um tamanho padrao 
        obs->width = 32;
        obs->height = 32;
    }
    n_obstacles++;
}

/* inicia os obstaculos */
void obstacles_init() {

    obst_create(600.0f, CHAO_NIVEL - 90.0f, 0.0f, OBS_TYPE_FLOWY);

    obst_create(1150.0f, CHAO_NIVEL - 180.0f - 50.0f, 200.0f, OBS_TYPE_GREEN);

    obst_create(1600.0f, CHAO_NIVEL - 90.0f, 910.0f, OBS_TYPE_CLOCK);
    obst_create(1900.0f, CHAO_NIVEL - 90.0f, 500.0f, OBS_TYPE_CLOCK);

    obst_create(2015.0f, CHAO_NIVEL - 238.0f, 0.0f, OBS_TYPE_FLOWY);
    obst_create(3600.0f, CHAO_NIVEL - 90.0f, 400.0f, OBS_TYPE_GREEN);
    obst_create(3300.0f, CHAO_NIVEL - 90.0f, 600.0f, OBS_TYPE_GREEN);

    obst_create(3600.0f, CHAO_NIVEL - 230.0f, 0.0f, OBS_TYPE_FLOWY);
    
    obst_create(4720.0f, CHAO_NIVEL - 235.0f, 0.0f, OBS_TYPE_FLOWY);
    
}

/* atualiza os obstaculos (obstaculos que se movem)*/
void obstacles_update() {
    for (int i = 0; i < n_obstacles; i++) {
        obstacle* obs = &obstacles[i];
        if (!obs->active) 
            continue;

        //movimentacao
        obs->x += obs->vel_x;

        if (obs->x <= obs->min_x) {
            obs->x = obs->min_x;
            obs->vel_x *= -1; 
        }
        else if (obs->x >= obs->max_x) {
            obs->x = obs->max_x;
            obs->vel_x *= -1; 
        }

        //animacao baseada no sprite
        obs->frame_timer++;
        if (obs->frame_timer >= FPS_OBSTACLE) {
            obs->frame_timer = 0;
            obs->current_frame++;
            
            //max_frames da create
            if (obs->current_frame >= obs->max_frames) {
                obs->current_frame = 0;
            }
        }
    }
}

/* desenha os obstaculos */
void obstacles_draw(float camera_offset_x) {
    for (int i = 0; i < n_obstacles; i++) {
        obstacle* obs = &obstacles[i];
        if (!obs->active) 
            continue;

        /* usa a get sprite para pegar sprite do obstaculo certo */
        ALLEGRO_BITMAP* sprite = get_sprite(obs->type, obs->current_frame);
        
        if (!sprite)
            continue;

        /* direcao da animacao do sprite */
        int dir = (obs->vel_x < 0) ? ALLEGRO_FLIP_HORIZONTAL : 0; 

        float w_og = al_get_bitmap_width(sprite);
        float h_og = al_get_bitmap_height(sprite);
        
        al_draw_scaled_bitmap(sprite, 0, 0, w_og, h_og, obs->x + camera_offset_x, obs->y, w_og * ESCALA_OBST, h_og * ESCALA_OBST, dir);
    }
}

bool obst_colisao(player* p) {
    /* hitbox d player para os obstaculos */
    float p_left = p->x - (p->width * 0.2f);
    float p_right = p->x + (p->width * 0.2f);
    float p_top = p->y - (p->height / 1.5f);
    float p_bottom = p->y + p->height;

    for (int i = 0; i < n_obstacles; i++) {
        obstacle* obs = &obstacles[i];
        if (!obs->active) continue;

        float o_left = obs->x;
        float o_right = obs->x + obs->width;
        float o_top = obs->y;
        float o_bottom = obs->y + obs->height;

        /* caso colidir */
        if (p_right > o_left && p_left < o_right &&
            p_bottom > o_top && p_top < o_bottom) {
            return true;
        }
    }
    return false;
}