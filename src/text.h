
#ifndef __TEXT_H__
#define __TEXT_H__

#include "memcheck.h"

class TextManager {
private:
   int tex;
   int base;

   int w, h, cw, ch, ca;
   float ct;
   
   TextManager();
   TextManager::~TextManager() { }

   static TextManager *instance;
public:

   static TextManager *getInstance();

   void draw(const int x, const int y, const char *s);

   int screenWidth() { return w; }
   int screenHeight() { return h; }
   // adjusted for the cell advance since chars may overlap
   int cellWidth() { return cw+(ca-cw); }
   int cellHeight() { return ch; }

   void _begin();
   void _draw(const int x, const int y, const char *s);
   void _end();
};


#endif

