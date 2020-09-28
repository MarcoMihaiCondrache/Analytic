#!/usr/bin/env bash

mkdir -p lib

#START COMPILING ANALYTIC
cd analytic
mkdir -p src/obj
gcc -c -o src/obj/functions.o src/functions.c
gcc -c -o src/obj/geometry.o src/geometry.c
gcc -c -o src/obj/plane.o src/plane.c
gcc -c -o src/obj/scale.o src/scale.c
gcc -c -o src/obj/analytic.o src/analytic.c
cd ../lib
ar cr libAnalytic.a ../analytic/src/obj/geometry.o ../analytic/src/obj/functions.o ../analytic/src/obj/plane.o ../analytic/src/obj/scale.o ../analytic/src/obj/analytic.o
cd ..
#END COMPILING ANALYTIC

#START COMPILING LOG
cd log
mkdir -p src/obj
gcc -c -o src/obj/log.o src/log.c -DLOG_USE_COLOR
cd ../lib
ar cr liblog.a ../log/src/obj/log.o
cd ..
#END COMPILING LOG

#START COMPILING UI
cd ui
mkdir -p src/obj
gcc -c -o src/obj/input.o src/input.c
gcc -c -o src/obj/output.o src/output.c
cd ../lib
ar cr libui.a ../ui/src/obj/input.o ../ui/src/obj/output.o
cd .. 
#END COMPILING UI

#FULL LINK AND COMPILE
gcc -I. -Llib -o draw draw.c -lSDL2 -lm  -lAnalytic -llog -lui
