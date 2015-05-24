#ifndef PHYSIC_H
#define PHYSIC_H

#include <math.h>
#include "SDL/SDL.h"
#include <stdint.h>
#include "main.h"
#include "list.h"
#include "init.h"
#include <assert.h>

int my_round(double a);
void toroidal_space(celestial_object *spaceship);
void calculate_move(celestial_object *obj, int direction);
void calculate_shot(celestial_object *spaceship, celestial_object *bullet);
void move_spaceship(celestial_object *obj);
void move_asteroids(list asteroid_list);
void move_bullet(list bullet_list);
void fire(list *bullet_list, celestial_object *bullet, celestial_object *spaceship);
bool collision(celestial_object *obj1, celestial_object *obj2, SDL_Surface **surfaces);
void check_spaceship_collision(celestial_object *spaceship, list *asteroid_list, list *explosion_list, SDL_Surface **surfaces);
void check_bullet_asteroid_collision(list *bullet_list, list *asteroid_list, list *explosion_list, SDL_Surface **surfaces);
void check_bullet_life_span(list *L);
void destroy_asteroid(celestial_object aste_destroy, list *asteroid_list, SDL_Surface **surfaces);
bool per_pixel_collision(celestial_object *obj1, celestial_object *obj2, SDL_Surface **surfaces);
Uint32 pixel(SDL_Surface *surface, int x, int y);
bool isColorkey(Uint8 r, Uint8 g, Uint8 b);
#endif
