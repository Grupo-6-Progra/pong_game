#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

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