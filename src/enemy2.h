
#ifndef __ENEMY2_H__
#define __ENEMY2_H__

#include <SDL/SDL_opengl.h>

#include "memcheck.h"
#include "vector.h"
#include "quaternion.h"
#include "actor.h"

class Enemy2 : public Actor {

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

      int life;

      vector3 pain;

   public:
      Enemy2(vector3 p);
      ~Enemy2();

      void render();
      void action(float dt);   

      void setPain(vector3 p) { pain = p; }

float NearestApproachTime(Enemy2 *other);

float NearestApproachPositions(Enemy2 *other, float time);

};

#endif

