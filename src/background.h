
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "main.h"

struct Vertex {
   unsigned char r, g, b, a;
   float x, y, z;
};



class Background : public Actor {

   private:
      GLuint texture_id[4];

      unsigned char *palette;
      unsigned char *half_palette;

      vector3 center;

      float u, ux, uy, uz;

      float *cols;

      int hex_tex;

      float cx, cy, cz;

      Vertex *strips;
      Vertex *hexes;

      int max_w, max_h, max_v, idx;
      int max_hw, max_hh, max_hv;

   public:
      Background();
      ~Background();

      void setCenter(vector3 v) { center = v; }

      void render();
      void action(float dt);
};

#endif


