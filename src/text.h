
#ifndef __TEXT_H__
#define __TEXT_H__

#include "main.h"

class TextManager {
private:
   int tex;
   int base;
   
   TextManager();
   TextManager::~TextManager() { }

   static TextManager *instance;
public:

   static TextManager *getInstance();

   void draw(const int x, const int y, const char *s);
};


#endif

