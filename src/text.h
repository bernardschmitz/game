
#ifndef __TEXT_H__
#define __TEXT_H__

#include "main.h"

class TextManager {
private:
   int tex;
   int base;

   int w, h, cw, ch;
   
   TextManager();
   TextManager::~TextManager() { }

   static TextManager *instance;
public:

   static TextManager *getInstance();

   void draw(const int x, const int y, const char *s);

   int screenWidth() { return w; }
   int screenHeight() { return h; }
   int cellWidth() { return cw; }
   int cellHeight() { return ch; }
};


#endif

