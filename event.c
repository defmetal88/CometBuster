#include "event.h"
#include "graph.h"
#include "physic.h"
#include "MusicManagement.h"
#include "keyboard.h"
#include <SDL/SDL_mixer.h>

extern Mix_Music *this_is_sparta;
extern Mix_Music *Back_In_Black_8_bit;
extern Mix_Music *Game_of_Thrones_8_bit;
extern Mix_Music *gameovermusic;
extern Mix_Music *pausemusic;
extern Mix_Music *titlemusic;
extern Mix_Music *mainmusic;
extern Mix_Music *epicbattle;
extern Mix_Music *battle3;
extern Mix_Music *battle4;
extern Mix_Music *battle5;
extern Mix_Chunk *laser;
extern Mix_Chunk *noiseexplosion;
extern int time_begin_invincibility;
extern int NB_OF_ASTEROID_AT_STARTUP;
extern int level;
extern int randommusic;
extern int choicememory;
extern int choice;
extern int choicemusic;
extern bool training;
extern bool gameover;
extern bool quit;
extern bool godmod;
extern bool desactivatescore;
extern int spaceship_state;
extern gamestates state;
extern bool pause;

void HandleEvent(SDL_Event event, celestial_object *spaceship, list *bullet_list, celestial_object *bullet, celestial_object *big_bullet, Uint8 *keystates,list *asteroid_list, int *delay_array)
{

  if (keystates[SDLK_BACKSPACE]){
    gameover=true;
    state=init;
  }

  /* ################# MENU ################# */
  if (state == menu) {

    if (keystates[SDLK_UP]){
      choice = 0;
    }
    else if (keystates[SDLK_DOWN]){
      choice = 1;
    }
    else if (keystates[SDLK_LEFT]){
      choice = 2;
    }
    else if (keystates[SDLK_RIGHT]){
      choice = 3;
    }


    if (keystates[SDLK_RETURN] && choice==0) {
      spaceship_state = INVINCIBLE;
      time_begin_invincibility = SDL_GetTicks();
      state = init;
      Mix_HaltMusic();
    }

    else if (keystates[SDLK_RETURN] && choice==1) {
      quit = true;
    }
    else if (keystates[SDLK_RETURN] && choice==2){
      training=true;
      gameover=false;
      level=0;
      NB_OF_ASTEROID_AT_STARTUP=2;
      state=init;
    }

    else if (keystates[SDLK_RETURN] && choice==3) {
      Mix_HaltMusic();
      state=music;
    }

  }


  /* #################### MOD #################### */

      if(state == mod){
	//en construction
      }


  /* ################# MUSIC ################# */
  if(state==music){

    readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);

    if (delay_array[K_UP] == GO && keystates[SDLK_UP]){
      Mix_HaltMusic();
      choicemusic = choicemusic-1;
      readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);
      if (choicemusic<1){
	choicemusic=6;
      }
    }
    else if (delay_array[K_DOWN] == GO && keystates[SDLK_DOWN]){
      Mix_HaltMusic();
      choicemusic = choicemusic+1;
      readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);

      if (choicemusic>6){
	choicemusic=1;
	Mix_PlayMusic(mainmusic, 0);
      }
    }
    choicememory=choicemusic;
  }
  /* ################# PLAY ################# */

  if(state==play){

    if (!pause) {

      /* Shoot */
      if (keystates[SDLK_SPACE] && (spaceship_state != DESTROY)) {
        if (godmod) {
          fire(bullet_list, spaceship, big_bullet);
          Mix_PlayChannel(1, laser, 0);
        }
        
        if (delay_array[K_SPACE] == GO) {
          fire(bullet_list, spaceship, bullet);
          Mix_PlayChannel(1, laser, 0);
        }
      }


      /* go forward right */
      if (delay_array[K_UP] == GO && delay_array[K_RIGHT] == GO && keystates[SDLK_UP] && keystates[SDLK_RIGHT]) {
        sprite_turn_left(spaceship);
        calculate_move(spaceship, FORWARD);
      }

      /* go forward left */
      else if (delay_array[K_UP] == GO && delay_array[K_LEFT] == GO && keystates[SDLK_UP] && keystates[SDLK_LEFT]) {
        sprite_turn_right(spaceship);
        calculate_move(spaceship, FORWARD);
      }

      /* go forward */
      else if (delay_array[K_UP] == GO && keystates[SDLK_UP]) {
        calculate_move(spaceship, FORWARD);
      }

      /* go back left */
      else if (delay_array[K_DOWN] == GO && delay_array[K_LEFT] == GO && keystates[SDLK_DOWN] && keystates[SDLK_LEFT]) {
        sprite_turn_right(spaceship);
        calculate_move(spaceship, BACK);
      }

      /* go back right */
      else if (delay_array[K_DOWN] == GO && delay_array[K_RIGHT] == GO && keystates[SDLK_DOWN] && keystates[SDLK_RIGHT]) {
        sprite_turn_left(spaceship);
        calculate_move(spaceship, BACK);
      }

      /* go back */
      else if(delay_array[K_DOWN] == GO && keystates[SDLK_DOWN]) {
        calculate_move(spaceship, BACK);
      }


      /* go left on the spaceship's sprite */
      else if (delay_array[K_RIGHT] && keystates[SDLK_RIGHT]) {
        sprite_turn_left(spaceship);
      }

      /* go right on the spaceship's sprite */
      else if (delay_array[K_LEFT] && keystates[SDLK_LEFT]) {
        sprite_turn_right(spaceship);
      }

      /* invicible mod */
      if (delay_array[K_i] == GO && keystates[SDLK_i]){
        godmod = !godmod;
        desactivatescore = !desactivatescore;
        if (godmod) {
          Mix_HaltMusic();
          Mix_PlayMusic(this_is_sparta, -1);
        }
        else {
          Mix_HaltMusic();
          readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);
        }
      }

      /*win mod*/
      if (delay_array[K_w] == GO && keystates[SDLK_w]){
        list_free(asteroid_list);
      }

    }

    if (keystates[SDLK_p]){
      pause = true;
      Mix_PauseMusic();
    }

    if (keystates[SDLK_RETURN] && pause) {
      pause = false;
      Mix_ResumeMusic();
    }

  }
  /* ################# END ################# */
  if(state==end){

    if (keystates[SDLK_RETURN]){
      Mix_HaltMusic();
      state=init;
    }
  }


  switch (event.type) {

  case SDL_QUIT:
    quit = true;
    break;

  case SDL_KEYDOWN:

    switch (event.key.keysym.sym) {

      /* quit when press press escape or q */
    case SDLK_ESCAPE:
      quit = true;
      break;
    case SDLK_q:
      quit = true;
      break;

      /* nothing to do for other keys */
    default:
      break;
    }
  }
}

