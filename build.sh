#!/bin/bash

cd src || exit

windres res/numsyslib_private.rc -O coff -o res/numsyslib_private.res

g++ -c dllmain.cpp bdouble.cpp processor.cpp utils.cpp
g++ -shared -o ../bin/numsyslib.dll \
	-Wl,--out-implib,../bin/numsyslib.dll.a \
	-Wl,--export-all-symbols \
	dllmain.o bdouble.o processor.o utils.o res/numsyslib_private.res

cd ../
