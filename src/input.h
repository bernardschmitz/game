
#ifndef __INPUT_H__
#define __INPUT_H__

#include "console.h"

typedef void(*KeyAction)();

class Input {
private:
   Console *con;
   //Menu * menu;



   KeyAction key[SDLK_LAST-SDLK_FIRST]; 

   static Input *instance;

   Input() { con = 0; for(int i=0; i<SDLK_LAST-SDLK_FIRST; i++) key[i] = 0; 
             rotate_left = rotate_right = thrust = fire = bomb = 0; }
   ~Input() { instance = 0; }

   void keypress(int code, bool isdown, int unicode);
public:
   static Input *getInstance();

   void linkConsole(Console *c) { con = c; }
   void unlinkConsole() { con = 0; }
 
   void linkKeyAction(int i, KeyAction act) { key[i] = act; }

   void process();

   int rotate_left;
   int rotate_right;
   int thrust;
   int fire;
   int bomb;
};


#endif

