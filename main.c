/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: bruno
 *
 * Created on 22 de junio de 2021, 20:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

#define BUFFER_H 480
#define BUFFER_W 640
#define PALETA_W 10
#define PALETA_H 50
#define PALETA_SPEED 4

#define PELOTA_SIZE 10
#define PELOTA_SPEED 2.5

#define FPS    60.0
#define SCREEN_W  640
#define SCREEN_H  480

typedef struct
{
    double x, y;
    double dy;
    double w,h;
    
}PALETA;

typedef struct
{
    double x,y;
    double dx,dy;
    double w,h; 
    
}PELOTA;


enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D //arrow keys
};


int colision(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

/*
 * 
 */
int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *player1 = NULL;
    ALLEGRO_BITMAP *player2 = NULL;
    ALLEGRO_BITMAP *al_pelota = NULL;
    
    bool key_pressed[8] = {false, false, false, false, false, false, false, false}; //Estado de teclas, true cuando esta apretada
    bool redraw = false;
    bool do_exit = false;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    
    player1 = al_create_bitmap(PALETA_W, PALETA_H);
    if (!player1) {
        fprintf(stderr, "failed to create player1 bitmap!\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    player2 = al_create_bitmap(PALETA_W, PALETA_H);
    if (!player2) {
        fprintf(stderr, "failed to create player2 bitmap!\n");
        al_destroy_bitmap(player1);
        al_destroy_timer(timer);
        return -1;
    }
    
    al_pelota = al_create_bitmap(PELOTA_SIZE, PELOTA_SIZE);
    if (!player2) {
        fprintf(stderr, "failed to create player2 bitmap!\n");
        al_destroy_bitmap(player2);
        al_destroy_bitmap(player1);
        al_destroy_timer(timer);
        return -1;
    }
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(player1);
        al_destroy_bitmap(player2);
        al_destroy_bitmap(al_pelota);
        al_destroy_timer(timer);
        return -1;
    }
    
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        al_destroy_bitmap(player1);
        al_destroy_bitmap(player2);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    
    

    
    al_set_target_bitmap(player1);
    al_clear_to_color(al_map_rgb(255,255,255));
    
    al_set_target_bitmap(player2);
    al_clear_to_color(al_map_rgb(255,255,255));
    
    al_set_target_bitmap(al_pelota);
    al_clear_to_color(al_map_rgb(255,255,255));
    
    al_set_target_bitmap(al_get_backbuffer(display));

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); 
        
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    PALETA paleta1 = {.x=0, .y=BUFFER_H/2 - PALETA_H/2,.dy=4, .w=PALETA_W, .h=PALETA_H};
    PALETA paleta2 = {.x= BUFFER_W - PALETA_W, .y=BUFFER_H/2 - PALETA_H/2, .dy=4,.w=PALETA_W, .h=PALETA_H};
    
    PELOTA pelota = {.x=BUFFER_W/2, .y=BUFFER_H/2, .dx=PELOTA_SPEED, .dy=PELOTA_SPEED ,.w=PELOTA_SIZE, .h=PELOTA_SIZE};
    
    
    al_start_timer(timer);
    
    while (!do_exit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                if (key_pressed[KEY_UP] && paleta2.y >= 0)
                   paleta2.y -= paleta2.dy;

                if (key_pressed[KEY_DOWN] && paleta2.y <= BUFFER_H - PALETA_H)
                    paleta2.y  += paleta2.dy;

                if (key_pressed[KEY_W] && paleta1.y >= 0)
                   paleta1.y -= paleta1.dy;

                if (key_pressed[KEY_S] && paleta1.y <= BUFFER_H - PALETA_H)
                    paleta1.y += paleta1.dy;

                int choque;
                
                if((choque = colision (pelota.x, pelota.y, pelota.w, pelota.h, paleta1.x, paleta1.y, paleta1.w, paleta1.h))!= 0)
                {
                    pelota.dx = -pelota.dx;
                    pelota.dy = ((double)choque-PALETA_H/2)/PALETA_H * PELOTA_SPEED;
                }
                
                if((choque = colision (pelota.x, pelota.y ,pelota.w, pelota.h, paleta2.x, paleta2.y, paleta2.w, paleta2.h)) != 0)
                {
                    pelota.dx = -pelota.dx;
                    pelota.dy = ((double)choque-PALETA_H/2)/PALETA_H * PELOTA_SPEED;
                }
                
                if(pelota.x <= 0 || pelota.x >= BUFFER_W - PELOTA_SIZE)
                {
                    pelota.dx = -pelota.dx;
                }
                
                if(pelota.y <= 0 || pelota.y >= BUFFER_H - PELOTA_SIZE)
                {
                    pelota.dy = -pelota.dy;
                }
                
                pelota.x += pelota.dx;
                pelota.y += pelota.dy;
                
                
                redraw = true;
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                do_exit = true;

            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (ev.keyboard.keycode) {
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
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
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
                        do_exit = true;
                        break;
                }
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            al_draw_bitmap(player1, paleta1.x, paleta1.y, 0);
            al_draw_bitmap(player2, paleta2.x, paleta2.y, 0);

            al_draw_bitmap(al_pelota, pelota.x, pelota.y, 0);
            
            al_flip_display();
        }
    }

    al_destroy_bitmap(player2);
    al_destroy_bitmap(player1);
    al_destroy_timer(timer);
    al_destroy_display(display);
    return 0;
    
    return (EXIT_SUCCESS);
}

int colision(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
    if(x1 >= x2 + w2)
        return 0;
   
    else if (x2 >= x1 + w1)
        return 0;
    
    else if (y1 >= y2 + h2)
        return 0;
    
    else if (y2 >= y1 + h1)
        return 0;
    
    else
        return y1-y2;
}