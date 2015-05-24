#include "keyboard.h"

extern gamestates state;

bool keyPressed(Uint8 *keystates)
{
  return (keystates[SDLK_UP]
	  || keystates[SDLK_DOWN]
	  || keystates[SDLK_RIGHT]
	  || keystates[SDLK_LEFT]	
	  || keystates[SDLK_i]	
	  || keystates[SDLK_o]	
	  || keystates[SDLK_w]
		|| keystates[SDLK_p]
	  || keystates[SDLK_SPACE]
	  );
}

void delay(int *delay_array, int *press_date, Uint8 *keystates)
{
  int time_now;

  /* #################### PLAY ################### */
  if (state == play) {
    /* --- SPACE --- */
    if (keystates[SDLK_SPACE]) {
      if (delay_array[K_SPACE] == CAN)
        delay_array[K_SPACE] = GO;
      else if (delay_array[K_SPACE] == GO)
        delay_array[K_SPACE] = CANT; 
    }

    else {
      delay_array[K_SPACE] = CAN;
    }

    /* --- I --- */
    if (keystates[SDLK_i]) {
      if (delay_array[K_i] == CAN)
        delay_array[K_i] = GO;
      else if (delay_array[K_i] == GO)
        delay_array[K_i] = CANT; 
    }

    else {
      delay_array[K_i] = CAN;
    }


    /* --- W --- */
    if (keystates[SDLK_w]) {
      if (delay_array[K_w] == CAN)
        delay_array[K_w] = GO;
      else if (delay_array[K_w] == GO)
        delay_array[K_w] = CANT; 
    }

    else {
      delay_array[K_w] = CAN;
    }

    /* --- UP --- */
    if (keystates[SDLK_UP]) {
      if (SDL_GetTicks() - press_date[K_UP] > DELAY) {
        delay_array[K_UP] = GO;
        press_date[K_UP] = SDL_GetTicks();
      }
      else
        delay_array[K_UP] = CANT;
    }
    /* --- DOWN --- */
    if (keystates[SDLK_DOWN]) {
      if (SDL_GetTicks() - press_date[K_DOWN] > DELAY) {
        delay_array[K_DOWN] = GO;
        press_date[K_DOWN] = SDL_GetTicks();
      }
      else
        delay_array[K_DOWN] = CANT;
    }
    /* --- RIGHT --- */
    if (keystates[SDLK_RIGHT]) {
      if (SDL_GetTicks() - press_date[K_RIGHT] > DELAY) {
        delay_array[K_RIGHT] = GO;
        press_date[K_RIGHT] = SDL_GetTicks();
      }
      else
        delay_array[K_RIGHT] = CANT;
    }
    /* --- LEFT --- */
    if (keystates[SDLK_LEFT]) {
      if (SDL_GetTicks() - press_date[K_LEFT] > DELAY) {
        delay_array[K_LEFT] = GO;
        press_date[K_LEFT] = SDL_GetTicks();
      }
      else
        delay_array[K_LEFT] = CANT;
    }

  }	

  /* #################### MUSIC ################### */
  if (state == music) {
    if (keystates[SDLK_UP]) {
      if (delay_array[K_UP] == CAN)
	delay_array[K_UP] = GO;
      else if (delay_array[K_UP] == GO)
	delay_array[K_UP] = CANT; 
    }

    else {
      delay_array[K_UP] = CAN;
    }
    if (keystates[SDLK_DOWN]) {
      if (delay_array[K_DOWN] == CAN)
	delay_array[K_DOWN] = GO;
      else if (delay_array[K_DOWN] == GO)
	delay_array[K_DOWN] = CANT; 
    }
    else {
      delay_array[K_DOWN] = CAN;
    }
  }
}

