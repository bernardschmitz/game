
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
/*
   char *c = new char[strlen(s)+1];
   strcpy(c,s);
   buf.push_back(c);
*/
   std::string str(s);
   buf.push_back(s);
//printf("added [%s]\n", c);

   // if reached maximum, remove and delete the first string
   if(buf.size() > max_lines) {
//      Buffer::iterator k = buf.begin();
  //    c = *k;
      buf.pop_front();
//printf("deleted [%s]\n", c);
  //    delete [] c;
   }
}


void Console::process(float dt) {

   if(scroll) {
      spos += dpos*dt;
      delay -= dt;
      if(delay <= 0.0) {
         spos = 0.0;
         scroll = false;
         visible = vis;
      }
      return;
   }

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

void Console::show() { 

   delay = 0.5;
   spos = disp_lines*TextManager::getInstance()->cellHeight();
   dpos = -disp_lines*TextManager::getInstance()->cellHeight() / delay;
   scroll = true;
   vis = visible = true;
}

void Console::hide() { 

   delay = 0.5; 
   spos = 0.0;
   dpos = disp_lines*TextManager::getInstance()->cellHeight() / delay;
   scroll = true;
   vis = false;
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
      int w = tm->screenWidth();
      int h = tm->screenHeight();
      int cw = tm->cellWidth();
      int ch = tm->cellHeight();

      tm->_begin();

      glDisable(GL_TEXTURE_2D);
      glColor4f(0.0, 0.0, 0.0, 0.5);
      glBegin(GL_QUADS);
       glVertex2i(0, (int)spos+h-disp_lines*ch);
       glVertex2i(w, (int)spos+h-disp_lines*ch);
       glVertex2i(w, (int)spos+h);
       glVertex2i(0, (int)spos+h);
      glEnd();
      glEnable(GL_TEXTURE_2D);

      glColor4f(1.0, 1.0, 1.0, 0.75);

      int pos = (int)spos+h - ch;
      for(int i=first; i<last; i++) {
//printf("printing at 0, %d [%s]\n", pos, buf[i]);
         tm->_draw(0, pos, buf[i].c_str());
         pos -= ch;
      }

      tm->_end();
    }
}

