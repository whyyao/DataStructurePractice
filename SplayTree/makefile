all: prog2
	make clean

prog2: main.o SplayTree.o
	g++ main.o SplayTree.o -o prog2

main.o: main.cpp
	g++ -c -g main.cpp

SplayTree.o: SplayTree.cpp 
	g++ -c -g SplayTree.cpp

clean:
	rm -f *.o
	echo Clean Done

