

#include "enemy.h"
#include "player.h"

#define MOVING      0
#define TRACKING    1
#define TARGET      2


ActorList<Enemy> alEnemy;



Enemy::Enemy(sgVec3 p) : Actor() { 

   sgCopyVec3(pos, p); 

   sgMakeIdentQuat(rot);

   delay = 1;
   state = TARGET;

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
            delay = 1;
            state = TARGET;
         }
         break;

      case TARGET:
         delay--;
         if(delay == 0) {
            player->getPosition(target_pos);

            sgSubVec3(target_dir, target_pos, pos);
            sgNormaliseVec3(target_dir);

            sgHPRfromVec3(target_hpr, target_dir);

            float angle = target_hpr[0];
            //float angle = sgAngleBetweenNormalizedVec3(dir, target);  

            sgAngleAxisToQuat(dst, angle, 0.0, 0.0, -1.0);

            sgCopyQuat(src, rot);

            delay = 15;
            state = TRACKING;
         }
         break;

      case TRACKING:


         sgAddVec3(pos, vel);

         sgSlerpQuat(rot, src, dst, (15.0-delay)/15.0);

/*   		sgVec3 axis;
		   float angle;
		   sgQuatToAngleAxis(&angle, axis, rot);

         // get dir vector from quaternion
         sgSetVec3(dir, -sgSin(angle), sgCos(angle), 0.0);
*/
         sgCopyVec3(dir, target_dir);

         delay--;
//printf("%d %p ta %f angle %f dir %f %f %f\n", delay, (void*)this, target_hpr[0], angle, dir[0], dir[1], dir[2]);
         if(delay == 0) {


            // acceleration
            sgAddScaledVec3(vel, dir, 0.025);
            //sgScaleVec3(vel, dir, 0.025);

    //friction
    float vmag = sgScalarProductVec3(vel, vel);
          if(vmag > 0.0) {
                sgVec3 friction;
                sgNormaliseVec3(friction, vel);
                sgAddScaledVec3(vel, friction, -0.001-0.05*vmag/(1.2*1.2));
           }
   
                                // clamp velocity
                                   if(sgScalarProductVec3(vel, vel) > 1.2*1.2) {
                                           sgVec3 n;
                                            sgNormaliseVec3(n, vel);
                                           sgScaleVec3(vel, n, 1.2);
                                   }
   

            delay = 5;
            state = MOVING;
         }
         break;

      default: 
         state = TRACKING;
         break;
   } 

}


void Enemy::render() {

   sgVec4 green = { 0.5, 0.8, 1.0, 1.0 };
   sgVec4 red = { 0.9, 0.3, 0.4, 1.0 };
   sgVec4 white = { 1.0, 1.0, 1.0, 1.0 };

   glPushMatrix();
   glTranslatef(pos[0], pos[1], pos[2]);

   glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
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
   sgVec3 axis;
   float angle;

   sgQuatToAngleAxis(&angle, axis, rot);

   glRotatef(angle, axis[0], axis[1], axis[2]);

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

