
# $Id: Makefile,v 1.1.1.1 2003-07-11 01:14:28 bernard Exp $

CC=g++

LD=$(CC)

CPPFLAGS = -ansi -pedantic -Wall -g -DHAVE_OPENGL -DWIN32 `sdl-config --cflags` 
LFLAGS = `sdl-config --libs` -lopengl32 -lglu32 -lSDL_image -ljpeg -lpng -lz -lm

HEADERFILES =

OBJS = src/main.o  \
       src/sg/sg.o src/sg/sgIsect.o src/sg/sgPerlinNoise.o src/sg/sgd.o src/sg/sgdIsect.o

SRCS = src/main.cpp  \
       src/sg/sg.cpp src/sg/sgIsect.cpp src/sg/sgPerlinNoise.cpp src/sg/sgd.cpp src/sg/sgdIsect.cpp

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



# DO NOT DELETE

src/main.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/main.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
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
src/main.o: ../cross-tools/include/SDL/SDL_image.h src/sg/sg.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/main.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/main.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sg.o: src/sg/sg.h ../cross-tools/i386-mingw32msvc/include/math.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/sg/sg.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/sg/sg.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/sg/sg.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/sg/sg.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/sg/sgIsect.o: src/sg/sg.h ../cross-tools/i386-mingw32msvc/include/math.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/sg/sgIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/sg/sgIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/sg/sgIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/sg/sgIsect.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/sg/sgPerlinNoise.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/sg/sgPerlinNoise.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/time.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/sys/types.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/math.h
src/sg/sgPerlinNoise.o: src/sg/sg.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/sg/sgPerlinNoise.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sgPerlinNoise.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/sg/sgd.o: src/sg/sg.h ../cross-tools/i386-mingw32msvc/include/math.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/sg/sgd.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/sg/sgd.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/sg/sgd.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/sg/sgd.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
src/sg/sgdIsect.o: src/sg/sg.h ../cross-tools/i386-mingw32msvc/include/math.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/_mingw.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/float.h
src/sg/sgdIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/float.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/assert.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/stdio.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/stddef.h
src/sg/sgdIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stddef.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/stdarg.h
src/sg/sgdIsect.o: ../cross-tools/lib/gcc-lib/i386-mingw32msvc/3.2.3/include/stdarg.h
src/sg/sgdIsect.o: ../cross-tools/i386-mingw32msvc/include/stdlib.h
