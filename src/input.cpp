
#include <SDL/SDL.h>

#include "input.h"


Input *Input::instance = 0;

Input *Input::getInstance() {

   if(instance == 0)
      instance = new Input();

   return instance;
}



void Input::process() {

   Uint8 *keys = SDL_GetKeyState(NULL);

   if(keys != 0) {
      rotate_left  = keys[SDLK_LEFT];
      rotate_right = keys[SDLK_RIGHT];
      thrust       = keys[SDLK_UP];
      fire         = keys[SDLK_LCTRL];
      bomb         = keys[SDLK_SPACE];
   }

// if the console is up it grabs the keyboard

/*
   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {

      case SDL_KEYDOWN:
      case SDL_KEYUP:
         keypress(event.key.keysym.sym, event.key.state==SDL_PRESSED, event.key.keysym.unicode);
         break;
      }
   }
*/
}


void Input::keypress(int code, bool isdown, int unicode) {

/*
   if(isdown && (unicode & 0xff80) == 0) 
      printf(" char %d is [%c]\n", code, unicode & 0x7F);
*/

/*
   if(isdown && code > SDLK_FIRST && code < SDLK_LAST) {
      if(key[code] != 0)
         (key[code])();
   }
*/

   // game keys

//   rotate_left = rotate_right = thrust = fire = bomb = 0;

   if(code == SDLK_LEFT)
      rotate_left = isdown?1:0;
   if(code == SDLK_RIGHT)
      rotate_right = isdown?1:0;
   if(code == SDLK_UP)
      thrust = isdown?1:0;
   if(code == SDLK_LCTRL)
      fire = isdown?1:0;
   if(code == SDLK_SPACE)
      bomb = isdown?1:0;
}

