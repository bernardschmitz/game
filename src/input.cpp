
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

//   con = Console::getInstance(); 

   quit = rotate_left = rotate_right = thrust = fire = bomb = 0; 
}


Input::~Input() { 

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
         if(event.key.keysym.sym == SDLK_ESCAPE)
            quit = 1;

         if(event.key.keysym.sym == 96)
            Console::getInstance()->show();

         break;
      }
   }


   Uint8 *keys = SDL_GetKeyState(NULL);

   if(keys != 0) {
      rotate_left  = keys[SDLK_LEFT];
      rotate_right = keys[SDLK_RIGHT];
      thrust       = keys[SDLK_UP];
      fire         = keys[SDLK_LCTRL];
      bomb         = keys[SDLK_SPACE];

      
      // tilde brings up the console
//      if(keys[96]) {
         // wait until user releases the tilde key
/*
         while(keys[96]) {
            SDL_Event event;
            SDL_PollEvent(&event);
            keys = SDL_GetKeyState(NULL);
         }
*/
//         Console::getInstance()->show();
 //     }
   }
}

