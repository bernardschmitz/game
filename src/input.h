
#ifndef __INPUT_H__
#define __INPUT_H__

//#include "console.h"

#include "memcheck.h"

class Input {
private:
//   Console *con;
   //Menu * menu;

   static Input *instance;

   Input();

//   void keypress(int code, bool isdown, int unicode);
public:
   static Input *getInstance();
   ~Input();

//   void linkConsole(Console *c) { con = c; }
//   void unlinkConsole() { con = 0; }

   void process();

   int rotate_left;
   int rotate_right;
   int thrust;
   int fire;
   int bomb;

   int quit;
   int lock_cam;
};


#endif

