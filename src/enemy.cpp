

#include "enemy.h"
#include "player.h"

#define MOVING      0
#define TRACKING    1


ActorList<Enemy> alEnemy;



Enemy::Enemy(sgVec3 p) : Actor() { 

   sgCopyVec3(pos, p); 

   delay = 60;
   state = TRACKING;
}

Enemy::~Enemy() {
   // do nothing
}


void Enemy::action() {


   switch(state) {

      case MOVING:
         sgAddVec3(pos, vel);
         delay--;
         if(delay == 0) {
            delay = 200;
            state = TRACKING;
         }
         break;

      case TRACKING:
         sgVec3 target;
         player->getPosition(target);

         sgSubVec3(dir, target, pos);
         sgNormaliseVec3(dir);

         delay--;
         if(delay == 0) {
            sgScaleVec3(vel, dir, 0.1);

            delay = 50;
            state = MOVING;
         }
         break;

      default: 
         state = TRACKING;
         break;
   } 

}


void Enemy::render() {

   sgVec4 green = { 0.5, 0.8, 0.2, 1.0 };
   sgVec4 red = { 0.9, 0.3, 0.4, 1.0 };
   // blocks
   glPushMatrix();
   glTranslatef(pos[0], pos[1], pos[2]);


   glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(dir[0], dir[1], dir[2]);
   glEnd();

   glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f( 0.0, 0.25, 0.0);
    glVertex3f(-0.2,  0.0, 0.0);
    glVertex3f( 0.0, -0.2, 0.0);
    glVertex3f( 0.2, 0.0, 0.0);
   glEnd();
 
   glPushMatrix();
   sgVec3 hpr;
   sgHPRfromVec3(hpr, dir);
   glRotatef(hpr[0], 0.0, 0.0, 1.0);

   glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f( 0.0, 1.0, 0.0);
    glVertex3f(-0.5,  0.0, 0.0);
    glVertex3f( 0.0, -0.5, 0.0);
    glVertex3f( 0.5, 0.0, 0.0);
   glEnd();
   glPopMatrix();
 
  glPopMatrix();

}

