
# $Id: Makefile,v 1.12 2003-07-30 06:34:43 bernard Exp $

CC=g++

LD=$(CC)

#-O9 -funroll-loops -ffast-math -fomit-frame-pointer -malign-double -mcpu=pentiumpro -finline-functions -march=pentiumpro -fno-exceptions
CPPFLAGS = -g -ansi -pedantic -Wall -DHAVE_OPENGL -DWIN32 `sdl-config --cflags` 
#CPPFLAGS = -O3 -ansi -pedantic -Wall -DHAVE_OPENGL -DWIN32 `sdl-config --cflags` 
LFLAGS = -lSDL_image `sdl-config --libs` -lopengl32 -lglu32 -ljpeg -lpng -lz -lm
#LFLAGS = -pg -lSDL_image `sdl-config --libs` -lopengl32 -lglu32 -ljpeg -lpng -lz -lm

HEADERFILES =

OBJS = src/main.o  src/background.o src/player.o src/input.o src/settings.o \
       src/enemy.o src/actor.o src/particle.o src/random.o src/interpolate.o \
       src/bullet.o
#       src/sg/sg.o src/sg/sgIsect.o src/sg/sgPerlinNoise.o src/sg/sgd.o src/sg/sgdIsect.o

SRCS = src/main.cpp  src/background.cpp src/player.cpp src/input.cpp  src/settings.cpp  \
       src/enemy.cpp src/actor.cpp src/particle.cpp src/random.cpp src/interpolate.cpp \
       src/bullet.cpp
#       src/sg/sg.cpp src/sg/sgIsect.cpp src/sg/sgPerlinNoise.cpp src/sg/sgd.cpp src/sg/sgdIsect.cpp

all : main.exe

clean :
	rm -rf main.exe ${OBJS}

main.exe : ${OBJS} 
	$(LD) -o $@ ${OBJS} ${LFLAGS}

depend :
	makedepend -Y -I../cross-tools/i386-mingw32msvc/include \
		-I../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include \
		-I../cross-tools/include \
		-I../cross-tools/i386-mingw32msvc/include/GL  \
		-I../cross-tools/include/SDL \
      -DWIN32 -DHAVE_OPENGL -Dmain=SDL_main  ${SRCS}

view_obj.exe: src/view_obj.o src/view_obj.cpp src/object.c
	$(LD) -o $@ src/view_obj.o ${LFLAGS}


# DO NOT DELETE

src/main.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/main.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/time.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/sys/types.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/main.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/main.o: ../cross-tools/include/SDL/SDL.h
src/main.o: ../cross-tools/include/SDL/SDL_main.h
src/main.o: ../cross-tools/include/SDL/SDL_types.h
src/main.o: ../cross-tools/include/SDL/begin_code.h
src/main.o: ../cross-tools/include/SDL/close_code.h
src/main.o: ../cross-tools/include/SDL/SDL_getenv.h
src/main.o: ../cross-tools/include/SDL/SDL_error.h
src/main.o: ../cross-tools/include/SDL/SDL_rwops.h
src/main.o: ../cross-tools/include/SDL/SDL_timer.h
src/main.o: ../cross-tools/include/SDL/SDL_audio.h
src/main.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/main.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/main.o: ../cross-tools/include/SDL/SDL_joystick.h
src/main.o: ../cross-tools/include/SDL/SDL_events.h
src/main.o: ../cross-tools/include/SDL/SDL_active.h
src/main.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/main.o: ../cross-tools/include/SDL/SDL_keysym.h
src/main.o: ../cross-tools/include/SDL/SDL_mouse.h
src/main.o: ../cross-tools/include/SDL/SDL_video.h
src/main.o: ../cross-tools/include/SDL/SDL_mutex.h
src/main.o: ../cross-tools/include/SDL/SDL_quit.h
src/main.o: ../cross-tools/include/SDL/SDL_version.h
src/main.o: ../cross-tools/include/SDL/SDL_opengl.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/main.o: ../cross-tools/include/SDL/SDL_image.h src/main.h src/vector.h
src/main.o: src/quaternion.h src/actor.h src/background.h src/player.h
src/main.o: src/input.h src/settings.h src/enemy.h src/bullet.h
src/main.o: src/particle.h src/random.h src/interpolate.h
src/background.o: src/background.h src/main.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/background.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/background.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/background.o: ../cross-tools/include/SDL/SDL.h
src/background.o: ../cross-tools/include/SDL/SDL_main.h
src/background.o: ../cross-tools/include/SDL/SDL_types.h
src/background.o: ../cross-tools/include/SDL/begin_code.h
src/background.o: ../cross-tools/include/SDL/close_code.h
src/background.o: ../cross-tools/include/SDL/SDL_getenv.h
src/background.o: ../cross-tools/include/SDL/SDL_error.h
src/background.o: ../cross-tools/include/SDL/SDL_rwops.h
src/background.o: ../cross-tools/include/SDL/SDL_timer.h
src/background.o: ../cross-tools/include/SDL/SDL_audio.h
src/background.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/background.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/background.o: ../cross-tools/include/SDL/SDL_joystick.h
src/background.o: ../cross-tools/include/SDL/SDL_events.h
src/background.o: ../cross-tools/include/SDL/SDL_active.h
src/background.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/background.o: ../cross-tools/include/SDL/SDL_keysym.h
src/background.o: ../cross-tools/include/SDL/SDL_mouse.h
src/background.o: ../cross-tools/include/SDL/SDL_video.h
src/background.o: ../cross-tools/include/SDL/SDL_mutex.h
src/background.o: ../cross-tools/include/SDL/SDL_quit.h
src/background.o: ../cross-tools/include/SDL/SDL_version.h
src/background.o: ../cross-tools/include/SDL/SDL_opengl.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/background.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/background.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/background.o: src/quaternion.h src/actor.h src/settings.h src/player.h
src/player.o: src/player.h src/main.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/player.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/player.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/player.o: ../cross-tools/include/SDL/SDL.h
src/player.o: ../cross-tools/include/SDL/SDL_main.h
src/player.o: ../cross-tools/include/SDL/SDL_types.h
src/player.o: ../cross-tools/include/SDL/begin_code.h
src/player.o: ../cross-tools/include/SDL/close_code.h
src/player.o: ../cross-tools/include/SDL/SDL_getenv.h
src/player.o: ../cross-tools/include/SDL/SDL_error.h
src/player.o: ../cross-tools/include/SDL/SDL_rwops.h
src/player.o: ../cross-tools/include/SDL/SDL_timer.h
src/player.o: ../cross-tools/include/SDL/SDL_audio.h
src/player.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/player.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/player.o: ../cross-tools/include/SDL/SDL_joystick.h
src/player.o: ../cross-tools/include/SDL/SDL_events.h
src/player.o: ../cross-tools/include/SDL/SDL_active.h
src/player.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/player.o: ../cross-tools/include/SDL/SDL_keysym.h
src/player.o: ../cross-tools/include/SDL/SDL_mouse.h
src/player.o: ../cross-tools/include/SDL/SDL_video.h
src/player.o: ../cross-tools/include/SDL/SDL_mutex.h
src/player.o: ../cross-tools/include/SDL/SDL_quit.h
src/player.o: ../cross-tools/include/SDL/SDL_version.h
src/player.o: ../cross-tools/include/SDL/SDL_opengl.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/player.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/player.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/player.o: src/quaternion.h src/actor.h src/input.h src/settings.h
src/player.o: src/enemy.h src/particle.h src/random.h src/bullet.h
src/input.o: src/input.h src/main.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/input.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/input.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/input.o: ../cross-tools/include/SDL/SDL.h
src/input.o: ../cross-tools/include/SDL/SDL_main.h
src/input.o: ../cross-tools/include/SDL/SDL_types.h
src/input.o: ../cross-tools/include/SDL/begin_code.h
src/input.o: ../cross-tools/include/SDL/close_code.h
src/input.o: ../cross-tools/include/SDL/SDL_getenv.h
src/input.o: ../cross-tools/include/SDL/SDL_error.h
src/input.o: ../cross-tools/include/SDL/SDL_rwops.h
src/input.o: ../cross-tools/include/SDL/SDL_timer.h
src/input.o: ../cross-tools/include/SDL/SDL_audio.h
src/input.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/input.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/input.o: ../cross-tools/include/SDL/SDL_joystick.h
src/input.o: ../cross-tools/include/SDL/SDL_events.h
src/input.o: ../cross-tools/include/SDL/SDL_active.h
src/input.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/input.o: ../cross-tools/include/SDL/SDL_keysym.h
src/input.o: ../cross-tools/include/SDL/SDL_mouse.h
src/input.o: ../cross-tools/include/SDL/SDL_video.h
src/input.o: ../cross-tools/include/SDL/SDL_mutex.h
src/input.o: ../cross-tools/include/SDL/SDL_quit.h
src/input.o: ../cross-tools/include/SDL/SDL_version.h
src/input.o: ../cross-tools/include/SDL/SDL_opengl.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/input.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/input.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/input.o: src/quaternion.h src/actor.h
src/settings.o: src/settings.h
src/enemy.o: src/enemy.h src/main.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/enemy.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/enemy.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/enemy.o: ../cross-tools/include/SDL/SDL.h
src/enemy.o: ../cross-tools/include/SDL/SDL_main.h
src/enemy.o: ../cross-tools/include/SDL/SDL_types.h
src/enemy.o: ../cross-tools/include/SDL/begin_code.h
src/enemy.o: ../cross-tools/include/SDL/close_code.h
src/enemy.o: ../cross-tools/include/SDL/SDL_getenv.h
src/enemy.o: ../cross-tools/include/SDL/SDL_error.h
src/enemy.o: ../cross-tools/include/SDL/SDL_rwops.h
src/enemy.o: ../cross-tools/include/SDL/SDL_timer.h
src/enemy.o: ../cross-tools/include/SDL/SDL_audio.h
src/enemy.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/enemy.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/enemy.o: ../cross-tools/include/SDL/SDL_joystick.h
src/enemy.o: ../cross-tools/include/SDL/SDL_events.h
src/enemy.o: ../cross-tools/include/SDL/SDL_active.h
src/enemy.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/enemy.o: ../cross-tools/include/SDL/SDL_keysym.h
src/enemy.o: ../cross-tools/include/SDL/SDL_mouse.h
src/enemy.o: ../cross-tools/include/SDL/SDL_video.h
src/enemy.o: ../cross-tools/include/SDL/SDL_mutex.h
src/enemy.o: ../cross-tools/include/SDL/SDL_quit.h
src/enemy.o: ../cross-tools/include/SDL/SDL_version.h
src/enemy.o: ../cross-tools/include/SDL/SDL_opengl.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/enemy.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/enemy.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/enemy.o: src/quaternion.h src/actor.h src/player.h src/random.h
src/actor.o: src/actor.h src/main.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/actor.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/actor.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/actor.o: ../cross-tools/include/SDL/SDL.h
src/actor.o: ../cross-tools/include/SDL/SDL_main.h
src/actor.o: ../cross-tools/include/SDL/SDL_types.h
src/actor.o: ../cross-tools/include/SDL/begin_code.h
src/actor.o: ../cross-tools/include/SDL/close_code.h
src/actor.o: ../cross-tools/include/SDL/SDL_getenv.h
src/actor.o: ../cross-tools/include/SDL/SDL_error.h
src/actor.o: ../cross-tools/include/SDL/SDL_rwops.h
src/actor.o: ../cross-tools/include/SDL/SDL_timer.h
src/actor.o: ../cross-tools/include/SDL/SDL_audio.h
src/actor.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/actor.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/actor.o: ../cross-tools/include/SDL/SDL_joystick.h
src/actor.o: ../cross-tools/include/SDL/SDL_events.h
src/actor.o: ../cross-tools/include/SDL/SDL_active.h
src/actor.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/actor.o: ../cross-tools/include/SDL/SDL_keysym.h
src/actor.o: ../cross-tools/include/SDL/SDL_mouse.h
src/actor.o: ../cross-tools/include/SDL/SDL_video.h
src/actor.o: ../cross-tools/include/SDL/SDL_mutex.h
src/actor.o: ../cross-tools/include/SDL/SDL_quit.h
src/actor.o: ../cross-tools/include/SDL/SDL_version.h
src/actor.o: ../cross-tools/include/SDL/SDL_opengl.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/actor.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/actor.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/actor.o: src/quaternion.h
src/particle.o: src/particle.h src/main.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/particle.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/particle.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/particle.o: ../cross-tools/include/SDL/SDL.h
src/particle.o: ../cross-tools/include/SDL/SDL_main.h
src/particle.o: ../cross-tools/include/SDL/SDL_types.h
src/particle.o: ../cross-tools/include/SDL/begin_code.h
src/particle.o: ../cross-tools/include/SDL/close_code.h
src/particle.o: ../cross-tools/include/SDL/SDL_getenv.h
src/particle.o: ../cross-tools/include/SDL/SDL_error.h
src/particle.o: ../cross-tools/include/SDL/SDL_rwops.h
src/particle.o: ../cross-tools/include/SDL/SDL_timer.h
src/particle.o: ../cross-tools/include/SDL/SDL_audio.h
src/particle.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/particle.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/particle.o: ../cross-tools/include/SDL/SDL_joystick.h
src/particle.o: ../cross-tools/include/SDL/SDL_events.h
src/particle.o: ../cross-tools/include/SDL/SDL_active.h
src/particle.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/particle.o: ../cross-tools/include/SDL/SDL_keysym.h
src/particle.o: ../cross-tools/include/SDL/SDL_mouse.h
src/particle.o: ../cross-tools/include/SDL/SDL_video.h
src/particle.o: ../cross-tools/include/SDL/SDL_mutex.h
src/particle.o: ../cross-tools/include/SDL/SDL_quit.h
src/particle.o: ../cross-tools/include/SDL/SDL_version.h
src/particle.o: ../cross-tools/include/SDL/SDL_opengl.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/particle.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/particle.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/particle.o: src/quaternion.h src/actor.h src/random.h
src/random.o: src/random.h ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/random.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/random.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/random.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/random.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/interpolate.o: src/interpolate.h src/main.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/interpolate.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/interpolate.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/interpolate.o: ../cross-tools/include/SDL/SDL.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_main.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_types.h
src/interpolate.o: ../cross-tools/include/SDL/begin_code.h
src/interpolate.o: ../cross-tools/include/SDL/close_code.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_getenv.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_error.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_rwops.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_timer.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_audio.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_joystick.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_events.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_active.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_keysym.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_mouse.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_video.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_mutex.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_quit.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_version.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_opengl.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/interpolate.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/interpolate.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/interpolate.o: src/quaternion.h src/actor.h
src/bullet.o: src/bullet.h src/main.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/bullet.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/bullet.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/string.h
src/bullet.o: ../cross-tools/include/SDL/SDL.h
src/bullet.o: ../cross-tools/include/SDL/SDL_main.h
src/bullet.o: ../cross-tools/include/SDL/SDL_types.h
src/bullet.o: ../cross-tools/include/SDL/begin_code.h
src/bullet.o: ../cross-tools/include/SDL/close_code.h
src/bullet.o: ../cross-tools/include/SDL/SDL_getenv.h
src/bullet.o: ../cross-tools/include/SDL/SDL_error.h
src/bullet.o: ../cross-tools/include/SDL/SDL_rwops.h
src/bullet.o: ../cross-tools/include/SDL/SDL_timer.h
src/bullet.o: ../cross-tools/include/SDL/SDL_audio.h
src/bullet.o: ../cross-tools/include/SDL/SDL_byteorder.h
src/bullet.o: ../cross-tools/include/SDL/SDL_cdrom.h
src/bullet.o: ../cross-tools/include/SDL/SDL_joystick.h
src/bullet.o: ../cross-tools/include/SDL/SDL_events.h
src/bullet.o: ../cross-tools/include/SDL/SDL_active.h
src/bullet.o: ../cross-tools/include/SDL/SDL_keyboard.h
src/bullet.o: ../cross-tools/include/SDL/SDL_keysym.h
src/bullet.o: ../cross-tools/include/SDL/SDL_mouse.h
src/bullet.o: ../cross-tools/include/SDL/SDL_video.h
src/bullet.o: ../cross-tools/include/SDL/SDL_mutex.h
src/bullet.o: ../cross-tools/include/SDL/SDL_quit.h
src/bullet.o: ../cross-tools/include/SDL/SDL_version.h
src/bullet.o: ../cross-tools/include/SDL/SDL_opengl.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/windows.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/windef.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winnt.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winerror.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/basetsd.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/pshpack4.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/poppack.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/wincon.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winbase.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/wingdi.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winuser.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winnls.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winver.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winnetwk.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winreg.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/winsvc.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/GL/gl.h
src/bullet.o: ../cross-tools/i386-mingw32msvc/include/GL/glu.h
src/bullet.o: ../cross-tools/include/SDL/SDL_image.h src/vector.h
src/bullet.o: src/quaternion.h src/actor.h
