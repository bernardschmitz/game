
#include "input.h"


Input input = Input();


void Input::process() {

   Uint8 *keys = SDL_GetKeyState(NULL);

   rotate_left  = keys[SDLK_LEFT];
   rotate_right = keys[SDLK_RIGHT];
   thrust       = keys[SDLK_UP];
   fire         = keys[SDLK_LCTRL];
   bomb         = keys[SDLK_SPACE];

}

