#ifndef GLOBALE_H
#define GLOBALE_H
#include <SDL/SDL_mixer.h>

Mix_Music *this_is_sparta;
Mix_Music *Back_In_Black_8_bit;
Mix_Music *Game_of_Thrones_8_bit;
Mix_Music *gameovermusic;
Mix_Music *pausemusic;
Mix_Music *titlemusic;
Mix_Music *mainmusic;
Mix_Music *epicbattle;
Mix_Music *battle3;
Mix_Music *battle4;
Mix_Music *battle5;
Mix_Chunk *laser;
Mix_Chunk *noiseexplosion;
int time_begin_invincibility;
int NB_OF_ASTEROID_AT_STARTUP;
int level;
int randommusic;
int choicememory;
int choicemusic;
bool pause;
bool training;
bool gameover;
bool quit;
bool desactivatescore;
int choice;
int choicemusic;
int spaceship_state;
int score;
gamestates state;
#endif