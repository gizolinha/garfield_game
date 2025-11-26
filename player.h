/* definicoes basicas para o player(personagem) */
#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include "game.h"

/*estado do player*/
typedef enum {
    PARADO,
    ANDANDO,
    PULANDO,
    ABAIXADO,
    DASH, 
} player_state;

/* direcao do player */
typedef enum {
    DIREITA = 1,
    ESQUERDA = 0
} player_dir;

/* estrutura do jogador*/
typedef struct {
    float x, y, vel_x, vel_y;
    int width;   // largura do sprite
    int height;  // altura do sprite
    player_state state;
    bool on_ground; //para fisica do pulo
    int current_frame; //frame atual 
    int frame_timer;   //controlar a velocidade da troca de frames
    int anim_direct; //direcao da animacao
    int dash_timer; //quanto tempo dura
    int dash_cooldown; //tempo para usar novamente
    player_dir direct; //direcao em que o player esta virado

} player;


player *player_create();
void player_destroy(player* p);
void player_update(player* p);
void player_draw(player* p, float camera_offset_x);
void player_dash(player* p);

/* funcoes de input teclado */
void player_jump(player* p);
void player_right(player* p);
void player_left(player* p);
void player_down_start(player* p);
void player_down_stop(player* p);
void player_stop(player* p);

#endif /* PLAYER_H */