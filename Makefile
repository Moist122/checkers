CC = g++
CFLAGS = -c -std=c++11

all: checkers
	./checkers
checkers: checkers.o main.o board.o square.o pawn.o
	$(CC) -o checkers main.o checkers.o board.o square.o pawn.o
main.o: main.cpp checkers.hh
	$(CC) $(CFLAGS) main.cpp
checkers.o: checkers.hh checkers.cpp pawn.hh board.hh square.hh comparators.hh
	$(CC) $(CFLAGS) checkers.cpp
board.o: board.hh board.cpp pawn.hh square.hh checkers.hh
	$(CC) $(CFLAGS) board.cpp
square.o: square.hh square.cpp checkers.hh
	$(CC) $(CFLAGS) square.cpp
pawn.o: pawn.hh pawn.cpp checkers.hh
	$(CC) $(CFLAGS) pawn.cpp
clean:
	rm *.o checkers