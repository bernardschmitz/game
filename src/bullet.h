
#ifndef __BULLET_H__
#define __BULLET_H__

#include "main.h"

class Bullet : public Actor {

   private:

      int energy;
      bool squid;
      vector3 A,B,C,D;

   public:
      Bullet(vector3 p, vector3 v, int e=20);
      ~Bullet();

      void render();
      void action();   
};


#endif

