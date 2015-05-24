#ifndef INIT_H
#define INIT_H

#include "main.h"
#include "SDL/SDL.h"
#include <time.h>

void initSpaceship(celestial_object *spaceship, SDL_Surface **surfaces);
void initAsteroid(celestial_object *aste, int size, SDL_Surface **surfaces);
void initBullet(celestial_object *bullet, int size, SDL_Surface **surfaces);
void initExplosion(celestial_object *explosion, SDL_Surface **surfaces);
void initProtection(celestial_object *protection, SDL_Surface **surfaces);
#endif
