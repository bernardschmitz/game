
#include <ctype.h>
#include <SDL/SDL.h>

extern "C" {
   #include <lua.h>
   #include <lualib.h>
   #include <lauxlib.h>
}


#include "console.h"
#include "text.h"

extern lua_State *L;
extern int exec_lua_string(lua_State *L, const char *buf);




Console *Console::instance = 0;

Console *Console::getInstance() {

   if(instance == 0) {
      instance = new Console();

      printf("created new console instance\n");
   }

   return instance;
}


Console::Console() { 

   buf_max = 1000; 
   hist_max = 100;
   hist_pos = 0;

   prompt = "> ";

   cursor = 0;

   disp_lines = 15; 
   visible = false;
   scroll = false; 

   cursor_rate = 0.15;
   cursor_on = true;
   cursor_time = 0.0;
}

Console::~Console() { 

   printf("console destroyed\n"); 
}


void Console::addString(const char *s) {

   // add string to buffer
   std::string str(s);
   buf.push_back(s);

   // if reached maximum, remove
   if(buf.size() > buf_max) {
      buf.pop_front();
   }
}


void Console::process(float dt) {

   cursor_time -= dt;
   if(cursor_time <= 0.0) {
      cursor_time = cursor_rate;
      cursor_on = !cursor_on;
   }

   if(scroll) {
      spos += dpos*dt;
      delay -= dt;
      if(delay <= 0.0) {
         spos = 0.0;
         scroll = false;
         visible = vis;
      }
      return;
   }

   if(!visible)
      return;

   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_KEYUP:
      case SDL_KEYDOWN:
         keypress(event.key.keysym.sym, event.key.state==SDL_PRESSED, event.key.keysym.unicode&0x7f);
         break;
      }
   }
}

void Console::keypress(int code, bool isdown, char ascii) {

   if(isdown) {
      switch(code) {
   
     case SDLK_RIGHT:
         if(cursor < cmd_line.length())
            cursor++;
         break;
   
      case SDLK_LEFT:
         if(cursor > 0)
            cursor--;
         break;

      case SDLK_END:
         cursor = cmd_line.length();
         break;

      case SDLK_HOME:
         cursor = 0;
         break;

      case SDLK_TAB:
         cmd_line.insert(cursor, "   ");
         cursor += 3;
         break;

      case SDLK_UP:
         if(history.size() > 0) {
            if(hist_pos > 0)
               hist_pos--;
            cmd_line = history[hist_pos];
            cursor = cmd_line.length();
         }
         break;

      case SDLK_DOWN:
         if(history.size() > 0) {
            if(hist_pos < history.size())
               hist_pos++;

            if(hist_pos >= history.size())
               cmd_line.clear();
            else
               cmd_line = history[hist_pos];

            cursor = cmd_line.length();
         }
         break;

      case SDLK_DELETE:
         if(cmd_line.length() > 0) {
            if(cursor < cmd_line.length())
               cmd_line.erase(cursor, 1);
         }
         break; 

      case SDLK_BACKSPACE:
         if(cmd_line.length() > 0) {
            if(cursor > 0) {
               cursor--;
               cmd_line.erase(cursor, 1);
            }
         }
         break; 
     
      default:
         if(isprint(ascii)) {
            cmd_line.insert(cursor, 1, ascii);
            cursor++;
            printf("cmd_line after %c [%s]\n", ascii, cmd_line.c_str());
         }
      } 
   }
   else {
      // escape turns console off
      if(code == SDLK_ESCAPE)
         hide();
   
      if(code == SDLK_RETURN) {

         // add to history
         if(!cmd_line.empty()) {
           printf("adding [%s] to history", cmd_line.c_str());
            history.push_back(cmd_line);
            if(history.size() > hist_max)
               history.pop_front();
            hist_pos = history.size();
         }

         // add to line buffer
         addString((prompt+cmd_line).c_str());

         // attempt to execute cmd_line here...
         exec_lua_string(L, cmd_line.c_str());

         // clear line
         cmd_line.clear();
         cursor = 0;
      }
   }
}

void Console::show() { 

   delay = 0.5;
   spos = disp_lines*TextManager::getInstance()->cellHeight();
   dpos = -disp_lines*TextManager::getInstance()->cellHeight() / delay;
   scroll = true;
   vis = visible = true;
}

void Console::hide() { 

   delay = 0.5; 
   spos = 0.0;
   dpos = disp_lines*TextManager::getInstance()->cellHeight() / delay;
   scroll = true;
   vis = false;
}

void Console::render() {

   if(!visible)
      return;

   TextManager *tm = TextManager::getInstance();
   tm->_begin();

   int w = tm->screenWidth();
   int h = tm->screenHeight();
   int cw = tm->cellWidth();
   int ch = tm->cellHeight();

   glDisable(GL_TEXTURE_2D);
   glColor4f(0.0, 0.0, 0.0, 0.5);
   glBegin(GL_QUADS);
    glVertex2i(0, (int)spos+h-disp_lines*ch);
    glVertex2i(w, (int)spos+h-disp_lines*ch);
    glVertex2i(w, (int)spos+h);
    glVertex2i(0, (int)spos+h);
   glEnd();
   glEnable(GL_TEXTURE_2D);

   glColor4f(1.0, 1.0, 1.0, 0.75);

   int last  = buf.size();
   int first = last - disp_lines + 1;

   if(first < 0)
      first = 0;

   int pos = (int)spos+h - ch;

   if(first < last) {
      for(int i=first; i<last; i++) {
         tm->_draw(0, pos, buf[i].c_str());
         pos -= ch;
      }
   }

   // prompt
   tm->_draw(0, pos, prompt.c_str());

   // command line
   tm->_draw(prompt.length()*cw, pos, cmd_line.c_str());

   // cursor
   if(cursor_on)
      tm->_draw((prompt.length()+cursor)*cw, pos, "_");

   tm->_end();
}

