
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "lunar.h"

class goon {
   protected:
      int blah;
   public:
      goon(int i) { blah = i; printf("goon %d created\n", blah); }
      virtual ~goon() { printf("goon %d deleted\n", blah); }

      int square() { return blah*blah; }
      int get_blah() { printf("goon get_blah\n"); return blah; }

      // lua methods
      goon(lua_State *L);
      int square(lua_State *L) { lua_pushnumber(L, square()); return 1; }
      virtual int get_blah(lua_State *L) { lua_pushnumber(L, get_blah()); return 1; }

      static const char className[];
      static Lunar<goon>::RegType methods[];
};

const char goon::className[] = "goon";

Lunar<goon>::RegType goon::methods[] = {
   {"square", &goon::square},
   {"get_blah", &goon::get_blah},
   {0,0}
};
   
goon::goon(lua_State *L) {

   blah = (int)luaL_checknumber(L, 1);
   printf("goon %d made from lua\n", blah);
}


class leng : public goon {
   public:
      leng(int i) : goon(i) { printf("leng %d created\n", blah); }
      ~leng() { printf("leng %d deleted\n", blah); }

      int get_blah() { printf("leng get_blah\n"); return blah; }
      int cube() { return blah*blah*blah; }

      // lua methods
      leng(lua_State *L);
      int cube(lua_State *L) { lua_pushnumber(L, cube()); return 1; }
		int get_blah(lua_State *L) { lua_pushnumber(L, get_blah()); return 1; }

      static const char className[];
      static Lunar<leng>::RegType methods[];
};

const char leng::className[] = "leng";

Lunar<leng>::RegType leng::methods[] = {
   {"square", &leng::square},
   {"cube", &leng::cube},
   {"get_blah", &leng::get_blah},
   {0,0}
};
 
leng::leng(lua_State *L) : goon(L) {
//   (int)luaL_checknumber(L, 1);
   printf("leng %d created from lua\n", blah);
}


int hoho(goon *k) {

   printf("this is hoho, blah is %d\n", k->get_blah());

   if(k->get_blah() == 0)
      return 100;
   else {
      if(k->get_blah() > 0)
         return 100;
      else
         return -100;
   }
}

int hoho(lua_State *L) {

/*
   int q = lua_type(L, -1);

   printf("%s\n", lua_typename(L, q));

   if(q == LUA_TUSERDATA) {
      Lunar<goon>::userdataType *ud = static_cast<Lunar<goon>::userdataType*>(lua_touserdata(L, -1));

      printf("%p\n", static_cast<void*>(ud->pT));

      return hoho(ud->pT);
   }
*/


//LUALIB_API void *luaL_checkudata (lua_State *L, int ud, const char *tname) {

  const char *tn;
  if(lua_getmetatable(L, -1)) {
     lua_rawget(L, LUA_REGISTRYINDEX);  /* get registry[metatable] */
     tn = lua_tostring(L, -1);
     if(tn) {
       lua_pop(L, 1);
       if(strcmp(tn, "goon") == 0) {
          goon *p = static_cast<goon*>(lua_touserdata(L, -1));
          printf("%p\n", static_cast<void*>(p));
          lua_pushnumber(L, hoho(p));
          return 1;
       }
       else {
// doen't work right
          if(strcmp(tn, "leng") == 0) {
             goon *p = dynamic_cast<goon*>(lua_touserdata(L, -1));
             printf("%p\n", static_cast<void*>(p));
             lua_pushnumber(L, hoho(p));
             return 1;
          }
        }
     }
  }

  // fail
  lua_pop(L, 1);
  return 0;

/*
   void *p = Lunar<leng>::check(L, 1);

   printf("%p\n", static_cast<void*>(p));
   lua_pushnumber(L, hoho(p));

   return 1;
*/
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
  Lunar<leng>::Register(L);

  lua_register(L, "hoho", hoho);

  leng qq = leng(45);
  printf("hoho on leng %d\n", hoho(&qq));

  // make qq visible to lua
  int QQ = Lunar<leng>::push(L, &qq);
  lua_pushliteral(L, "qq");
  lua_pushvalue(L, QQ);
  lua_settable(L, LUA_GLOBALSINDEX);

  if(argc>1) lua_dofile(L, argv[1]);

  lua_setgcthreshold(L, 0);  // collected garbage
  lua_close(L);
  return 0;
}
