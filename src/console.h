
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <deque>

typedef std::deque<char*> Buffer;

class Console {
private:
   int max_lines;
   int disp_lines;
   Buffer buf;
   bool visible;


public:
   Console() { max_lines = 4; disp_lines = 10; visible = false; } 
   ~Console() { printf("console destroyed\n"); }

   void show() { visible = true; }
   void hide() { visible = false; }

   void addString(const char *s);

   void action();
   void render();
};


#endif 

