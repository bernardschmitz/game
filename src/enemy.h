
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "main.h"

class Enemy : public Actor {

   private:

   public:
      Enemy(sgVec3 p);
      ~Enemy();

      void render();
      void action();   
};

extern ActorList<Enemy> alEnemy;

#endif

