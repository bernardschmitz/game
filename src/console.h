
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <deque>
#include <string>

typedef std::deque<std::string> Buffer;

class Console {
private:
   unsigned int buf_max;
   int buf_pos;
   Buffer buf;

   unsigned int hist_max;
   int hist_pos;
   Buffer history;

   std::string cmd_buf;
   std::string cmd_line;
   unsigned int cursor;
   std::string prompt;

   bool visible, vis;
   int disp_lines;

   float cursor_rate, cursor_time;
   bool cursor_on;

   float spos, dpos;
   float delay;
   bool scroll;

   static Console *instance;

   Console();

   void keypress(int code, bool isdown, char ascii);
public:

   ~Console();
   static Console* getInstance();

   void show();
   void hide();
   bool isVisible() { return visible; }

   void addString(const char *s);

   void process(float dt);
   void render();
};


#endif 

