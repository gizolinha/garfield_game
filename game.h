/* definicoes basicas para funcionamento e estados do jogo */
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "game_def.h"

/* estado atual do jogo */
extern gamestate current_state;
/* estado da selecao de botao no menu*/
extern menu current_select;

bool game_init();
gamestate game_update();
void game_draw();
void game_input(ALLEGRO_EVENT event);
void game_end();

#endif /* GAME_H */