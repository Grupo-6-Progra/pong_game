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
#include "juego.h"
#include "al_frontend.h"

#define FPS    60.0
#define SCREEN_W  640
#define SCREEN_H  480

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
    
    
    al_start_timer(timer);
    
    while (!do_exit) {
        ALLEGRO_EVENT ev;
        
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                //game logic (BACK-END)
                juego();
                
                if (key_pressed [KEY_ESCAPE] ==true)
                {
                    do_exit = true;
                }
                                        
                redraw = true;
            }
            
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                do_exit = true;

            actualizar_teclado(&ev);
            
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
    
    return (EXIT_SUCCESS);
}