
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "main.h"

class Background {

   private:
      GLuint texture_id[4];

      vector4 *palette;

   public:
      Background();
      ~Background();

      void render(vector3 center, int flags);
};

#endif


