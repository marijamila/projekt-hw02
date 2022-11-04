SRC=$(wildcard src/*.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
EXESRC=$(wildcard exesrc/*.c)
BIN=$(wildcard bin/*.bin)
INC=inc/

CFLAGS=-I $(INC)
EXE=exe/test_dft.elf exe/test_idft.elf


.SECONDARY:

all: $(EXE)

exe/%.elf: exesrc/%.o $(OBJ)
	gcc $(OBJ) $< -o $@ -lm

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ) $(EXE) $(BIN)