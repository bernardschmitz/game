
#ifndef __TEXT_H__
#define __TEXT_H__

#include "main.h"

class TextManager {
private:
   int w, h;

   GLuint id;

public:
   TextManager();
   TextManager::~TextManager() { }

   static void draw(char *s);
};


extern TextManager text;

#endif

