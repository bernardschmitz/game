#!/bin/sh
# $Id: build.sh,v 1.1 2003-08-11 23:30:28 bernard Exp $
make clean
make depend
../cross-make.sh OPTIMIZE=1
cp main.exe main_op.exe
make clean
../cross-make.sh PROFILE=1
cp main.exe main_pf.exe
make clean
../cross-make.sh
