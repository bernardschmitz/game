

#include "bullet.h"
#include "player.h"
#include "random.h"
#include "texture.h"

#define MOVING      0
#define TRACKING    1
#define TARGET      2



Bullet::Bullet(vector3 p, vector3 v, vector3 f, float l) : Actor(ACT_BULLET, "Bullet", p, v, 10.0, 60.0) { 

   delay = l;

   squid = false;

   collision_flags = ACT_ENEMY;

   force = f;

   mass = 10.0;

   radius = 0.1;

   max_force = f.length();


   for(int i=0; i<4; i++) {
         ang[i] = uniform_random_float(0.0, 2.0*M_PI);
         dis[i] = uniform_random_float(1.5, 4.5);
   }

   //tex = TextureManager::getInstance()->load("bullet.png");
   tex = TextureManager::getInstance()->load("red_yellow_spot.png");
   tex2 = TextureManager::getInstance()->load("squid_beam.png");

}

Bullet::~Bullet() {
   // do nothing
}


void Bullet::action(float dt) {

   oldpos = position;
   //position += velocity;
   //force = ff;

/*
   std::cout << "position " << position
             << " velocity " << velocity
             << " force " << force
             << " mass " << mass << std::endl;
*/
   if(delay < 0.0)
      flags |= ACT_REMOVE;


   // get a list of all enemies
   ActorList al = ActorManager::getInstance()->get_actor_type_list(ACT_ENEMY);

   squid = false;
/*
   if(!squid && al.size() >= 3) {
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

      if(mm < 20.0*20.0) {
         squid = true;

         //float ang, dis;

         pts[0] = A;

         //ang = uniform_random_float(0.0, 2.0*M_PI);
         //dis = uniform_random_float(0.5, 2.5);
         pts[1] = A + dis[0]*vector3(cos(ang[0]), sin(ang[0]), 0.0);

         //ang = uniform_random_float(0.0, 2.0*M_PI);
         //dis = uniform_random_float(0.5, 2.5);
         pts[2] = pts[1] + dis[1]*vector3(cos(ang[1]), sin(ang[1]), 0.0);

         pts[3] = B;

         vector3 d;
         d = !(B-pts[2]);
         pts[4] = B + d*dis[1];

         //ang = uniform_random_float(0.0, 2.0*M_PI);
         //dis = uniform_random_float(0.5, 2.5);
         pts[5] = pts[4] + dis[2]*vector3(cos(ang[2]), sin(ang[2]), 0.0);

         pts[6] = C;

         d = !(C-pts[5]);
         pts[7] = C + d*dis[2];

         //ang = uniform_random_float(0.0, 2.0*M_PI);
         //dis = uniform_random_float(0.5, 2.5);
         pts[8] = pts[7] + dis[3]*vector3(cos(ang[3]), sin(ang[3]), 0.0);

         pts[9] = D;
       }
   }
*/
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

   //static float pink[] = { 0.75, 0.75, 0.75, 0.75 };
   static float pink[] = { 1.0, 1.0, 1.0, 1.0 };
   glColor4fv(pink);

/*
     glBegin(GL_LINE_STRIP);
     for(int i=0; i<12; i++) {
        glVertex3f(pts[i].x, pts[i].y, pts[i].z);
     }
     glEnd();
*/
 /*
 // TODO
  // try quadatric spline, a at player, c at enemy and b some radius away from player
     glBegin(GL_LINE_STRIP);
     int st = 10;
     for(int i=0; i<=st; i++) {
        vector3 p;
        p.quadratic_interpolate(A, D, B, i/(float)st);
        glVertex3f(p.x, p.y, p.z);
     }
    glEnd();
    glBegin(GL_LINE_STRIP);
     st = 10;
     for(int i=0; i<=st; i++) {
        vector3 p;
        p.quadratic_interpolate(A, D, C, i/(float)st);
        glVertex3f(p.x, p.y, p.z);
     }
    glEnd();
*/

   //glBindTexture(GL_TEXTURE_2D, tex);
   TextureManager::getInstance()->bind(tex);
   glEnable(GL_TEXTURE_2D);

   glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   // Enable flat shading -- no need for smooth.
   glShadeModel(GL_FLAT);

   glDisable(GL_DEPTH_TEST);

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

               glTexCoord2f(0.0, 1.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(0.0, 0.0);
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

   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   TextureManager::getInstance()->bind(tex2);
   glBegin(GL_QUADS);
  for(int j=0; j<3; j++) {

     A = pts[j*3+0];
     B = pts[j*3+1];
     C = pts[j*3+2];
     D = pts[j*3+3];

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

     int step = 30 + mm*100/400;
 
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
     
         //glColor4f(0.75, 0.75, 0.75, 0.5);
         glColor4f(1.0, 1.0, 1.0, 0.8);

               glTexCoord2f(0.0, 1.0);
               glVertex3f(p0.x, p0.y, p0.z);
               glTexCoord2f(1.0, 1.0);
               glVertex3f(p1.x, p1.y, p1.z);
               glTexCoord2f(1.0, 0.0);
               glVertex3f(p2.x, p2.y, p2.z);
               glTexCoord2f(0.0, 0.0);
               glVertex3f(p3.x, p3.y, p3.z);


        op = p; 
        //glVertex3f(p.x, p.y, p.z);
     }
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

