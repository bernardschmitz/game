
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "memcheck.h"
#include "image.h"


Image::Image(const Image& img) {

   width = img.width; 
   height = img.height; 
   pixels = new unsigned char[width*height*4]; 
   memcpy(pixels, img.pixels, sizeof(unsigned char)*width*height*4); 
}




bool Image::load(const char *filename) {

   SDL_Surface *surf;

printf("loading %s...\n", filename);
   surf = IMG_Load(filename);

   if(surf != 0) {

      width  = surf->w;       
      height = surf->h;       
      pixels = new unsigned char[width*height*4];

      SDL_LockSurface(surf);

      unsigned char *p = (unsigned char *)surf->pixels;
      for(int y=0; y<height; y++) {
         for(int x=0; x<width; x++) {
            pixels[y*height*4+x*4+0] = p[y*surf->pitch+x*4+0];
            pixels[y*height*4+x*4+1] = p[y*surf->pitch+x*4+1];
            pixels[y*height*4+x*4+2] = p[y*surf->pitch+x*4+2];
            pixels[y*height*4+x*4+3] = p[y*surf->pitch+x*4+3];
         }
      }
       
      SDL_UnlockSurface(surf);
      SDL_FreeSurface(surf);

      return true;
   }
printf("\tfailed!\n");
   return false;
}

