
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "main.h"

class Background : public Actor {

   private:
      GLuint texture_id[4];

      unsigned char *palette;
      unsigned char *half_palette;

      vector3 center;

      float u, ux, uy, uz;

      unsigned char *strips;
      float *cols;

      int hex_tex;
   public:
      Background();
      ~Background();

      void setCenter(vector3 v) { center = v; }

      void render();
      void action(float dt);
};

#endif


