CC = g++
CFLAGS = -Wall
SRC = src/main.cpp
TRG = bin/main

DBG = gdb
DBGCFLAGS = -g -Wall
DBGFLAGS = 

all: $(TRG).bin $(TRG)-dbg.bin clean-obj run

cc: $(TRG).bin

cc-dbg: $(TRG)-dbg.bin

$(TRG).bin: $(TRG).o
	$(CC) $(TRG).o -o $(TRG).bin

$(TRG).o: $(SRC)
	$(CC) -c $(CFLAGS) $(SRC) -o $(TRG).o

$(TRG)-dbg.bin: $(TRG)-dbg.o
	$(CC) $(TRG)-dbg.o -o $(TRG)-dbg.bin

$(TRG)-dbg.o: $(SRC)
	$(CC) -c $(DBGCFLAGS) $(SRC) -o $(TRG)-dbg.o
	
clean-obj:
	rm -rf ./bin/*.o

clean: clean-obj
	rm -rf ./bin/*.bin ./img/resultados/*.* ./img/resultados/*_*

run: $(TRG).bin
	./$(TRG).bin

run-dbg: $(TRG)-dbg.bin
	$(DBG) $(DBGFLAGS) $(TRG)-dbg.bin

run-vgd: $(TRG).bin
	valgrind --leak-check=full -s ./$(TRG).bin