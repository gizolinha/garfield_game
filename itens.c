#include "itens.h"
#include "resources.h"
#include "plataform.h"

itens item[MAX_ITENS];
int n_itens = 0;

/* inicializa o item */
void item_create(float x, float y, itens_type type) {
    if(n_itens >= MAX_ITENS)
        return;

    itens* i = &item[n_itens];
    i->x = x;
    i->y = y;
    i->type = type;
    i->active = true;

    /* tamanho baseado no srpite*/
    ALLEGRO_BITMAP* sprite = NULL;
    float escala = 1.0f; // padrao 

    if(type == LASANHA_VITORIA) {
        sprite = assets.lasanha;
        escala = 0.04f;
    }
    else if(type == URSO_VIDA) {
        sprite = assets.urso;
        escala = 0.3f;
    }

    if(sprite) {
        i->width = al_get_bitmap_width(sprite) * escala;
        i->height = al_get_bitmap_height(sprite) * escala;

        /* ajuste em y*/
        i->y = y - i->height;
    }
    n_itens++;
}

/* cria os itens */
void item_init() {
    n_itens = 0;

    item_create(5800.0f, CHAO_NIVEL - 20.0f, LASANHA_VITORIA);
    item_create(2010.0f, CHAO_NIVEL - 320.f, URSO_VIDA);
}

/* desenha o item no jogo */
void item_draw(float camera_offset_x) {
    for(int i = 0; i < n_itens; i++) {
        itens* items = &item[i];

        if(!items->active)
            continue;

        ALLEGRO_BITMAP* sprite = NULL;
        float escala = 1.0f; // padrao 
        if(items->type == LASANHA_VITORIA) {
            sprite = assets.lasanha;
             escala = 0.04;
        }
        else if(items->type == URSO_VIDA) {
            sprite = assets.urso;
            escala = 0.3;
        }

        if (sprite) {
            float w = al_get_bitmap_width(sprite);
            float h = al_get_bitmap_height(sprite);
            
            al_draw_scaled_bitmap(sprite, 0, 0, w, h, 
                items->x + camera_offset_x, items->y, 
                w * escala, h * escala, 
                0);
        }
    }
}

/* colisao do player com os itens */
int item_colisao(player* p) {
    /* hitbox do player */
    float p_left = p->x - (p->width * 0.6f);
    float p_right = p->x + (p->width * 0.3f);
    float p_top = p->y - (p->height / 1.0f);
    float p_bottom = p->y + (p->height / 2.0f);

    for(int i = 0; i < n_itens; i++) {
        itens* items = &item[i];

        if(!items->active)
            continue;

        float i_left = items->x;
        float i_right = items->x + items->width;
        float i_top = items->y;
        float i_bottom = items->y + items->height;

        /* quando colide consome o item */
        if (p_right > i_left && p_left < i_right &&
            p_bottom > i_top && p_top < i_bottom) {
            
            items->active = false; // consome
            return items->type;    // qual item colidiu
        }

    }
    return -1;
}