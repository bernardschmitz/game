
#include <SDL/SDL.h>

#include "input.h"
#include "console.h"

Input *Input::instance = 0;

Input *Input::getInstance() {

   if(instance == 0)
      instance = new Input();

   return instance;
}

Input::Input() { 

   quit = 0;
   rotate_left = rotate_right = thrust = fire = bomb = 0; 
   lock_cam = 0;
}


Input::~Input() { 

   printf("input destructor\n");
   instance = 0;
}


void Input::process() {

   // return if console up
   if(Console::getInstance()->isVisible()) {
      rotate_left = rotate_right = thrust = fire = bomb = 0; 
      return;
   }

   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {

      case SDL_KEYUP:
         
         switch(event.key.keysym.sym) {

         case SDLK_ESCAPE:
            quit = 1;
            break;

         case SDLK_c:
            lock_cam = !lock_cam;
            break;
         case 96: // tilde
            Console::getInstance()->show();
            break;

         default:
            ; // nothing
         }
      }
   }


   Uint8 *keys = SDL_GetKeyState(NULL);

   if(keys != 0) {
      rotate_left  = keys[SDLK_LEFT];
      rotate_right = keys[SDLK_RIGHT];
      thrust       = keys[SDLK_UP];
      fire         = keys[SDLK_LCTRL];
      bomb         = keys[SDLK_SPACE];
   }
}

