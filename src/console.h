
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
   bool visible, vis;

   float spos, dpos;
   float delay;
   bool scroll;

   static Console *instance;

   Console() { scroll = false; max_lines = 1000; disp_lines = 15; visible = false; } 
   ~Console() { printf("console destroyed\n"); }
public:

   static Console* getInstance();

   void show();
   void hide();
   bool isVisible() { return visible; }

   void addString(const char *s);

   void process(float dt);
   void render();
};


#endif 

