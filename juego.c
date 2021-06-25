#include "juego.h"


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

static int colision(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

bool key_pressed[8] = {false, false, false, false, false, false, false, false};

PALETA paleta1 = {.x=0, .y=BUFFER_H/2 - PALETA_H/2,.dy=4, .w=PALETA_W, .h=PALETA_H};
PALETA paleta2 = {.x= BUFFER_W - PALETA_W, .y=BUFFER_H/2 - PALETA_H/2, .dy=4,.w=PALETA_W, .h=PALETA_H};

PELOTA pelota = {.x=BUFFER_W/2, .y=BUFFER_H/2, .dx=PELOTA_SPEED, .dy=PELOTA_SPEED ,.w=PELOTA_SIZE, .h=PELOTA_SIZE};

void juego(void)
{    
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
     

}

static int colision(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
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