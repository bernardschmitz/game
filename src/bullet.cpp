

#include "bullet.h"
#include "player.h"

#define MOVING      0
#define TRACKING    1
#define TARGET      2



Bullet::Bullet(vector3 p, vector3 v, int e) : Actor(ACT_BULLET, p, v, vector3(0.0, 0.0, 1.0)) { 

   energy = e;

   squid = false;
}

Bullet::~Bullet() {
   // do nothing
}


void Bullet::action() {

   oldpos = position;
   position += velocity;

   energy--;
   if(energy < 0)
      flags |= ACT_REMOVE;


   // get a list of all enemies
   ActorList al = actor_manager.get_actor_type_list(ACT_ENEMY);

   squid = false;
   if(al.size() >= 3) {
      A = player->getPosition();
      B = al[0]->getPosition();
      C = al[1]->getPosition();
      D = al[2]->getPosition();

      float dAB = (B-A)*(B-A);
     float dBC = (C-A)*(C-A);
     float dCD = (D-A)*(D-A);

     float mm = dAB;
     if(dBC < mm)
        mm = dBC;
     if(dCD < mm)
        mm = dCD;

      if(mm < 20.0*20.0)
         squid = true;
   }
}


void Bullet::render() {

/*
   float white[] = { 1.0, 1.0, 1.0, 1.0 };

   glPushMatrix();
   glTranslatef(pos.x, pos.y, pos.z);

   glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(vel.x, vel.y, vel.z);
   glEnd();

         glBegin(GL_QUADS);
          glNormal3f(0.0, 0.0, 1.0);
          glVertex3f( 0.3,  0.3, 0.0);
          glVertex3f(-0.3,  0.3, 0.0);
          glVertex3f(-0.3, -0.3, 0.0);
          glVertex3f( 0.3, -0.3, 0.0);
         glEnd();


   glPopMatrix();
*/



   glPushMatrix();


   glDisable(GL_LIGHTING);

   glEnable(GL_TEXTURE_2D);

   glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_FLAT);

   glDisable(GL_DEPTH_TEST);

   static float pink[] = { 0.75, 0.75, 0.75, 0.75 };
   glColor4fv(pink);

   //glTranslatef(pos.x, pos.y, pos.z);

   glBegin(GL_QUADS);

         vector3 dir;
         dir = position - oldpos;
         dir.z = 0.0;
         dir.normalize();
         dir *= 0.2;

         //dir = ~(p[i].pos - p[i].oldPos) * p[i].size;

         vector3 up, down, back;

         up.x = -dir.y;
         up.y = dir.x;
         up.z = dir.z;

         down = -up;

         back = -dir;

         vector3 p0, p1, p2, p3;

         p0 = oldpos + up + back;

         p1 = oldpos + down + back;

         p2 = position + down + dir;

         p3 = position + up + dir;

               glTexCoord2f(0.0, 0.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p3.x, p3.y, p3.z);

   glEnd();

/*
   glBegin(GL_LINES);
   for(int i=0; i<n; i++) {
      if(p[i].energy > 0) {
         glColor4fv(p[i].color);
         glVertex3f(p[i].oldPos[0], p[i].oldPos[1], p[i].oldPos[2]);
         glVertex3f(p[i].pos[0], p[i].pos[1], p[i].pos[2]);
      }
   }
   glEnd();
*/

   if(squid) {

   glBegin(GL_QUADS);
     vector3 op(A);
     vector3 p(0.0, 0.0, 0.0);

     float dAB = (B-A)*(B-A);
     float dBC = (C-B)*(C-B);
     float dCD = (D-C)*(D-C);

     float mm = dAB;
     if(dBC > mm)
        mm = dBC;
     if(dCD > mm)
        mm = dCD;

     int step = 30 + mm*120/400;

     for(int i=0; i<=step; i++) {
        p.cubic_interpolate(A, B, C, D, i/(float)step);

         vector3 dir;
         dir = p - op;
         dir.z = 0.0;
         dir.normalize();
         dir *= 0.2;

         //dir = ~(p[i].pos - p[i].oldPos) * p[i].size;

         vector3 up, down, back;

         up.x = -dir.y;
         up.y = dir.x;
         up.z = dir.z;

         down = -up;

         back = -dir;

         vector3 p0, p1, p2, p3;

         p0 = op + up + back;

         p1 = op + down + back;

         p2 = p + down + dir;

         p3 = p + up + dir;
     
//         glColor4f(0.75, 0.75, 0.75, 0.25);
         glColor4f(0.5, 0.5, 0.5, 0.25);

               glTexCoord2f(0.0, 0.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(0.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p3.x, p3.y, p3.z);


        op = p; 
        //glVertex3f(p.x, p.y, p.z);
     }
   glEnd();
}
   glEnable(GL_LIGHTING);
   glDisable(GL_BLEND);
   glDisable(GL_TEXTURE_2D);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_SMOOTH);

   glEnable(GL_DEPTH_TEST);

   glPopMatrix();



}

