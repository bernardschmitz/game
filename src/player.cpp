
#include "player.h"
#include "input.h"
#include "settings.h"


Player *player;

Player::Player() {

   sgSetVec3(position, 0.0, 0.0, -10.0);
   sgZeroVec3(velocity);

   z_rotation = 0.0;

   thrusting = 0;
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

      if(thrusting < 30)
         thrusting++;

      sgVec3 acceleration = { sgCos(z_rotation)/100.0, sgSin(z_rotation)/100.0, 0.0 };

      sgAddVec3(velocity, acceleration);
   }
   else {
      if(thrusting > 0)
         thrusting--;
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

   sgVec4 green  = { 1.0, 1.0, 1.0, 1.0 };
   sgVec4 yellow = { 1.0, 1.0, 0.0, 1.0 };

   // ship
   glPushMatrix();
   glTranslatef(position[0], position[1], position[2]);
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(z_rotation, 0.0, 0.0, 1.0);


   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
/*
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f( 0.5, -0.5, 0.0);
   glEnd();
*/
   float recoil = 30.0*sin((float)thrusting/30.0*M_PI/2.0); 

   glPushMatrix();
   glRotatef(140.0-recoil, 0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  1.1, 0.0);
    glVertex3f(-0.075, 0.0, 0.0);
    glVertex3f( 0.075, 0.0, 0.0);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glRotatef(-140.0+recoil, 0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  1.1, 0.0);
    glVertex3f(-0.075, 0.0, 0.0);
    glVertex3f( 0.075, 0.0, 0.0);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.3, -0.5, 0.0);
   glRotatef(10.0, 0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  1.25, 0.0);
    glVertex3f(-0.05, 0.0, 0.0);
    glVertex3f( 0.05, 0.0, 0.0);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.3, -0.5, 0.0);
   glRotatef(-10.0, 0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  1.25, 0.0);
    glVertex3f(-0.05, 0.0, 0.0);
    glVertex3f( 0.05, 0.0, 0.0);
   glEnd();
   glPopMatrix();


   //        cone { <0, 0, 0> .08 <0, -.05, 0> .15 rotate -10*z translate <-0.3, -.5, 0> }
   glPushMatrix();
   glTranslatef(0.3, -0.5, 0.0);
   glRotatef(10.0, 0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f( -0.04,  0.0, 0.0);
    glVertex3f(-0.075, -0.05, 0.0);
    glVertex3f( 0.075, -0.05, 0.0);
    glVertex3f( 0.04,  0.0, 0.0);
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.3, -0.5, 0.0);
   glRotatef(-10.0, 0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f( -0.04,  0.0, 0.0);
    glVertex3f(-0.075, -0.05, 0.0);
    glVertex3f( 0.075, -0.05, 0.0);
    glVertex3f( 0.04,  0.0, 0.0);
   glEnd();
   glPopMatrix();


   //                        sphere { <0, 0, 0> 0.2 texture { T_Brass_4B } }
   glBegin(GL_POLYGON);
   glNormal3f( 0.0, 0.0, -1);
   for(float a=0.0; a<2.0*M_PI; a+=2.0*M_PI/12.0) {
     glVertex3f(0.2*cos(a), 0.2*sin(a), 0.0);   
   }
   glEnd();

   //                                                         cone { <0, 0, 0> .15 <0, 0.4, 0> 0
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  0.4, 0.0);
    glVertex3f(-0.075, 0.0, 0.0);
    glVertex3f( 0.075, 0.0, 0.0);
   glEnd();
 
   glPopMatrix();



   // blocks
   for(float y = -30.0; y<=30.0; y+=10.0) {
      for(float x = -30.0; x<=30.0; x+=10.0) {
   glPushMatrix();
   glTranslatef(x, y, -10.0);
   glRotatef(z_rotation, 0.0, 0.0, 1.0);
   glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.5,  0.5, 0.0);
    glVertex3f(-0.5,  0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f( 0.5, -0.5, 0.0);
   glEnd();
   glPopMatrix();
}
}

   return 0;
}

/*
#declare Recoil = 30*sin(clock*pi/2)

#declare Flare = 1.0-clock*1

light_source {
   <0, -.25, -1.0>
   color <(1-Flare), (1-Flare), (1-Flare)*2>
   rotate frm/32*360*z
}

#declare Cw = 0.15
#declare Cl = 0.55
#declare Sr = 0.16

#declare Thrust = union {
   cone { <0, 0.01, 0> Cw+Flare*-Cw <0, -Cl+Flare*Cl, 0> 0 }
   sphere { <0, 0, 0> Sr+Flare*-Sr/2 }
   pigment { color rgbt <0.5, 0.5, 1, Flare*0.5> }
   finish { ambient 1-0*Flare/2 diffuse 1 }
}

#declare Ship = merge {

*/
   // wings
   //    merge {
   //          cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate (140-Recoil)*z }
   //                cone { <0, 0, 0> .15 <0, 1.1, 0> 0 rotate (-140+Recoil)*z }
   //                      texture { T_Stone22 scale <0.3, 0.3, 0.3> }
   //                         }
   //


//  object { Thrust translate <-0.3, -0.55, 0> }
//   object { Thrust translate < 0.3, -0.55, 0> }

