
#include "text.h"

TextManager text("Font.bmp", 16, 16);


TextManager::TextManager(const char *s, const int ww, const int hh) {

   id = texture_manager.load(s);

   w = ww;
   h = hh;
}


void TextManager::draw(const char *s) {

   // TODO this should only be done once 
   // need to optimize it away
   glBindTexture(GL_TEXTURE_2D, id);
   glEnable(GL_TEXTURE_2D);

   char *k = s;

   vector3 p;

   while(*k) {

      
   } 

   glDisable(GL_TEXTURE_2D); 
}

