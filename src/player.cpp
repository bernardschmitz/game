
#include "player.h"
#include "input.h"
#include "settings.h"


Player *player;

Player::Player() {

   sgSetVec3(position, 0.0, 0.0, -10.0);
   sgZeroVec3(velocity);

   z_rotation = 0.0;

   thrusting = 0;
   shooting = 0;



   sgVec3 cockpit_verts[20] = {
            {-0.385512, 0.781300, -0.064236}, 
            {-0.940514, -0.403633, -0.157114}, 
            {0.000000, -1.000000, 0.000000}, 
            {-0.940514, 0.212359, 0.123862},
            {-0.000000, -0.845510, 0.182575}, 
            {0.000000, -0.066485, 0.476179}, 
            {-0.000000, -0.262944, -0.122576}, 
            {0.385512, 0.781300, -0.064236}, 
            {0.940514, -0.403633, -0.157114}, 
            {0.940514, 0.212359, 0.123862}, 
            {-0.000000, 1.017013, 0.241674}, 
            {0.000000, 1.800000, 0.000000}, 
            {-0.377465, 0.387925, 0.214742}, 
            {-0.582912, -0.395008, 0.239925}, 
            {-0.272303, -0.133636, 0.383475}, 
            {-0.000000, 0.460622, 0.436603}, 
            {0.000000, -0.457044, 0.366407}, 
            {0.377465, 0.387925, 0.214742}, 
            {0.582912, -0.395008, 0.239925}, 
            {0.272303, -0.133636, 0.383475}  };

   int cockpit_faces[36*3] = {
				 0, 6, 1, 
				 1, 6, 2, 
				 3, 0, 1, 
				 2, 4, 1, 
				 12, 0, 3, 
				 13, 1, 4, 
				 14, 15, 12, 
				 16, 14, 13, 
				 0, 10, 11, 
				 6, 0, 11, 
				 8, 6, 7, 
				 2, 6, 8, 
				 8, 7, 9, 
				 2, 8, 4, 
				 10, 17, 7, 
				 9, 18, 8, 
				 17, 15, 19, 
				 18, 19, 16, 
				 7, 11, 10, 
				 6, 11, 7, 
				 9, 19, 18, 
				 5, 16, 19, 
				 4, 18, 16, 
				 10, 15, 17, 
				 5, 19, 15, 
				 9, 17, 19, 
				 18, 4, 8, 
				 17, 9, 7, 
				 5, 14, 16, 
				 3, 13, 14, 
				 4, 16, 13, 
				 5, 15, 14, 
				 10, 12, 15, 
				 3, 14, 12, 
				 13, 3, 1, 
				 10, 0, 12  };

   sgVec4 cockpit_diffuse = { 0.180451, 0.243609, 0.378947 };


   dl_cockpit = glGenLists(5);	

   glNewList(dl_cockpit, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cockpit_diffuse);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<36; i++) {
       sgVec3 a, b, c;
       sgCopyVec3(a, cockpit_verts[cockpit_faces[i*3+0]]);
       sgCopyVec3(b, cockpit_verts[cockpit_faces[i*3+1]]);
       sgCopyVec3(c, cockpit_verts[cockpit_faces[i*3+2]]);

       sgVec3 ba, bc;

       sgSubVec3(ba, a, b);
       sgSubVec3(bc, c, b);

       sgVec3 n;

       sgVectorProductVec3(n, bc, ba);
       sgNormaliseVec3(n);


       glNormal3fv(n);
       glVertex3fv(a);
       glVertex3fv(b);
       glVertex3fv(c);
    }
    glEnd();
   glEndList();




   sgVec3 wing_verts[5] = {
			{	 0.735932, 0.124324, 0.097324},
			{	 3.166326, -3.713438, -0.677015},
			{	 -0.508937, -0.543261, 0.000000},
			{	 0.016931, 0.000000, -0.058908},
			{	 0.113321, -0.178436, 0.238452}
			};

   int wing_faces[4*3] = { 1, 2, 3,  0, 1, 3,  1, 4, 2,  0, 4, 1  };

   sgVec4 wing_diffuse = { 0.330827, 0.454135, 0.228571 };

   dl_left_wing = dl_cockpit+1;

   glNewList(dl_left_wing, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wing_diffuse);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<4; i++) {
       sgVec3 a, b, c;
       sgCopyVec3(a, wing_verts[wing_faces[i*3+0]]);
       sgCopyVec3(b, wing_verts[wing_faces[i*3+1]]);
       sgCopyVec3(c, wing_verts[wing_faces[i*3+2]]);

       sgVec3 ba, bc;

       sgSubVec3(ba, a, b);
       sgSubVec3(bc, c, b);

       sgVec3 n;

       sgVectorProductVec3(n, bc, ba);
       sgNormaliseVec3(n);


       glNormal3fv(n);
       glVertex3fv(a);
       glVertex3fv(b);
       glVertex3fv(c);
    }
    glEnd();
   glEndList();

   dl_right_wing = dl_cockpit+2;

   glNewList(dl_right_wing, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wing_diffuse);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<4; i++) {
       sgVec3 a, b, c;
       sgCopyVec3(a, wing_verts[wing_faces[i*3+0]]);
       sgCopyVec3(b, wing_verts[wing_faces[i*3+1]]);
       sgCopyVec3(c, wing_verts[wing_faces[i*3+2]]);

       a[0] *= -1.0;
       b[0] *= -1.0;
       c[0] *= -1.0;

       sgVec3 ba, bc;

       sgSubVec3(ba, a, b);
       sgSubVec3(bc, c, b);

       sgVec3 n;

       
       //sgVectorProductVec3(n, bc, ba);
       sgVectorProductVec3(n, ba, bc);
       sgNormaliseVec3(n);

       glNormal3fv(n);
       glVertex3fv(c);
       glVertex3fv(b);
       glVertex3fv(a);
    }
    glEnd();
   glEndList();


   sgVec3 engine_verts[9] = {
           { 1.815618,-2.273985,-0.017416},
			{	 1.377251,-2.370869,-0.387990},
			{	 0.913988,-2.370869,-0.017416},
			{	 0.391991, 3.228739,-0.017416},
			{	 1.340985,-2.284365, 0.309189},
			{	 1.356453,-2.634609, 0.550990},
			{	 0.805463,-2.634609,-0.000000},
			{	 1.356453,-2.634609,-0.550990},
			{	 1.907444,-2.634609, 0.000000}
	};


   int engine_faces[14*3] = {
				 0, 1, 3, 
				 1, 2, 3, 
				 2, 4, 3, 
				 0, 3, 4, 
				 5, 6, 7, 
				 5, 7, 8, 
				 0, 4, 5, 
				 0, 5, 8, 
				 4, 2, 6, 
				 4, 6, 5,
				 2, 1, 7,
				 2, 7, 6, 
				 1, 0, 8, 
				 1, 8, 7 
    };


   sgVec4 engine_diffuse = {  0.619549, 0.634587, 0.724812 };

   dl_left_engine = dl_cockpit+3;

   glNewList(dl_left_engine, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, engine_diffuse);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<14; i++) {
       sgVec3 a, b, c;
       sgCopyVec3(a, engine_verts[engine_faces[i*3+0]]);
       sgCopyVec3(b, engine_verts[engine_faces[i*3+1]]);
       sgCopyVec3(c, engine_verts[engine_faces[i*3+2]]);

       sgVec3 ba, bc;

       sgSubVec3(ba, a, b);
       sgSubVec3(bc, c, b);

       sgVec3 n;

       sgVectorProductVec3(n, bc, ba);
       sgNormaliseVec3(n);


       glNormal3fv(n);
       glVertex3fv(a);
       glVertex3fv(b);
       glVertex3fv(c);
    }
    glEnd();
   glEndList();

   dl_right_engine = dl_cockpit+4;

   glNewList(dl_right_engine, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, engine_diffuse);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<14; i++) {
       sgVec3 a, b, c;
       sgCopyVec3(a, engine_verts[engine_faces[i*3+0]]);
       sgCopyVec3(b, engine_verts[engine_faces[i*3+1]]);
       sgCopyVec3(c, engine_verts[engine_faces[i*3+2]]);

       a[0] *= -1.0;
       b[0] *= -1.0;
       c[0] *= -1.0;

 
       sgVec3 ba, bc;

       sgSubVec3(ba, a, b);
       sgSubVec3(bc, c, b);

       sgVec3 n;

       //sgVectorProductVec3(n, bc, ba);
       sgVectorProductVec3(n, ba, bc);
       sgNormaliseVec3(n);

       glNormal3fv(n);
// reverse because of the scale above
       glVertex3fv(c);
       glVertex3fv(b);
       glVertex3fv(a);
    }
    glEnd();
   glEndList();



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

   // shoot
   if(input.fire) {

      if(shooting < 30)
         shooting++;
   }
   else {
      if(shooting > 0)
         shooting--;
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

   float thrust = 30.0*sin((float)thrusting/30.0*M_PI/2.0); 

   float shoot  = -1*sin((float)shooting/30.0*M_PI/2.0); 

   // ship
   glPushMatrix();

   glTranslatef(position[0], position[1], position[2]);
   glRotatef(-90.0, 0.0, 0.0, 1.0);
   glRotatef(z_rotation, 0.0, 0.0, 1.0);


   glPushMatrix();
   glScalef(0.25, 0.25, 0.25);
   glCallList(dl_cockpit);

   glPushMatrix();
   glRotatef(0.0+thrust, 0.0, 0.0, 1.0);
   glCallList(dl_left_wing);
   glPopMatrix();
   
   glPushMatrix();
   glRotatef(0.0-thrust, 0.0, 0.0, 1.0);
   glCallList(dl_right_wing);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0, shoot, 0.0);
   glCallList(dl_left_engine);
   glCallList(dl_right_engine);
   glPopMatrix();

   glPopMatrix();



#if 0
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
/*
   glBegin(GL_TRIANGLES);
    glNormal3f( 0.0, 0.0, -1);
    glVertex3f(  0.0,  0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f( 0.5, -0.5, 0.0);
   glEnd();
*/

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
 

#endif

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



