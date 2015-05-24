#include "main.h"
#include "physic.h"
#include "graph.h"
#include "event.h"
#include "init.h"
#include "list.h"
#include "global.h"
#include "keyboard.h"
#include "MusicManagement.h"

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
extern int choice;
extern int choicemusic;
extern int choicememory;
extern bool training;
extern bool gameover;
extern bool desactivatescore;
extern bool quit;
extern int score;
extern int spaceship_state;
bool godmod;
bool showlevel;
bool norepeat;
extern bool pause;

void blit_celestial_object(SDL_Surface *screen,
    celestial_object spaceship,
    list asteroid_list,
    list bullet_list,
    list explosion_list,
    celestial_object protection);

int main(int argc, char **argv)
{
  SDL_Surface *surfaces[NUMBER_OF_SURFACES];
  SDL_Rect rcSpace;

  int live;
  TTF_Font *font = NULL;
  TTF_Font *fontscore = NULL;
  TTF_Font *fontlevel = NULL;
  TTF_Font *fonttitle = NULL;
  TTF_Font *fonttitle2 = NULL;
  TTF_Font *fontgameover = NULL;
  TTF_Font *fontwin = NULL;
  SDL_Color white = {255, 255, 255, 0};
  SDL_Color red = {255, 0, 0, 0};
  SDL_Color blue = {38, 196, 236, 0};
  SDL_Color green = {0, 255, 0, 0};

  int time_now;
  int time_before;
  int time_game;
  int i;
  int colorkey;
  char textlevel[20];
  char textlive[10];
  char texttime[30];
  char textscore[50];

  int delay_array[NB_OF_KEYS];
  int press_date[NB_OF_KEYS];

  indice id;

  list asteroid_list;
  list bullet_list;
  list explosion_list;

  celestial_object spaceship;
  celestial_object aste;
  celestial_object bullet;
  celestial_object explosion;
  celestial_object protection;
  celestial_object big_bullet;

  /* Initialize SDL and TTF */
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  /* Set the title bar */
  SDL_WM_SetCaption("Comet Busters", "Comet Busters");


  /* Initialize variables */
  srand(time(NULL));

  randommusic=1+rand()%5;
  time_now = 0;
  time_before = 0;
  time_begin_invincibility = 0;
  live = 5;
  level = 0;
  choicememory=0;
  NB_OF_ASTEROID_AT_STARTUP = 3;
  training=false;
  gameover = true;
  quit = false;
  godmod=false;
  choice = 0;
  choicemusic=1;
  spaceship_state = DESTROY;
  score = 0;
  state = init;
  showlevel=false;
  desactivatescore=false;
  sprintf(textlevel,"LEVEL: %d",level);
  norepeat=false;

  for (i = 0; i < NUMBER_OF_SURFACES; i++)
    surfaces[i] = NULL;

  /* Create windows */
  surfaces[id = iSCREEN] = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* Load BMPs */
  surfaces[id = iSPACE] = SDL_LoadBMP("space.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iSPACESHIP] = SDL_LoadBMP("spaceship.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iSMALL_ASTE] = SDL_LoadBMP("small_asteroid.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iMEDIUM_ASTE] = SDL_LoadBMP("medium_asteroid.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);
  surfaces[id = iBIG_ASTE] = SDL_LoadBMP("big_asteroid.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iBULLET] = SDL_LoadBMP("bullet.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iEXPLOSION] = SDL_LoadBMP("explosion.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iPROTECTION] = SDL_LoadBMP("bubble_protection.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  surfaces[id = iBIG_BULLET] = SDL_LoadBMP("big_bullet.bmp");
  surfaces[id] = SDL_DisplayFormat(surfaces[id]);

  /* load font*/
  loadFont(&font, &fonttitle, &fonttitle2, &fontgameover, &fontwin, &fontlevel, &fontscore);

  /* Set color key */
  colorkey = SDL_MapRGB(surfaces[id = iSCREEN]->format, 255, 0, 255);
  SDL_SetColorKey(surfaces[id = iSPACESHIP], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_SetColorKey(surfaces[id = iEXPLOSION], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  colorkey = SDL_MapRGB(surfaces[id = iSCREEN]->format, 0, 255, 255);

  SDL_SetColorKey(surfaces[id = iSMALL_ASTE], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_SetColorKey(surfaces[id = iMEDIUM_ASTE], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_SetColorKey(surfaces[id = iBIG_ASTE], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  colorkey = SDL_MapRGB(surfaces[id = iSCREEN]->format, 255, 125, 0);

  SDL_SetColorKey(surfaces[id = iBULLET], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_SetColorKey(surfaces[id = iBIG_BULLET], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  colorkey = SDL_MapRGB(surfaces[id = iSCREEN]->format, 0, 0, 0);
  
  SDL_SetColorKey(surfaces[id = iPROTECTION], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /*initialize and load sound*/

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
  {
    printf("%s", Mix_GetError());
  }

  this_is_sparta = Mix_LoadMUS("this_is_sparta.mp3");
  Back_In_Black_8_bit = Mix_LoadMUS("Back_In_Black_8_bit.mp3");
  Game_of_Thrones_8_bit = Mix_LoadMUS("Game_of_Thrones_8_bit.mp3");
  gameovermusic = Mix_LoadMUS("gameovermusic.mp3");
  titlemusic = Mix_LoadMUS("titlemusic.mp3");
  pausemusic = Mix_LoadMUS("pausemusic.mp3");
  mainmusic = Mix_LoadMUS("mainmusic.mp3");
  epicbattle = Mix_LoadMUS("epicbattle.mp3");
  battle3 = Mix_LoadMUS("battle3.mp3");
  battle4 = Mix_LoadMUS("battle4.mp3");
  battle5 = Mix_LoadMUS("battle5.mp3");

  Mix_AllocateChannels(10);

  laser = Mix_LoadWAV("laser.wav");
  noiseexplosion = Mix_LoadWAV("explosion.wav");

  for (i = 0; i < NB_OF_KEYS; i++) { 
    delay_array[i] = 0;
    press_date[i] = SDL_GetTicks();
  }

  rcSpace.x = 0;
  rcSpace.y = 0;

  asteroid_list = new_list();
  bullet_list = new_list();
  explosion_list = new_list();

  initSpaceship(&spaceship, surfaces);
  initBullet(&bullet, SMALL, surfaces);
  initBullet(&big_bullet, BIG, surfaces);
  initExplosion(&explosion, surfaces);
  initProtection(&protection, surfaces);

  /* ######################### MAIN LOOP  #########################*/
  while (!quit) {

    SDL_Event event;
    Uint8 *keystates = SDL_GetKeyState( NULL );
    time_now = SDL_GetTicks();

    /* 30 FPS */
    if (time_now - time_before > 24) {
      /* update keystates */
      SDL_PumpEvents();
      delay(delay_array, press_date, keystates);
      /* Look for an event */
      if (SDL_PollEvent(&event) || keyPressed(keystates)) {
        HandleEvent(event, &spaceship, &bullet_list, &bullet, &big_bullet, keystates,&asteroid_list, delay_array);
      }

      /* Draw background on screen */
      SDL_BlitSurface(surfaces[id = iSPACE], NULL, surfaces[id = iSCREEN], &rcSpace);
      
      /* #################### MOD #################### */

      if(state == mod){
	//en construction
      }


      /* #################### MUSIC #################### */

      if(state == music) {
        printMusicMenu(choicemusic, fonttitle,blue, white, surfaces[id = iSCREEN]);
      }

      /* #################### INIT #################### */

      if (state == init){
        list_free(&asteroid_list);

        if (gameover==true)
        {
          live = 5;
          score = 0;
          level = 0;
          NB_OF_ASTEROID_AT_STARTUP=2;
          for (i = 0; i < NB_OF_ASTEROID_AT_STARTUP; i++) {
            initAsteroid(&aste, BIG, surfaces);
            asteroid_list = push(aste, asteroid_list);
          }
          gameover=false;
          Mix_PlayMusic(Game_of_Thrones_8_bit, -1);
          state=menu;
        }
        else
        {
          level++;

          NB_OF_ASTEROID_AT_STARTUP++;

          for (i = 0; i < NB_OF_ASTEROID_AT_STARTUP; i++) {
            initAsteroid(&aste, BIG, surfaces);
            asteroid_list = push(aste, asteroid_list);
          }
          spaceship_state = ALIVE;

          choicememory=choicemusic;
          if (norepeat==false){
            readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);
          }
          else if(choicemusic==6){
            choicememory=choicemusic;
            randommusic=1+rand()%5;
            choicemusic=randommusic;
            readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);
          }
          spaceship_state = INVINCIBLE;
          time_begin_invincibility = SDL_GetTicks();
          showlevel=true;
          state=play;

        }
      }

      /* #################### MENU #################### */
      if (state == menu) { 
        list_free(&asteroid_list);
        list_free(&bullet_list);
        list_free(&explosion_list);
        spaceship_state = DESTROY;
        list_free(&bullet_list);
        printMainMenu(choice, fonttitle,fonttitle2, white, red, surfaces[id = iSCREEN]);
      }

      /* #################### PLAY #################### */
      if (state == play && !pause) {

        if(Mix_PlayingMusic()==0){
          if (choicememory==6){
            randommusic=1+rand()%5;
            choicemusic=randommusic;
            readmusic(choicemusic,mainmusic,epicbattle,battle3,battle4,battle5);
          }
          else {
            Mix_RewindMusic();
          }
        }

        if (showlevel==true){
          printText(textlevel, 40, 50, fontgameover, green, surfaces[id = iSCREEN]);
        }


        if (spaceship_state == INVINCIBLE && SDL_GetTicks() - time_begin_invincibility > TIME_INVINCIBILITY)
        {
          showlevel=false;
          spaceship_state = ALIVE;
        }

        protection.position.x = spaceship.position.x - 10;
        protection.position.y = spaceship.position.y - 10;
        if (godmod==true){
          spaceship_state = INVINCIBLE;
          printText("Invincible", 250, 60, font, green, surfaces[id = iSCREEN]);
        }

        if (spaceship_state != DESTROY) {
          move_spaceship(&spaceship);
          if (spaceship_state != INVINCIBLE){
            check_spaceship_collision(&spaceship, &asteroid_list, &explosion_list, surfaces);
          }
        }
        /* return 0 means that the explosion of the spaceship is finished */
        if (explosion_sprite_changer(&explosion_list) == 0) {
          spaceship_state = INVINCIBLE;
          time_begin_invincibility = SDL_GetTicks();
          if (training==false){
            live--;
          }
          initSpaceship(&spaceship, surfaces);
        }

        /* check the invincibility duration */
        if (spaceship_state == INVINCIBLE && SDL_GetTicks() - time_begin_invincibility > TIME_INVINCIBILITY && !godmod)
        {
          spaceship_state = ALIVE;
        }
        /* define bullet life's span */
        check_bullet_life_span(&bullet_list);

        /* bullets / asteroids collisions */
        check_bullet_asteroid_collision(&bullet_list, &asteroid_list, &explosion_list, surfaces);

        move_asteroids(asteroid_list);
        move_bullet(bullet_list);

        /* Draw live on screen */
        if(training==false) {
          sprintf(textlive,"Lives : %d",live);
          printText(textlive, 40, 40, font, white, surfaces[id = iSCREEN]);

        }
        /* Draw the score on screen */
        sprintf(textscore,"Score : %d",score);

        if(desactivatescore==true){
          printText("Score : Desactivate", 250, 40, font, white, surfaces[id = iSCREEN]);
        }
        else{
          printText(textscore, 250, 40, font, white, surfaces[id = iSCREEN]);
        }
        /* Draw level on screen */
        sprintf(textlevel,"LEVEL: %d",level);
        printText(textlevel, 260, 10, font, green, surfaces[id = iSCREEN]);

        /* gameover*/

        if(live==0)
          gameover=true;

        if (gameover)
        {
          Mix_HaltMusic();
          Mix_PlayMusic(gameovermusic, 0);
          state = end;
          spaceship_state = DESTROY;
          list_free(&bullet_list);
        }
        if (is_empty(asteroid_list)){
          state = init;
          norepeat=true;
        }
      }

      else if (pause) {
        printText("PAUSE", 260, 10, font, green, surfaces[id = iSCREEN]);
        printText("Press Enter to continue", 120, 50, font, green, surfaces[id]);
      }

      /* #################### END #################### */

      if (state == end) {
        if (desactivatescore==true){
          score=0;
        }
        list_free(&explosion_list);
        move_asteroids(asteroid_list);

        choicemusic=choicememory;

        printText("Press Enter to menu", 130, 280, font, green, surfaces[id = iSCREEN]);	
        sprintf(textlevel,"LEVEL: %d",level);
        printText(textlevel, 130, 50, fonttitle, green, surfaces[id = iSCREEN]);
        printText(textscore, 80, 100, fonttitle, white, surfaces[id = iSCREEN]);
        printText("GAMEOVER", 10, 200, fontgameover, red, surfaces[id = iSCREEN]);

      }


      /* Draw celestial object */
      blit_celestial_object(surfaces[id = iSCREEN], spaceship, asteroid_list, bullet_list, explosion_list, protection);

      /* Update the screen */
      SDL_UpdateRect(surfaces[id = iSCREEN], 0, 0, 0, 0);

      time_before = time_now; 


    }
  }

  /* Clean up */
  list_free(&asteroid_list); 
  list_free(&bullet_list);
  for (i = 0; i < NUMBER_OF_SURFACES; i++) 
  {
    SDL_FreeSurface(surfaces[i]);
  }
  freeFonts(font, fonttitle, fonttitle2, fontgameover, fontwin, fontlevel, fontscore);

  TTF_Quit();
  Mix_FreeChunk(laser);
  Mix_CloseAudio();
  SDL_Quit(); 

  return EXIT_SUCCESS; 
} 

void blit_celestial_object(SDL_Surface *screen, celestial_object spaceship, list asteroid_list, list bullet_list, list explosion_list, celestial_object protection)
{
  while (!is_empty(asteroid_list)) {
    SDL_BlitSurface(asteroid_list->object.surface, &asteroid_list->object.rcSrc, screen, &asteroid_list->object.position); 
    asteroid_list = tail(asteroid_list);
  }
  while (!is_empty(bullet_list)) {
    SDL_BlitSurface(bullet_list->object.surface, &bullet_list->object.rcSrc, screen, &bullet_list->object.position);
    bullet_list = tail(bullet_list);
  }
  while (!is_empty(explosion_list)) {
    SDL_BlitSurface(explosion_list->object.surface, &explosion_list->object.rcSrc, screen, &explosion_list->object.position);
    explosion_list = tail(explosion_list);
  }
  /* After blitting asteroids and bullets, we blit the spaceship. In this way, the spaceship is "on" the bullet when we shot */

  if (spaceship_state != DESTROY) {
    if (spaceship_state == INVINCIBLE)
      SDL_BlitSurface(protection.surface, NULL, screen, &protection.position);
    SDL_BlitSurface(spaceship.surface, &spaceship.rcSrc, screen, &spaceship.position);
  }
}

