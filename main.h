#ifndef MAIN_H
#define MAIN_H

#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define RIGHT		0
#define LEFT		1

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define FORWARD		0
#define BACK		1

#define BIG		64
#define MEDIUM		32
#define SMALL		16

#define MAX_SPEED	10.

#define BULLET_LIFE_SPAN 80
#define INVINCIBLE      2
#define TIME_INVINCIBILITY 2000
#define ALIVE		0
#define DESTROY		1

#define K_SPACE 0
#define K_UP 1
#define K_DOWN 2
#define K_LEFT 3
#define K_RIGHT 4
#define K_i 5
#define K_w 6

#define NB_OF_KEYS 7

#define CAN 0
#define GO 1
#define CANT 2

#define NUMBER_OF_SURFACES 10

enum indice_tab_surfaces_u {
  iSCREEN,
  iSPACE,
  iSPACESHIP,
  iPROTECTION,
  iSMALL_ASTE,
  iMEDIUM_ASTE,
  iBIG_ASTE,
  iBULLET,
  iEXPLOSION,
  iBIG_BULLET
};

enum gamestates_u {
  init,
  menu,
  play,
  end,
  music,
  mod
};

typedef enum indice_tab_surfaces_u indice;
typedef enum gamestates_u gamestates;

struct celestial_object_t {
  float speed;
  float x_move;
  float y_move;
  
  SDL_Rect rcSrc;
  SDL_Rect position;
  
  SDL_Surface *surface;

  int sprite_size;
  int nb_of_sprite;

  int direction_of_rotation;

  int life_span;
  
  bool isExplosionOfSpaceship;
}; 

typedef struct celestial_object_t celestial_object;

#endif
