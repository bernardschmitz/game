
#include "texture.h"

TextureManager texture_manager;


TextureManager::~TextureManager() {

   // TODO
}


void TextureManager::free(const int n) {

   textures[n]->ref--;

   if(textures[n]->ref > 0)
      return;

   if(textures[n]->gl_id != 0)
      glDeleteTextures(1, &textures[n]->gl_id);

   delete textures[n];

   textures[n] = 0;
}


int TextureManager::create(Image *img, const char *name) {

   Texture *t = new Texture();

   t->ref = 0;
   t->image = img;
   t->name = new char[strlen(name)+1];
   strcpy(t->name, name);
   t->gl_id = 0;

   int i;
   for(i=0; i<textures.size(); i++) {
      if(textures[i] == 0) {
         textures[i] = t;
         return i;
      }
   }

   textures.push_back(t);

   return i;
}


int TextureManager::find(const char *s) {

   for(int i=0; i<textures.size(); i++) {
      if(textures[i] != 0)
         printf("%d %s %s\n", i, textures[i]->name, s);
      if(textures[i] != 0 && strcmp(textures[i]->name, s) == 0) {
         printf("found!\n");
         return i;
      }
   }

   return -1;
}


int TextureManager::load(const char *fn) {

   // already loaded?
   int n = find(fn);
   if(n > 0) {
      textures[n]->ref++;
      return n;
   }

   Image *img = new Image();

   // load image
   if( img->load(fn) ) {

      int n = create(img, fn);

      setup(n);      

      return n;
   }

   return -1;
}

     
void TextureManager::setup(const int n) {

   Texture *t = textures[n];

   glGenTextures(1, &t->gl_id);
   glBindTexture(GL_TEXTURE_2D, t->gl_id);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, t->image->width, t->image->height, GL_RGBA, GL_UNSIGNED_BYTE, t->image->pixels);
 
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void TextureManager::bind(const int n) {
   
   glBindTexture(GL_TEXTURE_2D, textures[n]->gl_id);
}

int TextureManager::width(const int n) {

   return textures[n]->image->width;
}

int TextureManager::height(const int n) {

   return textures[n]->image->height;
}

int TextureManager::gl_id(const int n) {

   return textures[n]->gl_id;
}





