
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "sg/sg.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define FS 0
#define WIDTH 640
#define HEIGHT 480

static GLint T0 = 0;
static GLint Frames = 0;

static GLuint torus;
static GLuint box;

static GLuint blur;

static GLuint texture[3];

static GLUquadric *fsphere;
static GLUquadric *bsphere;

static GLfloat view_rotx = 0.0, view_roty = 0.0, view_rotz = 90.0;
static GLfloat vel_x = 0.0, vel_y = 0.0;
static GLint gear1, gear2, gear3;
static GLfloat angle = 0.0;

static GLuint world;

  static GLfloat pos[4] =
  {0.0, 0.0, 200.0, 1.0};
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
  { 10.0,  10.0,  10.0, 1.0};
  static GLfloat white[4] =
  {0.8, 0.8, 0.8, 1.0};

  static GLfloat sgen[4] =
  {0.5, 0.0, 0.0, 0.0};
  static GLfloat tgen[4] =
  {0.0, 0.5, 0.0, 0.0};


static void draw(void) {

   static GLfloat fps = 0;
   int i;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


/*
   // render blur texture
   glViewport(0, 0, 128, 128);
   glPushMatrix();
//   glTranslatef(0.0, 0.0, -200.0);
   glTranslatef(0.0, 0.0, -140.0);
   glTranslatef(0.0, 0.0,  100.0);
   glRotatef(view_rotx, 1.0, 0.0, 0.0);
   glTranslatef(0.0, 0.0, -100.0);
   glRotatef(view_roty, 0.0, 1.0, 0.0);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glCallList(torus);

   glBindTexture(GL_TEXTURE_2D, blur);
   //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);
   glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);
  
   // setup main render 
   glClearColor(0, 0, 0 ,0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glViewport(0, 0, WIDTH, HEIGHT);

*/



/*
   // apply blur/flare
   int times = 25;
   float inc = 0.02f ;

   float spost = 0.0f;
   float alphainc = 0.9f / times;
   float alpha = 0.2f;

   glDisable(GL_TEXTURE_GEN_S);
   glDisable(GL_TEXTURE_GEN_T);

   glEnable(GL_TEXTURE_2D);
   glDisable(GL_DEPTH_TEST);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   glEnable(GL_BLEND);
   glBindTexture(GL_TEXTURE_2D, blur);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   alphainc = alpha / times;

   glBegin(GL_QUADS);
    for(int i=0; i<times; i++) {
       glColor4f(1.0, 1.0, 1.0, alpha);
       glTexCoord2f(0+spost, 1-spost);
       glVertex2f(0,0);

       glTexCoord2f(0+spost, 0+spost);
       glVertex2f(0,HEIGHT);

       glTexCoord2f(1-spost, 0+spost);
       glVertex2f(WIDTH,HEIGHT);

       glTexCoord2f(1-spost, 1-spost);
       glVertex2f(WIDTH,0);

       spost += inc;
       alpha -= alphainc;
    }
   glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, 0);

*/
















   // player
   glPushMatrix();
   //glTranslatef(view_roty/36.0, view_rotx/36.0, -14.5);
   glTranslatef(0, 0, -20);
   glRotatef(view_rotz, 0.0, 0.0, 1.0);
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


   SDL_GL_SwapBuffers();

   Frames++;

   GLint t = SDL_GetTicks();
   if(t - T0 >= 5000) {
      GLfloat seconds = (t - T0) / 1000.0;
      fps = Frames / seconds;
      printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
      T0 = t;
      Frames = 0;
   }
}

static void
idle(void)
{
  angle += 1.0;
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





  if (argc > 1 && strcmp(argv[1], "-info")==0) {
     printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
     printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
     printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
     printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
  }

}

int main(int argc, char *argv[])
{
  SDL_Surface *screen;
  int done;
  Uint8 *keys;

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


    draw();

    SDL_Delay(1000/60);
  }
  SDL_Quit();
  return 0;             /* ANSI C requires main to return int. */
}
