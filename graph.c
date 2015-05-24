#include "graph.h"

void sprite_turn_left(celestial_object *obj)
{
  obj->rcSrc.x -= obj->sprite_size;
  if (obj->rcSrc.x < 0)
    obj->rcSrc.x = obj->nb_of_sprite * obj->sprite_size - obj->sprite_size;
}

void sprite_turn_right(celestial_object *obj)
{
  obj->rcSrc.x += obj->sprite_size;
  if (obj->rcSrc.x > (obj->nb_of_sprite * obj->sprite_size) - obj->sprite_size)
    obj->rcSrc.x = 0;
}

int explosion_sprite_changer(list *explosion_list)
{
  bool ret = 1;
  list exp_tmp = *explosion_list;
  
  
  while (!is_empty(exp_tmp)) {
    exp_tmp->object.rcSrc.x += exp_tmp->object.sprite_size;

    if (exp_tmp->object.rcSrc.x == (exp_tmp->object.nb_of_sprite * exp_tmp->object.sprite_size)) {
      if (exp_tmp->object.isExplosionOfSpaceship)
        ret = 0;
      delete(exp_tmp, explosion_list);
      exp_tmp = *explosion_list;

    }
    exp_tmp = tail(exp_tmp);
  }
  return ret;
}

void loadFont(TTF_Font **font, TTF_Font **fonttitle, TTF_Font **fonttitle2, TTF_Font **fontgameover, TTF_Font **fontwin, TTF_Font **fontlevel, TTF_Font **fontscore)
{
  *font = TTF_OpenFont("space_age.ttf", 20);
  *fonttitle = TTF_OpenFont("space_age.ttf", 60);
  *fonttitle2 = TTF_OpenFont("space_age.ttf", 50);
  *fontgameover = TTF_OpenFont("space_age.ttf", 90);
  *fontwin = TTF_OpenFont("space_age.ttf", 50);
  *fontlevel = TTF_OpenFont("space_age.ttf", 40);
  *fontscore = TTF_OpenFont("space_age.ttf", 40);
}

void freeFonts(TTF_Font *font, TTF_Font *fonttitle, TTF_Font *fonttitle2, TTF_Font *fontgameover, TTF_Font *fontwin, TTF_Font *fontlevel, TTF_Font *fontscore)
{
	TTF_CloseFont(font);
	TTF_CloseFont(fonttitle);
	TTF_CloseFont(fonttitle2);
	TTF_CloseFont(fontgameover);
	TTF_CloseFont(fontwin);
	TTF_CloseFont(fontlevel);
	TTF_CloseFont(fontscore);
}

void printText(char *str, int x, int y, TTF_Font *font, SDL_Color color, SDL_Surface *screen)
{
	SDL_Surface *text;
	SDL_Rect position;	

	text = TTF_RenderText_Blended(font, str, color);
	position.x = x;
	position.y = y;
	
	SDL_BlitSurface(text, NULL, screen, &position);

	SDL_FreeSurface(text);
}

void printMainMenu(int choice, TTF_Font *fonttitle,TTF_Font *fonttitle2, SDL_Color white, SDL_Color red, SDL_Surface *screen)
{
	printText("COMETBUSTER", 20, 4, fonttitle, white, screen);

	if(choice==0){
		printText("> START", 200, 100, fonttitle, red, screen); 
		printText ("TRAINING", 2, 250, fonttitle2, white, screen);
		printText("MUSIC", 400, 250, fonttitle2, white, screen);
		printText("QUIT", 200, 400, fonttitle, white, screen);
	}

	if (choice==1){
		printText("START", 200, 100, fonttitle, white, screen); 
		printText ("TRAINING", 2, 250, fonttitle2, white, screen);
		printText("MUSIC", 400, 250, fonttitle2, white, screen);
		printText("> QUIT", 200, 400, fonttitle, red, screen);
	}

	if (choice==2){
		printText("START", 200, 100, fonttitle, white, screen); 
		printText ("> TRAINING", 2, 250, fonttitle2, red, screen);
		printText("MUSIC", 400, 250, fonttitle2, white, screen);
		printText("QUIT", 200, 400, fonttitle, white, screen);

	}
	if (choice==3){
		printText("START", 200, 100, fonttitle, white, screen); 
		printText ("TRAINING", 2, 250, fonttitle2, white, screen);
		printText("> MUSIC", 400, 250, fonttitle2, red, screen);
		printText("QUIT", 200, 400, fonttitle, white, screen);
	}

}
  
void printMusicMenu(int choicemusic, TTF_Font *fonttitle, SDL_Color blue, SDL_Color white, SDL_Surface *screen)
{
	if(choicemusic==1){
		printText("1: > mainmusic", 2, 25, fonttitle, blue, screen);
		printText("2: epicbattle", 2, 100, fonttitle, white, screen);
		printText("3: BATTLE3", 2, 175, fonttitle, white, screen);
		printText("4: BATTLE4", 2, 250, fonttitle, white, screen);
		printText("5: BATTLE5", 2, 325, fonttitle, white, screen);
		printText("6: RANDOM", 2, 400, fonttitle, white, screen); 
	}

	if(choicemusic==2){
		printText("1: mainmusic", 2, 25, fonttitle, white, screen);
		printText("2: > epicbattle", 2, 100, fonttitle, blue, screen);
		printText("3: BATTLE3", 2, 175, fonttitle, white, screen);
		printText("4: BATTLE4", 2, 250, fonttitle, white, screen);
		printText("5: BATTLE5", 2, 325, fonttitle, white, screen);
		printText("6: RANDOM", 2, 400, fonttitle, white, screen); 
	}

	if(choicemusic==3){
		printText("1: mainmusic", 2, 25, fonttitle, white, screen);
		printText("2: epicbattle", 2, 100, fonttitle, white, screen);
		printText("3: > BATTLE3", 2, 175, fonttitle, blue, screen);
		printText("4: BATTLE4", 2, 250, fonttitle, white, screen);
		printText("5: BATTLE5", 2, 325, fonttitle, white, screen);
		printText("6: RANDOM", 2, 400, fonttitle, white, screen); 
	}

	if(choicemusic==4){
		printText("1: mainmusic", 2, 25, fonttitle, white, screen);
		printText("2: epicbattle", 2, 100, fonttitle, white, screen);
		printText("3: BATTLE3", 2, 175, fonttitle, white, screen);
		printText("4: > BATTLE4", 2, 250, fonttitle, blue, screen);
		printText("5: BATTLE5", 2, 325, fonttitle, white, screen);
		printText("6: RANDOM", 2, 400, fonttitle, white, screen); 
	}

	if(choicemusic==5){
		printText("1: mainmusic", 2, 25, fonttitle, white, screen);
		printText("2: epicbattle", 2, 100, fonttitle, white, screen);
		printText("3: BATTLE3", 2, 175, fonttitle, white, screen);
		printText("4: BATTLE4", 2, 250, fonttitle, white, screen);
		printText("5: > BATTLE5", 2, 325, fonttitle, blue, screen);
		printText("6: RANDOM", 2, 400, fonttitle, white, screen); 
	}

	if(choicemusic==6){
		printText("1: mainmusic", 2, 25, fonttitle, white, screen);
		printText("2: epicbattle", 2, 100, fonttitle, white, screen);
		printText("3: BATTLE3", 2, 175, fonttitle, white, screen);
		printText("4: BATTLE4", 2, 250, fonttitle, white, screen);
		printText("5: BATTLE5", 2, 325, fonttitle, white, screen);
		printText("6: > RANDOM", 2, 400, fonttitle, blue, screen); 
	}

}







