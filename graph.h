#ifndef GRAPH_H
#define GRAPH_H

#include "SDL/SDL.h"
#include "main.h"
#include "list.h"


void sprite_turn_left(celestial_object *obj);
void sprite_turn_right(celestial_object *obj);
int explosion_sprite_changer(list *explosion_list);
void setColorKey(SDL_Surface **surfaces);
void loadFont(TTF_Font **font,
	      TTF_Font **fonttitle,
	      TTF_Font **fonttitle2,
	      TTF_Font **fontgameover,
	      TTF_Font **fontwin,
	      TTF_Font **fontlevel,
	      TTF_Font **fontscore); 	

void freeFonts(TTF_Font *font, TTF_Font *fonttitle, TTF_Font *fonttitle2, TTF_Font *fontgameover, TTF_Font *fontwin, TTF_Font *fontlevel, TTF_Font *fontscore);
void printText(char *str, int x, int y, TTF_Font *font, SDL_Color color, SDL_Surface *screen);
void printMusicMenu(int choicemusic,TTF_Font *fonttitle, SDL_Color blue, SDL_Color white, SDL_Surface *screen);
void printMainMenu(int choice, TTF_Font *fonttitle,TTF_Font *fonttitle2, SDL_Color white, SDL_Color red, SDL_Surface *screen);
#endif
