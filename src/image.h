
#ifndef __IMAGE_H__
#define __IMAGE_H__

// RGBA image
#include "memcheck.h"

class Image {
public:
   int width, height;
   unsigned char *pixels;

   Image() { width = height = 0; pixels = 0; }
   Image(const int w, const int h) { width = w; height = h; pixels = new unsigned char[width*height*4]; }

   Image(const Image& img);

   ~Image() { if(pixels != 0) delete [] pixels; }

   bool load(const char *filename);
};

#endif

