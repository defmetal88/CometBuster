#ifndef EVENT_H
#define EVENT_H

#include "SDL/SDL.h"
#include "main.h"


#include "list.h"

void HandleEvent(SDL_Event event, celestial_object *spaceship, list *bullets, celestial_object *bullet, celestial_object *big_bullet, Uint8 *keystates,list *asteroid_list, int *delay_array);

#endif
