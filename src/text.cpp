
#include "text.h"
#include "texture.h"

TextManager *TextManager::instance = 0;

TextManager::TextManager() {

   w = 800;
   h = 600;

   cw = 16;
   ch = 16;   

   ca = 10;
   ct = 1.0/16.0;

   tex = TextureManager::getInstance()->load("font.png");

   base = glGenLists(256);

   TextureManager::getInstance()->bind(tex);

   // TODO the 16's below should come from the cw,ch above

   for(int i=0; i<256; i++) {
      float cx = (i%cw)/(float)cw;
      float cy = (i/ch)/(float)ch;
      glNewList(base+i, GL_COMPILE);
       glBegin(GL_QUADS);
        glTexCoord2f(cx, cy+ct);
        glVertex2i(0,0);
        glTexCoord2f(cx+ct, cy+ct);
        glVertex2i(cw,0);
        glTexCoord2f(cx+ct, cy);
        glVertex2i(cw,ch);
        glTexCoord2f(cx, cy);
        glVertex2i(0,ch);
       glEnd();
       glTranslatef((float)ca,0,0);
      glEndList();
   }

}

TextManager *TextManager::getInstance() {

   if(instance == 0) 
      instance = new TextManager();

   return instance;
}

void TextManager::_begin() {

   glShadeModel(GL_FLAT);
   glDisable(GL_LIGHTING);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   TextureManager::getInstance()->bind(tex);
   glEnable(GL_TEXTURE_2D);

   glDisable(GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   //glOrtho(0, 1280, 0, 960, -1, 1);
   //glOrtho(0, 640, 0, 480, -1, 1);
   glOrtho(0, w, 0, h, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

}

void TextManager::_end() {

   glMatrixMode(GL_PROJECTION); 
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   glEnable(GL_DEPTH_TEST);

   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glDisable(GL_BLEND);

   glDisable(GL_TEXTURE_2D); 
}



void TextManager::_draw(int x, int y, const char *s) {

   glPushMatrix();
   glTranslated(x, y, 0);
   glListBase(base-32+(128*0));  // 128*1 for 2nd font
   glCallLists(strlen(s), GL_UNSIGNED_BYTE, s);
   glPopMatrix();
}


void TextManager::draw(int x, int y, const char *s) {

   _begin();
   glColor4f(1.0, 1.0, 1.0, 1.0);
   _draw(x, y, s);
   _end();
}

