# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = -lm

# Define set of implementation source files and object files
SRC = dict3.c data.c linked.c quad.c
SRC2 = dict4.c data.c linked.c quad.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
# Define the executable name(s)
EXE = dict3
EXE2 = dict4
# the first target:
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ) $(EXE)

# the second target:
$(EXE2): $(OBJ2) 
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2) $(LIB)

clean2:
	rm -f $(OBJ2) $(EXE2)

# clean all:
cleanall:
	rm -f $(OBJ) $(EXE)
	rm -f $(OBJ2) $(EXE2)
