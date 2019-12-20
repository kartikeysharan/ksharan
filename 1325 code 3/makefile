#Name: Kartikey Sharan ID: 1001659433
SRC1 = Code3_1001659433.cpp
SRC2 = SnackLib.cpp
SRC3 = SnackMachine.cpp


OBJ1 = $(SRC1:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)
OBJ3 = $(SRC3:.cpp=.o)

EXE = $(SRC1:.cpp=.e)

HFILES = SnackLib.h SnackMachine.h


CFLAGS = -g -std=c++11

all : $(EXE)

$(EXE): $(OBJ1) $(OBJ2) $(OBJ3)
	g++ $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) -o $(EXE) 

$(OBJ1) : $(SRC1) $(HFILES)
	g++ -c $(CFLAGS) $(SRC1) -o $(OBJ1) 

$(OBJ2) : $(SRC2) $(HFILES) 
	g++ -c $(CFLAGS) $(SRC2) -o $(OBJ2)

$(OBJ3) : $(SRC3) $(HFILES2) 
	g++ -c $(CFLAGS) $(SRC3) -o $(OBJ3)

