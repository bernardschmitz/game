

#include "enemy.h"
#include "player.h"

#define MOVING      0
#define TRACKING    1



Enemy::Enemy(sgVec3 p) { 

   sgCopyVec3(position, p); 
   sgZeroVec3(velocity); 

   delay = 60;
   state = TRACKING;
}

Enemy::~Enemy() {
   // do nothing
}


int Enemy::action() {


   switch(state) {

      case MOVING:
         sgAddVec3(position, velocity);
         delay--;
         if(delay == 0) {
            delay = 1;
            state = TRACKING;
         }
         break;

      case TRACKING:
         delay--;
         if(delay == 0) {
            sgVec3 target;
            player->getPosition(target);

            sgVec3 acceleration;
            sgSubVec3(acceleration, target, position);
            sgNormalizeVec3(acceleration);
            sgScaleVec3(acceleration, 0.05);

            sgAddVec3(velocity, acceleration);

            delay = 10;
            state = MOVING;
         }
         break;

      default: 
         state = TRACKING;
         break;
   } 

   return 0;
}


int Enemy::render() {

   sgVec4 yellow = { 0.5, 0.8, 0.2, 1.0 };
   // blocks
             glPushMatrix();
                glTranslatef(position[0], position[1], position[2]);
//                   glRotatef(z_rotation, 0.0, 0.0, 1.0);
                      glBegin(GL_QUADS);
                          glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
                              glNormal3f( 0.0, 0.0, -1);
                                  glVertex3f(  0.5,  0.5, 0.0);
                                      glVertex3f(-0.5,  0.5, 0.0);
                                          glVertex3f(-0.5, -0.5, 0.0);
                                              glVertex3f( 0.5, -0.5, 0.0);
                                                 glEnd();
                                                    glPopMatrix();

   return 0;
}

