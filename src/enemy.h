
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "main.h"

class Enemy : public Actor {

   private:

      sgVec3 target_pos, target_dir, target_hpr;

      sgQuat src, dst;

   public:
      Enemy(sgVec3 p);
      ~Enemy();

      void render();
      void action();   
};

extern ActorList<Enemy> alEnemy;

#endif

