
#include <stdio.h>
extern "C"
{
 #include <lua.h>
 #include <lualib.h>
 #include <lauxlib.h>
}


int leng(int k) {

   return k*k;
}

int leng_glue(lua_State *L) {

   lua_pushnumber(L, (lua_Number)leng((int)lua_tonumber(L, -1)));

   return 1;
}

int fac_glue(lua_State *L, int x) {

   lua_pushstring(L, "fac");
   lua_gettable(L, LUA_GLOBALSINDEX);
   lua_pushnumber(L, x);
   lua_call(L, 1, 1);

   return (int)lua_tonumber(L, -1);
}

void goon_glue(lua_State *L) {
   
   lua_pushstring(L, "leng");
   lua_gettable(L, LUA_GLOBALSINDEX);

   lua_newtable(L);
/*
   lua_pushstring(L, "six");
   lua_pushnumber(L, 6);
   lua_settable(L, -3);
*/
   for(int i=0; i<100; i++) {
      lua_pushnumber(L, i);
      lua_pushnumber(L, i*i*i);
      lua_settable(L, -3);
   }

   lua_call(L, 1, 0);
}
 
int main(int argc, char* argv[ ])
{
   lua_State* L = lua_open();
 
   if (NULL == L)
   {
      printf("Error Initializing lua\n");
      return -1;
   }
 
   // initialize lua standard library functions
/*
   lua_baselibopen(L);
   lua_iolibopen(L);
   lua_strlibopen(L);
   lua_mathlibopen(L);
   lua_tablibopen(L);
*/
  luaopen_base(L);
  luaopen_table(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);
  luaopen_debug(L);

   // Do stuff with lua code.

   lua_register(L, "square", leng_glue);
    
//   char* strLuaInput = "a=2; b=square(a); print(b);\n";
//   lua_dostring(L, strLuaInput);

   lua_dofile(L, "./goon.lua");
   //lua_dofile(L, "./luac.out");

   printf("fac(12) = %d\n", fac_glue(L, 12));

   goon_glue(L);

 
   lua_close(L);   
 
   return 0;
}

