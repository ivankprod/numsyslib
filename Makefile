CPP      = g++
WINDRES  = windres

SRC      = src/
RES      = $(SRC)res/numsyslib_private.res
OBJ      = $(SRC)dllmain.o $(SRC)utils.o $(SRC)bdouble.o $(SRC)processor.o $(RES)
LINKOBJ  = $(SRC)dllmain.o $(SRC)utils.o $(SRC)bdouble.o $(SRC)processor.o $(RES)
CXXFLAGS = -ansi -std=gnu++11 -DBUILDING_DLL=1
BIN      = $(SRC)../bin/numsyslib.dll
DEF      = $(SRC)../bin/numsyslib.def
STATIC   = $(SRC)../bin/numsyslib.a

.PHONY: all all-before all-after

all: $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CPP) -shared $(LINKOBJ) -o $(BIN) -Wl,--output-def,$(DEF),--out-implib,$(STATIC),--export-all-symbols

$(SRC)dllmain.o: $(SRC)dllmain.cpp
	$(CPP) -c $(SRC)dllmain.cpp -o $(SRC)dllmain.o $(CXXFLAGS)

$(SRC)utils.o: $(SRC)utils.cpp
	$(CPP) -c $(SRC)utils.cpp -o $(SRC)utils.o $(CXXFLAGS)

$(SRC)bdouble.o: $(SRC)bdouble.cpp
	$(CPP) -c $(SRC)bdouble.cpp -o $(SRC)bdouble.o $(CXXFLAGS)

$(SRC)processor.o: $(SRC)processor.cpp
	$(CPP) -c $(SRC)processor.cpp -o $(SRC)processor.o $(CXXFLAGS)

$(SRC)res/numsyslib_private.res: $(SRC)res/numsyslib_private.rc
	$(WINDRES) -i $(SRC)res/numsyslib_private.rc --input-format=rc -o $(SRC)res/numsyslib_private.res -O coff 
