/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juego.h
 * Author: bruno
 *
 * Created on 24 de junio de 2021, 22:29
 */

#ifndef JUEGO_H
#define JUEGO_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
    
#define BUFFER_H 480
#define BUFFER_W 640
#define PALETA_W 10
#define PALETA_H 50
#define PALETA_SPEED 4

#define PELOTA_SIZE 10
#define PELOTA_SPEED 2.5    
    
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

    
enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D, KEY_ESCAPE //arrow keys
};

extern bool key_pressed[8];
extern PALETA paleta1;
extern PALETA paleta2;
extern PELOTA pelota;

void juego(void);


#ifdef __cplusplus
}
#endif

#endif /* JUEGO_H */

