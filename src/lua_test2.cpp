
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "src/lunar.h"

class goon {
   protected:
      int blah;
   public:
      goon(int i) { blah = i; printf("goon %d created\n", blah); }
      goon(const goon& g) { blah = g.blah; printf("copy goon %d created\n", blah); }

      virtual ~goon() { printf("goon %d deleted\n", blah); }

      void square() { printf("goon square\n"); blah = blah*blah; }
      int get_blah() { printf("goon get_blah\n"); return blah; }

      // lua methods
      goon(lua_State *L);
      int square(lua_State *L) { square(); return 0; } //lua_pushnumber(L, square()); return 1; }
      virtual int get_blah(lua_State *L) { lua_pushnumber(L, get_blah()); return 1; }

      static int add(lua_State *L);

      static const char className[];
      static Lunar<goon>::RegType methods[];

      friend goon operator+(const goon& a, const goon& b) { printf("+\n"); return goon(a.blah + b.blah); }
};


int goon::add(lua_State *L) {

   Lunar<goon>::push(L, new goon(*(Lunar<goon>::check(L, 1)) + *(Lunar<goon>::check(L, 2))), true);
   return 1; 
}


const char goon::className[] = "goon";

Lunar<goon>::RegType goon::methods[] = {
   {"square", &goon::square},
   {"get_blah", &goon::get_blah},
   {0,0}
};
   
goon::goon(lua_State *L) {

   if(lua_type(L, 1) == LUA_TUSERDATA) {
      goon *g = Lunar<goon>::check(L,1);
      if(g) {
         blah = g->blah;
         printf("copy goon %d made from lua\n", blah);
      }
   }
   else {
      blah = (int)luaL_checknumber(L, 1);
      printf("goon %d made from lua\n", blah);
   }
}



int main(int argc, char *argv[])
{
  lua_State *L = lua_open();

  luaopen_base(L);
  luaopen_table(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);
  luaopen_debug(L);

  Lunar<goon>::Register(L);

  lua_register(L, "add", goon::add);

  goon A(5);

  // make qq visible to lua
  int q = Lunar<goon>::push(L, &A);
  lua_pushliteral(L, "A");
  lua_pushvalue(L, q);
  lua_settable(L, LUA_GLOBALSINDEX);

  if(argc>1) lua_dofile(L, argv[1]);

  lua_setgcthreshold(L, 0);  // collected garbage
  lua_close(L);
  return 0;
}
