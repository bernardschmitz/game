
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "main.h"

class Enemy {

   private:
      sgVec3 position;
      sgVec3 velocity;

      int delay;
      int state;

   public:
      Enemy(sgVec3 p);
      ~Enemy();

      int render();
      int action();   
};

#endif

