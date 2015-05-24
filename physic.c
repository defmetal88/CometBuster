
#include "physic.h"
#include "graph.h"



extern bool gameover;
extern bool quit;
extern int score;
extern bool spaceship_state;
extern Mix_Chunk *noiseexplosion;

int my_round(double a)
{
  int ret;
  
  ret = (int) a;
  if (a - (double) ret >= 0.5)
    ret += 1;
  return ret;
}

/* sets up a space ring */
void toroidal_space(celestial_object *obj)
{
  if ((obj->position.x + obj->rcSrc.w) > SCREEN_WIDTH)
    obj->position.x = 0;
  else if (obj->position.x < 0)
    obj->position.x = SCREEN_WIDTH - obj->rcSrc.w;
  if ((obj->position.y + obj->rcSrc.h) > SCREEN_HEIGHT)
    obj->position.y = obj->rcSrc.h;
  else if (obj->position.y < 0)
    obj->position.y = SCREEN_HEIGHT - obj->rcSrc.h;
}

/* calculate x/y_move the spaceship */
void calculate_move(celestial_object *obj, int direction)
{
  int deg;
  double cos_rad, sin_rad;
  
  /* Angle in degrees */
  deg = (obj->rcSrc.x / obj->sprite_size) * 10; 
  
  /* Conversion to radians */
  cos_rad = cos((M_PI * deg) / 180);     
  sin_rad = sin((M_PI * deg) / 180);
  
  if (direction == FORWARD) {
    obj->x_move += cos_rad;
    obj->y_move += -sin_rad;

    obj->speed = fabsf(obj->x_move) + fabsf(obj->y_move);
    if (obj->speed > MAX_SPEED) {
      obj->x_move -= cos_rad;
      obj->y_move -= -sin_rad;
    }
  }

  if (direction == BACK) {
    obj->x_move -= cos_rad;
    obj->y_move -= -sin_rad;

    obj->speed = fabsf(obj->x_move) + fabsf(obj->y_move);
    if (obj->speed > MAX_SPEED) {
      obj->x_move += cos_rad;
      obj->y_move += -sin_rad;
    }
  }

}

void calculate_shot(celestial_object *spaceship, celestial_object *bullet)
{
  int deg;
  double cos_rad, sin_rad;

  /* Angle in degrees */
  deg = (spaceship->rcSrc.x / spaceship->sprite_size) * 10; 
  
  /* Conversion to radians */
  cos_rad = cos((M_PI * deg) / 180);     
  sin_rad = sin((M_PI * deg) / 180);

  /* Multiplication for rounding precision */
  bullet->x_move = cos_rad;	
  bullet->y_move = sin_rad; 
}

void move_spaceship(celestial_object *obj)
{
  obj->position.x += my_round(obj->x_move);
  obj->position.y += my_round(obj->y_move);

  toroidal_space(obj);
}

void move_asteroids(list asteroid_list)
{
  while (!is_empty(asteroid_list))
    {
      if (asteroid_list->object.direction_of_rotation == LEFT)
	sprite_turn_left(&asteroid_list->object);
      else 
	sprite_turn_right(&asteroid_list->object);
     
      asteroid_list->object.position.x += round(asteroid_list->object.x_move * asteroid_list->object.speed);
      asteroid_list->object.position.y += round(asteroid_list->object.y_move * asteroid_list->object.speed);
     
      toroidal_space(&asteroid_list->object);
      
      asteroid_list = tail(asteroid_list);
    }
}

void move_bullet(list bullet_list)
{
  while (!is_empty(bullet_list))
    {
      bullet_list->object.position.x += my_round(bullet_list->object.x_move * bullet_list->object.speed);
      bullet_list->object.position.y -= my_round(bullet_list->object.y_move * bullet_list->object.speed);

      toroidal_space(&bullet_list->object);
      bullet_list->object.life_span += 1;      
      bullet_list = tail(bullet_list);
    }
}

void check_bullet_life_span(list *L)
{
  list tmp = *L;
  
  while (!is_empty(tmp)) {
    if (tmp->object.life_span > BULLET_LIFE_SPAN) {
      delete(tmp, L);
    }
    tmp = tail(tmp);
  }
}

void fire(list *bullet_list, celestial_object *spaceship, celestial_object *bullet)
{
  calculate_shot(spaceship, bullet);
  bullet->position.x = spaceship->position.x + (spaceship->rcSrc.w / 2) - (bullet->rcSrc.w / 2);
  bullet->position.y = spaceship->position.y + (spaceship->rcSrc.h / 2) - (bullet->rcSrc.h / 2);
  *bullet_list = push(*bullet, *bullet_list);  
}

bool collision(celestial_object *obj1, celestial_object *obj2, SDL_Surface **surfaces)
{
  if (obj1 == NULL || obj2 == NULL)
    return false;
  if ((obj1->position.x >= obj2->position.x && obj1->position.x <= (obj2->position.x + obj2->sprite_size))
      || ((obj1->position.x + obj1->sprite_size) >= obj2->position.x && (obj1->position.x + obj1->sprite_size) <= (obj2->position.x + obj2->sprite_size))
			|| (obj2->position.x >= obj1->position.x && obj2->position.x <= (obj1->position.x + obj1->sprite_size))
      || ((obj2->position.x + obj2->sprite_size) >= obj1->position.x && (obj2->position.x + obj2->sprite_size) <= (obj1->position.x + obj1->sprite_size)))
    {
			if ((obj1->position.y >= obj2->position.y && obj1->position.y <= (obj2->position.y + obj2->sprite_size))
					|| ((obj1->position.y + obj1->sprite_size) >= obj2->position.y && (obj1->position.y + obj1->sprite_size) <= (obj2->position.y + obj2->sprite_size))
					|| (obj2->position.y >= obj1->position.y && obj2->position.y <= (obj1->position.y + obj1->sprite_size))
					|| ((obj2->position.y + obj2->sprite_size) >= obj1->position.y && (obj2->position.y + obj2->sprite_size) <= (obj1->position.y + obj1->sprite_size)))
			{
				return per_pixel_collision(obj1, obj2, surfaces);
			}
    }
	return false;
}

void check_spaceship_collision(celestial_object *spaceship, list *asteroid_list, list *explosion_list, SDL_Surface **surfaces)
{
  list ast_tmp = *asteroid_list;
  celestial_object explosion;
  
  initExplosion(&explosion, surfaces);
  
  while (!is_empty(ast_tmp)) {
    if (collision(spaceship, &ast_tmp->object, surfaces)) {
      explosion.position.x = ast_tmp->object.position.x;
      explosion.position.y = ast_tmp->object.position.y;
      Mix_PlayChannel(2,noiseexplosion, 0);
      explosion.isExplosionOfSpaceship = true;
      *explosion_list = push(explosion, *explosion_list);
      destroy_asteroid(ast_tmp->object, asteroid_list, surfaces);
      delete(ast_tmp, asteroid_list);
      spaceship_state = DESTROY;
      
      return;
    }
    ast_tmp = tail(ast_tmp);
  }
}

void check_bullet_asteroid_collision(list *bullet_list, list *asteroid_list, list *explosion_list, SDL_Surface **surfaces)
{
	list bul_tmp = *bullet_list;
	list ast_tmp = *asteroid_list;
	celestial_object explosion;

	initExplosion(&explosion, surfaces);

	if (!is_empty(ast_tmp) && !is_empty(bul_tmp)) {
		while (!is_empty(ast_tmp)) {
			while (!is_empty(bul_tmp)) {
				if (collision(&bul_tmp->object, &ast_tmp->object, surfaces)) {
					// we create 3 new aste if ast_tmp is medium or bigger
					Mix_PlayChannel(2,noiseexplosion, 0);
					explosion.position.x = ast_tmp->object.position.x - 80;
					explosion.position.y = ast_tmp->object.position.y - 10 ;
					*explosion_list = push(explosion, *explosion_list);
					destroy_asteroid(ast_tmp->object, asteroid_list, surfaces);

					delete(ast_tmp, asteroid_list);
					delete(bul_tmp, bullet_list);
					ast_tmp = *asteroid_list;
					bul_tmp = *bullet_list;
				}
				bul_tmp = tail(bul_tmp);
			}
			ast_tmp = tail(ast_tmp);
			bul_tmp = *bullet_list;
		}
	}
}

void destroy_asteroid(celestial_object aste_destroy, list *asteroid_list, SDL_Surface **surfaces)
{
  celestial_object aste;
  int i, num;

  if (aste_destroy.sprite_size == BIG) {
    score += 10;
  }
  else if (aste_destroy.sprite_size == MEDIUM) {
    score += 20;
  }
  else {
    score += 30;
  }

  if (aste_destroy.sprite_size != SMALL) {
    for (i = 0; i < 3; i++) {
      if (aste_destroy.sprite_size == BIG) 
        initAsteroid(&aste, MEDIUM, surfaces);
      if (aste_destroy.sprite_size == MEDIUM) 
        initAsteroid(&aste, SMALL, surfaces);

      num = rand() % 3;
      if (num == 0) {
        aste.position.x = aste_destroy.position.x + 10;
      }
      else if (num == 1) {
        aste.position.x = aste_destroy.position.x - 10;
      }
      else {
        aste.position.x = aste_destroy.position.x;
      } 
      num = rand() % 3;
      if (num == 0) {
        aste.position.y = aste_destroy.position.y + 10;
      }
      else if (num == 1) {
        aste.position.y = aste_destroy.position.y - 10;
      }
      else {
        aste.position.y = aste_destroy.position.y;
      }
      *asteroid_list = push(aste, *asteroid_list);
    }
  }
}

bool per_pixel_collision(celestial_object *obj1, celestial_object *obj2, SDL_Surface **surfaces)
{
	int i, j;
	int offsetx1, offsety1, offsetx2, offsety2;
	SDL_Rect rect;
	SDL_Surface *screen, *surface1, *surface2;
	Uint8 r1, r2, g1, g2, b1, b2;
	bool ret;
	indice id;

	screen = surfaces[0];
	surface1 = obj1->surface;
	surface2 = obj2->surface;  
	ret = false;

	if (obj1->position.x >= obj2->position.x)
	{
		rect.x = obj1->position.x;
		rect.w = obj2->position.x + obj2->sprite_size - rect.x;
		if (rect.w > obj1->sprite_size)
			rect.w = obj1->sprite_size;
		offsetx1 = 0;
		offsetx2 = rect.x - obj2->position.x;
	}
	else {
		rect.x = obj2->position.x;
		rect.w = obj1->position.x + obj1->sprite_size - rect.x;
		if (rect.w > obj2->sprite_size)
			rect.w = obj2->sprite_size;
		offsetx2 = 0;
		offsetx1 = rect.x - obj1->position.x;
	}

	if (obj1->position.y >= obj2->position.y)
	{
		rect.y = obj1->position.y;
		rect.h = obj2->position.y + obj2->sprite_size - rect.y;
		if (rect.h > obj1->sprite_size)
			rect.h = obj1->sprite_size;
		offsety1 = 0;
		offsety2 = rect.y - obj2->position.y;
	}
	else {
		rect.y = obj2->position.y;
		rect.h = obj1->position.y + obj1->sprite_size - rect.y;
		if (rect.h > obj2->sprite_size)
			rect.h = obj2->sprite_size;
		offsety2 = 0;
		offsety1 = rect.y - obj1->position.y;
	}

	SDL_LockSurface(surface1);
	SDL_LockSurface(surface2);

	for (j = 0; j < rect.h; j++) {
		for (i = 0; i < rect.w; i++) {
			SDL_GetRGB(pixel(surface1, i + obj1->rcSrc.x + offsetx1, j + offsety1), screen->format, &r1, &g1, &b1);
			SDL_GetRGB(pixel(surface2, i + obj2->rcSrc.x + offsetx2, j + offsety2), screen->format, &r2, &g2, &b2);

			if (!isColorkey(r1, g1, b1) && !isColorkey(r2, g2, b2)) {
				ret = true;
			}
		}
	}

	SDL_UnlockSurface(surface1);
	SDL_UnlockSurface(surface2);

	return ret;
}

Uint32 pixel(SDL_Surface *surface, int x, int y)
{
	Uint32 *pixels;
	Uint32 p;

	pixels = (Uint32 *) surface->pixels;
	p =  pixels[(y * surface->w) + x];

	return p;
}

bool isColorkey(Uint8 r, Uint8 g, Uint8 b)
{
	if (r == 255 && g == 0 && b == 255) {
		return true;
	}
	if (r == 0 && g == 255 && b == 255) {
		return true;
	}
	if (r == 255 && g == 125 && b == 0) {
		return true;
	}
	return false;
}
