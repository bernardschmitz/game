
#ifndef __INPUT_H__
#define __INPUT_H__

//#include "console.h"


class Input {
private:
//   Console *con;
   //Menu * menu;

   static Input *instance;

   Input();
   ~Input();

//   void keypress(int code, bool isdown, int unicode);
public:
   static Input *getInstance();

//   void linkConsole(Console *c) { con = c; }
//   void unlinkConsole() { con = 0; }
 

   void process();

   int rotate_left;
   int rotate_right;
   int thrust;
   int fire;
   int bomb;

   int quit;
};


#endif

