
#include "text.h"
#include "texture.h"

TextManager *TextManager::instance = 0;

TextManager::TextManager() {

   w = 800;
   h = 600;

   cw = 16;
   ch = 16;   

   tex = TextureManager::getInstance()->load("font.png");

   base = glGenLists(256);

   TextureManager::getInstance()->bind(tex);

   // TODO the 16's below should come from the cw,ch above

   for(int i=0; i<256; i++) {
      float cx = (i%16)/16.0f;
      float cy = (i/16)/16.0f;
      glNewList(base+i, GL_COMPILE);
       glBegin(GL_QUADS);
        glTexCoord2f(cx, cy+1.0/16.0);
        glVertex2i(0,0);
        glTexCoord2f(cx+1.0/16.0, cy+1.0/16.0);
        glVertex2i(16,0);
        glTexCoord2f(cx+1.0/16.0, cy);
        glVertex2i(16,16);
        glTexCoord2f(cx, cy);
        glVertex2i(0,16);
       glEnd();
       glTranslated(10,0,0);
      glEndList();
   }

}

TextManager *TextManager::getInstance() {

   if(instance == 0) 
      instance = new TextManager();

   return instance;
}


void TextManager::draw(int x, int y, const char *s) {

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

   glPushMatrix();
   glTranslated(x, y, 0);
   glListBase(base-32+(128*0));  // 128*1 for 2nd font
   glCallLists(strlen(s), GL_UNSIGNED_BYTE, s);
   glPopMatrix();

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

