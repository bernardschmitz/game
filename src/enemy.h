
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "main.h"

class Enemy : public Actor {

   private:

      vector3 target_pos, target_dir, target_hpr;

      vector3 steering;

      quaternion src, dst, rot;

      vector3 angular_vel;
      float w_spd;
      float v_spd;
      float v_acc;

      float tt;
      float look_ahead;

      GLuint dl_enemy;

      vector3 pain;

   public:
      Enemy(vector3 p);
      ~Enemy();

      void render();
      void action(float dt);   


float NearestApproachTime(Enemy *other);

float NearestApproachPositions(Enemy *other, float time);

};

#endif

