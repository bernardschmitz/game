
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "main.h"

class Background : public Actor {

   private:
      GLuint texture_id[4];

      vector4 *palette;

      vector3 center;

   public:
      Background();
      ~Background();

      void setCenter(vector3 v) { center = v; }

      void render();
      void action();
};

#endif


