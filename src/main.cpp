
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

extern "C"
{
 #include <lua.h>
 #include <lualib.h>
 #include <lauxlib.h>
}

#include <string>

#include "main.h"

#include "background.h"
#include "player.h"
#include "input.h"
#include "settings.h"
#include "enemy.h"
#include "bullet.h"
#include "particle.h"
#include "random.h"
#include "interpolate.h"
#include "image.h"
#include "texture.h"
#include "text.h"
#include "console.h"

#include <assert.h>

#include <iostream>
#include <map>


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


lua_State *L = 0;

static ActorManager *actor_manager;

static Background *bg;

static Console *console;

static Input *input;

GLuint blurry_spot;

static GLuint box;



static GLUquadric *fsphere;
static GLUquadric *bsphere;

static GLfloat angle = 0.0;

static GLuint world;

  static GLfloat pos[4] =
  {-20.0, 20.0, 20.0, 1.0};
  //{5.0, 5.0, 10.0, 0.0};
  static GLfloat red[4] =
  {0.8, 0.8, 0.0, 0.15};
  static GLfloat blue[4] =
  {0.0, 0.0, 0.8, 0.25};
  static GLfloat lcol[4] =
  { 1.0,  1.0,  1.0, 1.0};


static int delta = 0;

#if 0

struct mem_block {
   size_t n;
   void *p;
   mem_block(size_t nn, void *pp) { n = nn; p = pp; }
   mem_block(const mem_block& m) { n = m.n; p = m.p; }
   mem_block() { n = 0; p = 0; }
   static int max_bytes;
   static void report();

};

typedef std::map<void *, mem_block> BlockMap;

BlockMap block_map;

int mem_block::max_bytes = 0;

void mem_block::report() {

   std::cout << "\nMax mem allocated " << max_bytes << " bytes\n";

   if(block_map.size() == 0) {
      std::cout << "All memory freed!\n";
      return;
   }

   BlockMap::iterator i = block_map.begin();

   while(i != block_map.end()) {
      mem_block m = (*i).second;
      std::cout << "block " << m.p << " size " << m.n << " not freed!\n";
      ++i;
   }

   std::cout << "Done.\n";
}

void *operator new(size_t n) {

   void *p = malloc(n);

//   std::cout << "new " << n << " return " << p << endl;

   mem_block b(n,p);
   block_map[p] = b;

   mem_block::max_bytes += n;

   return p;
}

void *operator new[](size_t n) {

   void *p = malloc(n);

//   std::cout << "new [] " << n << " return " << p << endl;

   mem_block b(n,p);
   block_map[p] = b;

   mem_block::max_bytes += n;

   return p;
}

void operator delete(void *p) {

//   std::cout << "delete " << p << endl;

   BlockMap::iterator i = block_map.find(p);

   if(i == block_map.end()) {
      std::cout << "attempt to free non existant block\n";
   }
   else {
      block_map.erase(i);
      free(p);
   }
}

void operator delete[](void *p) {

//   std::cout << "delete [] " << p << endl;
   BlockMap::iterator i = block_map.find(p);
   if(i == block_map.end()) {
      std::cout << "attempt to free non existant block\n";
   }
   else {
      block_map.erase(i);
      free(p);
   }
}

#endif



int  glue_addEnemy(lua_State *L) {

   float x = (float)luaL_checknumber(L, 1);
   float y = (float)luaL_checknumber(L, 2);

   printf("adding enemy at %f %f\n", x, y);
   actor_manager->insert(new Enemy(vector3(x, y, -10.0)));

   return 0;
}

static int LuaError( lua_State *L ) {

  const char *errormsg = lua_tostring( L, -1 );

  Console::getInstance()->addString(errormsg);

  return 0;
}



/*
** If your system does not support `stdout', you can just remove this function.
** If you need, you can define your own `print' function, following this
** model but changing `fputs' to put the strings at a proper place
** (a console window or a log file, for instance).
*/
static int luaB_print (lua_State *L) {
  int n = lua_gettop(L);  /* number of arguments */
  int i;
  lua_getglobal(L, "tostring");

  std::string out;

  for (i=1; i<=n; i++) {
    const char *s;
    lua_pushvalue(L, -1);  /* function to be called */
    lua_pushvalue(L, i);   /* value to print */
    lua_call(L, 1, 1);
    s = lua_tostring(L, -1);  /* get result */
    if (s == NULL)
      return luaL_error(L, "`tostring' must return a string to `print'");
    if (i>1) out.append("\t");
    out.append(s);
    lua_pop(L, 1);  /* pop result */
  }

  Console::getInstance()->addString(out.c_str());

  return 0;
}






static void draw(void) {

   static int frames = 0;
   static float fps = 10.0;
   static int last = 0;

   int now = SDL_GetTicks();

   //printf("now %d last %d ", now, last);

   if(now - last > 200)
      last = now - 200;
   else
      if(now - last < 1)
         last = now - 1;



   delta = now - last;

   last = now;

   //printf("delta %d %f\n", delta, delta/1000.0);


   //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   vector3 pos(player->getPosition());

   vector3 vel(player->getVelocity());

   float pa = degToRad(player->getZRot());
   vector3 dir(cos(pa), sin(pa), 0.0);

   static float mag = 0.0;

   //mag = -vel.length();
   mag = (mag*100 + -vel.length()*1.5)/101;

   if(input->lock_cam)
      mag = -60.0;

   //printf("mag = %f\n", mag);

   glTranslatef(-pos.x, -pos.y, mag*0.75);


   actor_manager->render();

   //bg->setCenter(vector3(pos.x, pos.y, 0.0));
   bg->setCenter(vector3(pos.x, pos.y, mag*0.75));


   char fs[100];
   sprintf(fs, "fps %3d", (int)fps);
   glColor4f(1.0, 1.0, 1.0, 1.0);
   TextManager::getInstance()->draw(800-strlen(fs)*16, 600-16, fs);

   console->render();

   SDL_GL_SwapBuffers();

   frames++;

   fps = (1000.0/delta + fps*50)/51;

   static int out = 0;

   if(now - out >= 1000) {
      char fs[100];
      sprintf(fs, "delta %d ms fps %f", delta, fps);
      out = now;
      glColor4f(1.0, 1.0, 1.0, 1.0);
      printf("%s\n", fs);
      //console->addString(fs);
   }

   // pause a little...
/*
   int ww = 1000/60 - (SDL_GetTicks() - now);
   if(ww > 1)
      SDL_Delay(ww);
*/

}

static void
idle(void)
{
   angle += 1.0;

   input->process();

   actor_manager->update(delta/1000.0);

   console->process(delta/1000.0);
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


   printf("creating background\n");
   bg = new Background();
   printf("\tdone\n");

   console = Console::getInstance();

   actor_manager->insert(bg);

/*
   actor_manager.insert(new Enemy(vector3(10, 10, -10)));
   actor_manager.insert(new Enemy(vector3(20, 10, -10)));
   actor_manager.insert(new Enemy(vector3(-50, -25, -10)));
   actor_manager.insert(new Enemy(vector3(10, -10, -10)));
*/

   blurry_spot = TextureManager::getInstance()->load("white_spot.png");

   ParticleDesc pd;
   memset((void*)&pd, 0, sizeof(pd));

   pd.n = 1000; 
   pd.spawn_init = pd.n-100;
   pd.spawn_rate = 50;
   pd.texture_id = TextureManager::getInstance()->gl_id(blurry_spot);
   pd.spawn_pos.set(0.0, 0.0, 0.0);
   pd.spawn_radius = 0.1;
   pd.min_life = 1;
   pd.max_life = 5;
   pd.min_size = 0.1;
   pd.max_size = 0.3;
   pd.respawn_on_death = false;
   pd.energy_in_alpha = true;
   pd.size_from_velocity = true;

   //actor_manager.insert(new ParticleSystem(vector3(0.0,0.0,-10.0), vector3(0.0,0.0,0.0), pd));

   player = new Player();
   actor_manager->insert(player);

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

   GLuint gluerr;
   GLubyte tex[128][128][4];
   int x,y,t;
   int hole_size = 63*63; //3300; // ~ == 57.45 ^ 2.

   // Generate a texture index, then bind it for future operations.
   // Iterate across the texture array.

   for(y=0;y<128;y++) {
      for(x=0;x<128;x++) {

        // Make a round dot in the texture's alpha-channel.

         // Calculate distance to center (squared).
         t = (x-64)*(x-64) + (y-64)*(y-64) ;

         if ( t < hole_size) {// Don't take square root; compare squared.
            //tex[x][y]= 240 - (240 * t) / hole_size + ourRand(15);
            tex[x][y][0]=0;   // Outside of the dot, it's transparent.
            tex[x][y][1]=0;   // Outside of the dot, it's transparent.
            tex[x][y][2]=0;   // Outside of the dot, it's transparent.
            tex[x][y][3]=0;   // Outside of the dot, it's transparent.

            tex[x][y][0]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
            tex[x][y][1]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
         //   tex[x][y][2]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
            tex[x][y][3]= 240 - (240 * t) / hole_size + uniform_random_int(0, 15);
         }
         else {
            tex[x][y][0]=0;   // Outside of the dot, it's transparent.
            tex[x][y][1]=0;   // Outside of the dot, it's transparent.
            tex[x][y][2]=0;   // Outside of the dot, it's transparent.
            tex[x][y][3]=0;   // Outside of the dot, it's transparent.
         }



      }
   }


   glGenTextures(1, &blurry_spot);
   glBindTexture(GL_TEXTURE_2D, blurry_spot);

   // The GLU library helps us build MipMaps for our texture.

   if ((gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 4, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, (void *)tex))) {

      fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
   }

   // Some pretty standard settings for wrapping and filtering.
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);


   // Some pretty standard settings for wrapping and filtering.
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
   //glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   // We start with GL_MODULATE mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


//   blurry_spot = texture_manager.load("purple_star.png");

 //  printf("blurry %d %d\n", texture_manager.width(blurry_spot), texture_manager.height(blurry_spot));




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
//  Uint8 *keys;

  int fs = FS;
  int w = WIDTH;
  int h = HEIGHT;

  if(argc > 1) 
     w = atoi(argv[1]);     

  if(argc > 2) 
     h = atoi(argv[2]);     

  if(argc > 3) 
    fs  = atoi(argv[3]);     


  settings.screen_width = w;
  settings.screen_height = h;

printf("attempting %dx%dx32 %s\n", w, h, fs==0?"windowed":"fullscreen");



  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);


   if(fs)
     screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL|SDL_FULLSCREEN);
   else
     screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL);
  if ( ! screen ) {
    fprintf(stderr, "Couldn't set 300x300 GL video mode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }
  SDL_WM_SetCaption("Sword of Cydonia", "Sword of Cydonia");

  SDL_EnableUNICODE(1);
 
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);


 
  input = Input::getInstance(); 

  actor_manager = ActorManager::getInstance();

   L = lua_open();

  luaopen_base(L);
  luaopen_table(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);
  luaopen_debug(L);
  luaopen_loadlib(L);


   lua_register(L, "print", luaB_print);
   lua_register(L, "_ALERT", LuaError );

   lua_register(L, "Enemy", glue_addEnemy );


// gl init
  init(argc, argv);

   lua_dofile(L, "startup.lua");



  reshape(screen->w, screen->h);
  done = 0;
  while ( ! done ) {
    SDL_Event event;

    idle();

    done = input->quit;

    while ( SDL_PollEvent(&event) ) {
      switch(event.type) {
        case SDL_QUIT:
          done = 1;
          break;
/*
        case SDL_KEYUP:
          printf("key %d\n", event.key.keysym.sym);
          if(event.key.keysym.sym = 96)
             console->show(); 
          break;
*/
      }
    }

/*
  keys = SDL_GetKeyState(NULL);

    if ( keys[SDLK_ESCAPE] ) {
      done = 1;
    }
*/

    draw();
  }
  SDL_Quit();


   lua_close(L);


   delete input;


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
#if 0
#ifndef NDEBUG
   atexit(mem_block::report);
#endif
#endif

   return 0;             /* ANSI C requires main to return int. */
}


