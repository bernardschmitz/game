
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

int leng_glue(lua_State *luaVM) {

   lua_pushnumber(luaVM, (lua_Number)leng((int)lua_tonumber(luaVM, -1)));

   return 1;
}
 
int main(int argc, char* argv[ ])
{
   lua_State* luaVM = lua_open();
 
   if (NULL == luaVM)
   {
      printf("Error Initializing lua\n");
      return -1;
   }
 
   // initialize lua standard library functions
   lua_baselibopen(luaVM);
   lua_iolibopen(luaVM);
   lua_strlibopen(luaVM);
   lua_mathlibopen(luaVM);
   // Do stuff with lua code.

   lua_register(luaVM, "square", leng_glue);
    
//   char* strLuaInput = "a=2; b=square(a); print(b);\n";
//   lua_dostring(luaVM, strLuaInput);

   //lua_dofile(luaVM, "./goon.lua");
   lua_dofile(luaVM, "./luac.out");
 
   lua_close(luaVM);   
 
   return 0;
}

