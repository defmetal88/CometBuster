#include "init.h"

void initSpaceship(celestial_object *spaceship, SDL_Surface **surfaces)
{
  indice id;
  
  // Set the surface
  spaceship->surface = surfaces[id = iSPACESHIP];

  // Sprite's info
  spaceship->sprite_size = 32;
  spaceship->nb_of_sprite = 36;
  spaceship->rcSrc.x = 0;
  spaceship->rcSrc.y = 0;
  spaceship->rcSrc.w = spaceship->sprite_size;
  spaceship->rcSrc.h = spaceship->sprite_size;

  // Position
  spaceship->position.x = SCREEN_WIDTH / 2;
  spaceship->position.y = SCREEN_HEIGHT / 2;

  // Movements
  spaceship->speed = 0.;

  spaceship->x_move = 0;
  spaceship->y_move = 0;  
}


void initAsteroid(celestial_object *aste, int size, SDL_Surface **surfaces)
{
  int rand_number;
  indice id;
  

  switch (size) {
  case SMALL:
    aste->surface = surfaces[id = iSMALL_ASTE];
    break;
  case MEDIUM:
    aste->surface = surfaces[id = iMEDIUM_ASTE];
    break;
  case BIG:
    aste->surface = surfaces[id = iBIG_ASTE];
    break;
  default:
    break;
    }

  // Sprite's info
  aste->nb_of_sprite = 32;
  aste->sprite_size = size;
  aste->rcSrc.x = 0;
  aste->rcSrc.y = 0;
  aste->rcSrc.w = aste->sprite_size;
  aste->rcSrc.h = aste->sprite_size;

  // Position

  aste->position.x = rand() % SCREEN_WIDTH;
	if (aste->position.x < (SCREEN_WIDTH /2 - 150) || aste->position.x > (SCREEN_WIDTH/2 + 150)) {
		aste->position.y = rand() % SCREEN_HEIGHT;
	}
	else {
		if (rand() % 2 == 1) {
			aste->position.y = rand() % (SCREEN_HEIGHT/2 - 150); 
		}

		else {
			aste->position.y = (rand() % ((SCREEN_HEIGHT/2) - 150)) + (SCREEN_HEIGHT/2 +150);
		}
	}
		
  aste->direction_of_rotation = rand() % 2;
  
  // Movements
  aste->speed = 1.;
  
  rand_number = rand() % 3;
  if (rand_number == 0) 
    aste->x_move = 1;
  else if (rand_number == 1)
    aste->x_move = -1;
  else
    aste->x_move = 0;

  rand_number = rand() % 3;
  if (rand_number == 0)
    aste->y_move = 1;
  else if (rand_number == 1)
    aste->y_move = -1;
  else
    aste->y_move = 0;
}

void initBullet(celestial_object *bullet, int size,  SDL_Surface **surfaces)
{
  indice id;
  
  bullet->speed = 5.;

  if (size == SMALL)
    bullet->sprite_size = 8;
  else if (size == BIG)
    bullet->sprite_size = 16;

  bullet->nb_of_sprite = 1;

  if (size == SMALL)
    bullet->surface = surfaces[id = iBULLET];
  else if (size == BIG)
    bullet->surface = surfaces[id = iBIG_BULLET];

  bullet->rcSrc.x = 0;
  bullet->rcSrc.y = 0;
  bullet->rcSrc.w = bullet->sprite_size;
  bullet->rcSrc.h = bullet->sprite_size;

  bullet->life_span = 0;
}

  void initExplosion(celestial_object *explosion, SDL_Surface **surfaces)
{
  indice id;
  
  explosion->position.x = 0;
  explosion->position.y = 0;

  explosion->sprite_size = 64;
  explosion->nb_of_sprite = 25;

  explosion->rcSrc.x = -64;
  explosion->rcSrc.y = 0;
  explosion->rcSrc.h = explosion->sprite_size;;
  explosion->rcSrc.w = explosion->sprite_size;;

  explosion->surface = surfaces[id = iEXPLOSION];
  
  explosion->isExplosionOfSpaceship = false;

  
}

void initProtection(celestial_object *protection, SDL_Surface **surfaces)
{
  indice id;

  protection->position.x = 0;
  protection->position.y = 0;

  protection->surface = surfaces[id = iPROTECTION];
}
