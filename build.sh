#!/bin/sh
# $Id: build.sh,v 1.2 2003-08-13 02:26:32 bernard Exp $
make clean
make depend
../cross-make.sh OPTIMIZE=1 -j 2
cp main.exe main_op.exe
make clean
../cross-make.sh PROFILE=1 -j 2
cp main.exe main_pf.exe
make clean
../cross-make.sh -j 2
