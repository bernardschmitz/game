
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "main.h"

class Enemy : public Actor {

   private:

      vector3 target_pos, target_dir, target_hpr;

      quaternion src, dst;

      vector3 angular_vel;
      float w_spd;

      GLuint dl_enemy;

   public:
      Enemy(vector3 p);
      ~Enemy();

      void render();
      void action();   
};

extern ActorList<Enemy> alEnemy;

#endif

