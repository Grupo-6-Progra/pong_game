#include "al_frontend.h"
#include "juego.h"
#include <allegro5/allegro.h>

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



void actualizar_teclado(ALLEGRO_EVENT * ev)
{
    if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key_pressed[KEY_UP] = true;
                break;

            case ALLEGRO_KEY_DOWN:
                key_pressed[KEY_DOWN] = true;
                break;

            case ALLEGRO_KEY_LEFT:
                key_pressed[KEY_LEFT] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                key_pressed[KEY_RIGHT] = true;
                break;

            case ALLEGRO_KEY_W:
                key_pressed[KEY_W] = true;
                break;

            case ALLEGRO_KEY_S:
                key_pressed[KEY_S] = true;
                break;

            case ALLEGRO_KEY_A:
                key_pressed[KEY_A] = true;
                break;

            case ALLEGRO_KEY_D:
                key_pressed[KEY_D] = true;
                break;
        }
    }
    else if (ev->type == ALLEGRO_EVENT_KEY_UP) {
        switch (ev->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key_pressed[KEY_UP] = false;
                break;

            case ALLEGRO_KEY_DOWN:
                key_pressed[KEY_DOWN] = false;
                break;

            case ALLEGRO_KEY_LEFT:
                key_pressed[KEY_LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                key_pressed[KEY_RIGHT] = false;
                break;

            case ALLEGRO_KEY_W:
                key_pressed[KEY_W] = false;
                break;

            case ALLEGRO_KEY_S:
                key_pressed[KEY_S] = false;
                break;

            case ALLEGRO_KEY_A:
                key_pressed[KEY_A] = false;
                break;

            case ALLEGRO_KEY_D:
                key_pressed[KEY_D] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                key_pressed[KEY_ESCAPE] = true;
                break;
        }
    }
}
