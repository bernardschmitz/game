
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "main.h"
#include "background.h"
#include "player.h"
#include "input.h"
#include "settings.h"
#include "enemy.h"
#include "particle.h"
#include "random.h"
#include "interpolate.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define FS 0
#define WIDTH 800
#define HEIGHT 600

/*
#define FS 1
#define WIDTH 800
#define HEIGHT 600
*/

static Background *bg;
static Enemy *enemy;


static GLint T0 = 0;
static GLint Frames = 0;

static GLuint torus;
static GLuint box;

static GLuint blur;

static int follow = 1;
static int flags = 0;

static GLuint texture[3];

static GLUquadric *fsphere;
static GLUquadric *bsphere;

static GLfloat view_rotx = 0.0, view_roty = 0.0, view_rotz = 90.0;
static GLfloat vel_x = 0.0, vel_y = 0.0;
static GLint gear1, gear2, gear3;
static GLfloat angle = 0.0;

static GLuint world;

  static GLfloat pos[4] =
  {-20.0, 20.0, 20.0, 1.0};
  //{5.0, 5.0, 10.0, 0.0};
  static GLfloat red[4] =
  {0.8, 0.8, 0.0, 0.15};
  static GLfloat green[4] =
  {0.0, 0.8, 0.0, 1.0};
  static GLfloat yellow[4] =
  {0.8, 0.8, 0.0, 1.0};
  static GLfloat blue[4] =
  {0.0, 0.0, 0.8, 0.25};
  static GLfloat lcol[4] =
  { 1.0,  1.0,  1.0, 1.0};
  static GLfloat white[4] =
  {0.8, 0.8, 0.8, 1.0};

  static GLfloat sgen[4] =
  {0.5, 0.0, 0.0, 0.0};
  static GLfloat tgen[4] =
  {0.0, 0.5, 0.0, 0.0};


static void draw(void) {

   static GLfloat fps = 0;
   int i;

   GLint st0 = SDL_GetTicks();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   GLint clear_time = SDL_GetTicks() - st0;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   sgVec3 pos;
   player->getPosition(pos);

   sgVec3 vel;
   player->getVelocity(vel);

   float mag = -15.0*sgLengthVec3(vel);

   if(follow)
      glTranslatef(-pos[0]-15*vel[0], -pos[1]-15*vel[1], mag);
   else
      glTranslatef(-pos[0], -pos[1], -100.0);


   GLint st = SDL_GetTicks();

   bg->render(pos, flags);

   GLint bg_time = SDL_GetTicks() - st;

   st = SDL_GetTicks();

   alEnemy.render();

   player->render();

   alParticles.render();


   sgVec3 A, B, C, D;

   sgCopyVec3(A, pos);
   //sgSetVec3(A, -5.0, 0.0, -8.0);
   sgSetVec3(B,  1.0, -2.0, -8.0);
   sgSetVec3(C,  2.0, 2.0, -8.0);
   sgSetVec3(D,  -2.0, 3.0, -8.0);

   glBegin(GL_LINE_STRIP);
        glVertex3f(A[0], A[1], A[2]);
        glVertex3f(B[0], B[1], B[2]);
        glVertex3f(C[0], C[1], C[2]);
        glVertex3f(D[0], D[1], D[2]);
   glEnd();

   glBegin(GL_LINE_STRIP);
     for(int i=0; i<=10; i++) {
        sgVec3 p;
        quadratic_interpolate(p, A, B, C, i/10.0);
        glVertex3f(p[0], p[1], p[2]);
     }
   glEnd();

   glBegin(GL_LINE_STRIP);
     for(int i=0; i<=10; i++) {
        sgVec3 p;
        cubic_interpolate(p, A, B, C, D, i/10.0);
        glVertex3f(p[0], p[1], p[2]);
     }
   glEnd();



   GLint player_time = SDL_GetTicks() - st;

   SDL_GL_SwapBuffers();

   Frames++;

   GLint t = SDL_GetTicks();
   if(t - T0 >= 5000) {
      GLfloat seconds = (t - T0) / 1000.0;
      fps = Frames / seconds;
      printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
      T0 = t;
      Frames = 0;

      printf("%d %d %d\n", clear_time, bg_time, player_time);
   }


   // pause a little...
   int ww = 1000/48 - (SDL_GetTicks() - st0);

   if(ww > 1)
      SDL_Delay(ww);
}

static void
idle(void)
{
   angle += 1.0;

   input.process();

   player->action();
   alEnemy.action();
   alParticles.action();
}

/* new window size or exposure */
static void
reshape(int width, int height)
{
  GLfloat h = (GLfloat) height / (GLfloat) width;

  //glViewport(0, 0, (GLint) width, (GLint) height);
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -h, h, 1.0, 400.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  glTranslatef(0.0, 0.0, -40.0);
  //gluLookAt(-40.0, 70.0, 210.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 // gluLookAt(0.0, 0.0, 110.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

static void
init(int argc, char *argv[])
{
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lcol);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  fsphere = gluNewQuadric();  
  gluQuadricDrawStyle(fsphere, GLU_LINE);
  //gluQuadricNormals(fsphere, GLU_FLAT);
  bsphere = gluNewQuadric();  
  gluQuadricOrientation(bsphere, GLU_INSIDE);

  world = glGenLists(1);
  glLoadIdentity();
  glNewList(world, GL_COMPILE);
   //glShadeModel(GL_FLAT);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
   gluSphere(bsphere, 1.0, 10, 10);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   gluSphere(fsphere, 1.0, 10, 10);
  glEndList();


//  glEnable(GL_POLYGON_SMOOTH);
//  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  //glEnable(GL_LINE_SMOOTH);
  //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  //glLineWidth(1);


  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEnable(GL_NORMALIZE);


  bg = new Background();

   sgVec3 p =  { -20.0, 20.0, -10.0 };
  
   for(int i=0; i<20; i++) {
      p[0] += 4.0;
      alEnemy.insert(new Enemy(p));
   }


   alParticles.insert(new ParticleSystem());


   player = new Player();


   box = glGenLists(1);
   glNewList(box, GL_COMPILE);
   glBegin(GL_QUADS);
    static GLfloat yellow1[] = { 1.0, 1.0, 0.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow1);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0,  1.0, 1.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f( 1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0,-1.0,  1.0);
    glVertex3f(-1.0,-1.0, -1.0);
    glVertex3f( 1.0,-1.0, -1.0);
    glVertex3f( 1.0,-1.0,  1.0);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 1.0, 1.0,  1.0);
    glVertex3f( 1.0,-1.0,  1.0);
    glVertex3f( 1.0,-1.0, -1.0);
    glVertex3f( 1.0, 1.0, -1.0);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0,-1.0, -1.0);
    glVertex3f(-1.0,-1.0,  1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glEnd();

   glEndList();


/*
   GLuint *data = new GLuint[128*128*sizeof(GLuint)];

   glGenTextures(1, &blur);
   glBindTexture(GL_TEXTURE_2D, blur);
   glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   delete [] data;
*/





//  if (argc > 1 && strcmp(argv[1], "-info")==0) {
     printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
     printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
     printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
     printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));

     GLint texSize;
     glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);
     printf("GL_MAX_TEXTURE_SIZE = %d\n", texSize);
//  }

}

int main(int argc, char *argv[])
{

   srand(time(NULL));








  SDL_Surface *screen;
  int done;
  Uint8 *keys;

  settings.screen_width = WIDTH;
  settings.screen_height = HEIGHT;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

   if(FS)
     screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL|SDL_FULLSCREEN);
   else
     screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL|SDL_RESIZABLE);
  if ( ! screen ) {
    fprintf(stderr, "Couldn't set 300x300 GL video mode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }
  SDL_WM_SetCaption("Gears", "gears");


  init(argc, argv);
  reshape(screen->w, screen->h);
  done = 0;
  while ( ! done ) {
    SDL_Event event;

    idle();
    while ( SDL_PollEvent(&event) ) {
      switch(event.type) {
        case SDL_VIDEORESIZE:
          screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
                                    SDL_OPENGL|SDL_RESIZABLE);
          if ( screen ) {
            reshape(screen->w, screen->h);
          } else {
            /* Uh oh, we couldn't set the new video mode?? */;
          }
          break;

        case SDL_QUIT:
          done = 1;
          break;
      }
    }

  keys = SDL_GetKeyState(NULL);

    if ( keys[SDLK_ESCAPE] ) {
      done = 1;
    }


    if(keys[SDLK_p]) {
       flags = !flags;
    }
    if(keys[SDLK_f]) {
       follow = !follow;
    }
/*
    if ( keys[SDLK_UP] ) {
      vel_x += 0.4*cos(view_rotz*M_PI/180.0)/40.0;
      vel_y += 0.1*sin(view_rotz*M_PI/180.0)/40.0;
    }
    if ( keys[SDLK_DOWN] ) {
      vel_x -= 0.4*cos(view_rotz*M_PI/180.0)/40.0;
      vel_y -= 0.1*sin(view_rotz*M_PI/180.0)/40.0;
    }
    if ( keys[SDLK_LEFT] ) {
      view_rotz += 5.0;
    }
    if ( keys[SDLK_RIGHT] ) {
      view_rotz -= 5.0;
    }

    if(vel_x > 0.5)
       vel_x = 0.5;
    if(vel_x < -0.5)
       vel_x = -0.5;

    if(vel_y > 0.5)
       vel_y = 0.5;
    if(vel_y < -0.5)
       vel_y = -0.5;

    view_rotx += vel_x;
    view_roty += vel_y;
*/

    draw();
  }
  SDL_Quit();


/*
  sgVec3 A, B, C, D;

  sgSetVec3(A, 0.0, 0.0, 0.0);
  sgSetVec3(B, 1.0, 0.0, 0.0);
  sgSetVec3(C, 2.0, 2.0, 0.0);
  sgSetVec3(D, -1.0, -1.0, 0.0);

  sgVec3 p[100];
 
  bezier_curve(p, 4, A, B, C, D); 

  for(int i=0; i<=2*2*2*2; i++)
     printf("%d : %f %f %f\n", i, p[i][0], p[i][1], p[i][2]);

*/
  return 0;             /* ANSI C requires main to return int. */
}
