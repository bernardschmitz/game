
#include "player.h"
#include "input.h"
#include "settings.h"

Player::Player() {

   sgSetVec3(position, 0.0, 0.0, -10.0);
   sgZeroVec3(velocity);

   z_rotation = 0.0;
}

Player::~Player() {
   // do nothing
}

int Player::action() {

   // rotate player
   if(input.rotate_left) {
      z_rotation += 360.0/60.0;
   }

   if(input.rotate_right) {
      z_rotation -= 360.0/60.0;
   }

   // clamp rotation
   if(z_rotation > 360.0)
      z_rotation -= 360.0;
   if(z_rotation < 0.0)
      z_rotation += 360.0;


   // thrust
   if(input.thrust) {

      sgVec3 acceleration = { sgCos(z_rotation)/100.0, sgSin(z_rotation)/100.0, 0.0 };

      sgAddVec3(velocity, acceleration);
   }

   sgAddVec3(position, velocity);

   if(position[0] < -settings.world_width)
      position[0] += settings.world_width*2.0;

   if(position[0] >  settings.world_width)
      position[0] -= settings.world_width*2.0;

   if(position[1] < -settings.world_height)
      position[1] += settings.world_height*2.0;

   if(position[1] >  settings.world_height)
      position[1] -= settings.world_height*2.0;



   return 0;
}

int Player::render() {

   sgVec4 green  = { 0.0, 1.0, 0.0, 1.0 };
   sgVec4 yellow = { 1.0, 1.0, 0.0, 1.0 };

   glPushMatrix();
   glTranslatef(position[0], position[1], position[2]);
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(z_rotation, 0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f( 0.5, -0.5, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glNormal3f( 0.0, 0.0, 1);
    glVertex3f(  0.0,  0.5, 0.0);
    glVertex3f( 0.5, -0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
   glEnd();
   glPopMatrix();

   return 0;
}

