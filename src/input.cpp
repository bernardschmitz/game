
#include "input.h"


Input input = Input();


void Input::process() {

/*
   Uint8 *keys = SDL_GetKeyState(NULL);

   rotate_left  = keys[SDLK_LEFT];
   rotate_right = keys[SDLK_RIGHT];
   thrust       = keys[SDLK_UP];
   fire         = keys[SDLK_LCTRL];
   bomb         = keys[SDLK_SPACE];
*/

   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {

      case SDL_KEYDOWN:
         // TODO have a list of functions for each key
         switch(event.key.keysym.sym) {
         case SDLK_LEFT:
            rotate_left = 1;
            break;
         case SDLK_RIGHT:
            rotate_right = 1;
            break;
         case SDLK_LCTRL:
            fire = 1;
            break;
         case SDLK_UP:
            thrust = 1;
            break;
         case SDLK_SPACE:
            bomb = 1;
            break;
         case SDLK_ESC:
            quit = 1;
            break;
         case 96:   // backtick
            console = 1;
            break;
         }
         break;

      case SDL_KEYUP:
         // TODO have a list of functions for each key
         switch(event.key.keysym.sym) {
         case SDLK_LEFT:
            rotate_left = 0;
            break;
         case SDLK_RIGHT:
            rotate_right = 0;
            break;
         case SDLK_LCTRL:
            fire = 0;
            break;
         case SDLK_UP:
            thrust = 0;
            break;
         case SDLK_SPACE:
            bomb = 0;
            break;
         }
         break;

       }
   }

}

