dliang26-proj7 : dliang26-proj7.o dliang26-Pieces.o dliang26-Exceptions.o dliang26-Board.o dliang26-Board.h dliang26-Exceptions.h dliang26-Pieces.h
	g++ -g -o dliang26-proj7 dliang26-proj7.o dliang26-Pieces.o dliang26-Exceptions.o dliang26-Board.o 

.cpp.o :
	g++ -g -c $<

Debug : dliang26-proj7.cpp
	g++ -o dliang26-proj7 -g -DDEBUG dliang26-proj7.cpp dliang26-Board.cpp dliang26-Pieces.cpp dliang26-Exceptions.cpp

clean :
	rm -rf *.o