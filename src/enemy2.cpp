
extern "C" {
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}


#include <iostream>

#include "enemy2.h"
#include "player.h"
#include "random.h"

#define MOVING      0
#define TRACKING    1
#define TARGET      2



Enemy2::Enemy2(vector3 p) : Actor(ACT_ENEMY2, "Enemy2", p) { 

   //can turn once a frame
   angular_vel.set(0.0, 0.0, degToRad(90.0/50.0));

   w_spd = 180.0;
   v_spd = 0.5;
   v_acc = 750 + uniform_random_float(-50.0, 50.0);

   mass = 10.0;
   radius = 1.0;

   inv_mass = 1.0/mass;

   life = 20;

   collision_flags = ACT_ENEMY | ACT_ENEMY2 | ACT_BULLET | ACT_PLAYER;

   max_speed = 10; //30;
   max_force = 100;

   velocity = vector3(0,0,0);

   rot.set(0.0, 0.0, 0.0, 1.0);

   position = p;
   prev_position = p;

   look_ahead = max_speed*0.15;

   target_pos = vector3( uniform_random_float(-40.0, 40.0), uniform_random_float(-40.0, 40.0), -10.0 );

   //sgMakeIdentQuat(rot);

   delay = 1;
   state = TARGET;

   dl_enemy = glGenLists(2);


   glNewList(dl_enemy, GL_COMPILE);
   glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.0, 0.0, 0.0, 1.0);
    for(int i=0; i<12; i++) {
       float x = radius*cos(i/12.0*2.0*M_PI);
       float y = radius*sin(i/12.0*2.0*M_PI);
       glVertex3f(x, y, 0.0);
    }
   glEnd();
   glEndList();

   glNewList(dl_enemy+1, GL_COMPILE);
   glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    for(int i=0; i<12; i++) {
       float x = radius*cos(i/12.0*2.0*M_PI);
       float y = radius*sin(i/12.0*2.0*M_PI);
       glVertex3f(x, y, 0.0);
    }
   glEnd();
   glEndList();


}

Enemy2::~Enemy2() {
   // do nothing
}




void Enemy2::action(float dt) {

/*
   flags = 0;
   if(collide(player, dt)) {
      std::cout << position << " " << hit_position << " " << hit_normal << " " << hit_time << " " << std::endl;
   }
*/
/*
   if(flags & ACT_COLLISION) {
      life--;
      if(life < 0)
         flags |= ACT_REMOVE;
   }
 */  


/*
   lua_pushstring(L, "enemy_action");
   lua_gettable(L, LUA_GLOBALSINDEX);
   lua_pushstring(L, name);
   lua_pushnumber(L, dt);
   lua_call(L, 2, 0);
*/

/*
   float size = 200.0;

   force = vector3(0,0,0);

   if(position.x-radius < -size) {
      force += vector3(5, 0, 0)*mass / dt;
   }
   if(position.x+radius > size) {
      force += vector3(-5, 0, 0)*mass / dt;
   }

   if(position.y-radius < -size) {
      force += vector3(0, 5,  0)*mass / dt;
   }
   if(position.y+radius > size) {
      force += vector3(0, -5,  0)*mass / dt;
   }

//   force += mass * vector3(0, -5.0f, 0);
*/

   vector3 dir = position - player->getPosition();

   vector3 steering = velocity - dir;

   force = !steering * max_force;

}



void Enemy2::render() {


   float green[] = { 0.5, 0.8, 1.0, 1.0 };
   float red[] = { 0.9, 0.3, 0.4, 1.0 };
   float white[] = { 1.0, 1.0, 1.0, 1.0 };

   float n = grid_list.size()/4.0;

   glDisable(GL_LIGHTING);

   glColor4f(pain.x, pain.y, pain.z, 1.0);
//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

   //printf("speed %f alpha %f\n", speed, (max_speed-speed)/max_speed);
//   glColor4f(pain.x, pain.y, pain.z, fabs(0.25-speed)/0.25);

/*
   if(flags & ACT_COLLISION) {
      assert(hit_actor != 0);
      vector3 other = hit_actor->getPosition();

      glBegin(GL_LINES);
       glColor4f(0.0, 1.0, 0.0, 1.0);
       glVertex3f(other.x, other.y, other.z);
       glVertex3f(position.x, position.y, position.z);
      glEnd();

      glColor4f(1.0*n, 0.0, 0.0, 1.0);
   }
   else {
      glColor4f(1.0*n, 1.0*n, 0.0, 1.0);
   }
*/

   glPushMatrix();
   glTranslatef(position.x, position.y, position.z);
/*
   glBegin(GL_LINES);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(velocity.x, velocity.y, velocity.z);
   glEnd();
*/
   if(flags & ACT_COLLISION) 
      glCallList(dl_enemy+1);
   else
      glCallList(dl_enemy);

/*
   glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<12; i++) {
       float x = radius*cos(i/12.0*2.0*M_PI);
       float y = radius*sin(i/12.0*2.0*M_PI);
       glVertex3f(x, y, 0.0);
    }
   glEnd();
*/

  glPopMatrix();

   glDisable(GL_BLEND);
   glEnable(GL_LIGHTING);
}

