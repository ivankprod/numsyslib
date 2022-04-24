CPP      = g++
WINDRES  = windres
RM       = rm

SRC     = src/
INC     = -I"$(CURDIR)/include"
RES     = res/numsyslib_private.res
OBJ     = $(SRC)dllmain.o $(SRC)utils.o $(SRC)bdouble.o $(SRC)processor.o $(RES)
LINKOBJ = $(SRC)dllmain.o $(SRC)utils.o $(SRC)bdouble.o $(SRC)processor.o $(RES)
FLAGS   = $(INC) -ansi -std=gnu++11 -DBUILDING_DLL=1 
BIN     = bin/numsyslib.dll
DEF     = bin/numsyslib.def
STATIC  = bin/numsyslib.a

.PHONY: all all-before all-after

all: $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CPP) -shared $(LINKOBJ) -o $(BIN) -Wl,--output-def,$(DEF),--out-implib,$(STATIC),--export-all-symbols

$(SRC)dllmain.o: $(SRC)dllmain.cpp
	$(CPP) -c $(SRC)dllmain.cpp -o $(SRC)dllmain.o $(FLAGS)

$(SRC)utils.o: $(SRC)utils.cpp
	$(CPP) -c $(SRC)utils.cpp -o $(SRC)utils.o $(FLAGS)

$(SRC)bdouble.o: $(SRC)bdouble.cpp
	$(CPP) -c $(SRC)bdouble.cpp -o $(SRC)bdouble.o $(FLAGS)

$(SRC)processor.o: $(SRC)processor.cpp
	$(CPP) -c $(SRC)processor.cpp -o $(SRC)processor.o $(FLAGS)

res/numsyslib_private.res: res/numsyslib_private.rc
	$(WINDRES) -i res/numsyslib_private.rc --input-format=rc -o res/numsyslib_private.res -O coff

clean:
	${RM} $(OBJ) $(BIN) $(DEF) $(STATIC)
