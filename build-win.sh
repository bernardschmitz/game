#!/bin/sh
# $Id: build-win.sh,v 1.1 2003-08-11 23:33:40 bernard Exp $
make clean
#make depend
make -f makefile.win OPTIMIZE=1
cp main.exe main_op.exe
make clean
make -f makefile.win PROFILE=1
cp main.exe main_pf.exe
make clean
make -f makefile.win
