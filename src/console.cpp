
#include <SDL/SDL.h>

#include "console.h"
#include "text.h"

Console *Console::instance = 0;

Console *Console::getInstance() {

   if(instance == 0)
      instance = new Console();

   return instance;
}


void Console::addString(const char *s) {

   // allocate, copy and insert new string
   char *c = new char[strlen(s)+1];
   strcpy(c,s);
   buf.push_back(c);

//printf("added [%s]\n", c);

   // if reached maximum, remove and delete the first string
   if(buf.size() > max_lines) {
      Buffer::iterator k = buf.begin();
      c = *k;
      buf.pop_front();
//printf("deleted [%s]\n", c);
      delete [] c;
   }
}


void Console::process() {

   if(!visible)
      return;

   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {

      case SDL_KEYUP:
         // tilde turns console off
         if(event.key.keysym.sym == 96)
            hide();
 
         break;

      case SDL_KEYDOWN:

         break;
      }
   }
}


void Console::render() {

   if(!visible)
      return;

   int last  = buf.size();
   int first = last - disp_lines;

   if(first < 0)
      first = 0;

   if(first < last) {

      TextManager *tm = TextManager::getInstance();

      glColor4f(1.0, 1.0, 1.0, 1.0);

      int pos = tm->screenHeight() - tm->cellHeight();
      for(int i=first; i<last; i++) {
//printf("printing at 0, %d [%s]\n", pos, buf[i]);
         tm->draw(0, pos, buf[i]);
         pos -= tm->cellHeight();
      }
   }
}

