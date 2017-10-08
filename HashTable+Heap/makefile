all : prog1

prog1: main.o HashHeap.o HashTable.o Heap.o
	g++ main.o HashHeap.o HashTable.o Heap.o -o prog1

main.o: main.cpp
	g++ -c -g main.cpp

HashHeap.o: HashHeap.cpp 
	g++ -c -g HashHeap.cpp

HashTable.o: HashTable.cpp
	g++ -c -g HashTable.cpp

Heap.o: Heap.cpp
	g++ -c -g Heap.cpp

clean:
	rm -f *.o prog1
