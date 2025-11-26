/*agrupa todos os recursos allegro*/
#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "game_def.h"

typedef struct {
    ALLEGRO_BITMAP* player_parado[FRAMES_PARADO]; //array de sprites
    ALLEGRO_BITMAP* player_andando[FRAMES_ANDANDO];
    ALLEGRO_BITMAP* player_pulando[FRAMES_PULANDO];
    ALLEGRO_BITMAP* player_abaixado[FRAMES_ABAIXADO];
    ALLEGRO_BITMAP* player_dash;
    ALLEGRO_BITMAP* sprites_vida[5];
    ALLEGRO_BITMAP* obst_green[FRAMES_GREEN];
    ALLEGRO_BITMAP* obst_flowy[FRAMES_FLOWY];
    ALLEGRO_BITMAP* obst_clock[FRAMES_CLOCK];
    ALLEGRO_BITMAP* fundo_menu; //tela de menu
    ALLEGRO_BITMAP* fundo_gameover;
    ALLEGRO_BITMAP* fundo_vitoria;
    ALLEGRO_BITMAP* bt_iniciar; //botao menu iniciar
    ALLEGRO_BITMAP* bt_sair; //botao menu sair
    ALLEGRO_BITMAP* bt_menu;
    ALLEGRO_BITMAP* fundo_game; //fundo se movimenta
    ALLEGRO_BITMAP* fundo_pause;
    ALLEGRO_BITMAP* plataform_ground;
    ALLEGRO_BITMAP* plataform_small;
    ALLEGRO_BITMAP* plataform_med;
    ALLEGRO_BITMAP* lasanha;
    ALLEGRO_BITMAP* urso;
    ALLEGRO_AUDIO_STREAM *musica_menu;
    ALLEGRO_AUDIO_STREAM *musica_jogo;
    
} gameresources;

/*variavel com todos os resources*/
extern gameresources assets;

/*funcoes sobre os resources*/
bool resources_load_all(); 
void resources_unload_all(); 

#endif /*RESOURCES_H*/