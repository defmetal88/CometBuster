#include <SDL/SDL_mixer.h>
#include <stdint.h>
#include "MusicManagement.h"

void readmusic(int choicemusic,Mix_Music *mainmusic,Mix_Music *epicbattle,Mix_Music *battle3,Mix_Music *battle4,Mix_Music *battle5){

  if (choicemusic==1){
    Mix_PlayMusic(mainmusic, -1);
  }
  else if (choicemusic==2){
    Mix_PlayMusic(epicbattle, -1);
  }
  else if (choicemusic==3){
    Mix_PlayMusic(battle3, -1);
  }
  else if (choicemusic==4){
    Mix_PlayMusic(battle4, -1);
  }
  else if (choicemusic==5){
    Mix_PlayMusic(battle5, -1);
  }
}

