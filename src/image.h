
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "main.h"

// RGBA image

class Image {
public:
   int width, height;
   byte *pixels;

   Image() { width = height = 0; pixels = 0; }
   Image(const int w, const int h) { width = w; height = h; pixels = new byte[width*height*4]; }

   Image(const Image& img);

   ~Image() { if(pixels != 0) delete [] pixels; }

   bool load(const char *filename);
};

#endif

