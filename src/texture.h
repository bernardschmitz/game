
#ifndef _TEXTURE_H__
#define _TEXTURE_H__

#include <vector>

#include "main.h"
#include "image.h"

class Texture {
public:
   GLuint gl_id;
   int ref;
   char *name;
   Image *image;
};


typedef std::vector<Texture*> TextureList;


class TextureManager {
private:
   TextureList textures;

   int find(const char *name);
   int create(Image *img, const char *name);
   TextureManager();

   static TextureManager *instance; 
public: 
   ~TextureManager();
   static TextureManager *getInstance();

   //int load(Image& img);
   int load(const char *fn);

   void free(const int id);
   void freeall();

   void setup(const int id);
   void bind(const int id);

   int width(const int id);
   int height(const int id);
   int gl_id(const int id);
};


#endif

