#include <iostream>
#include "HashHeap.cpp"
#include <string>
// #include "HashTable.cpp"
// #include "Heap.cpp"
// #include "HeapNode.h"
// #include "HashNode.h"

using namespace std;
int main(){
	int size;
	cin>>size;
	int functions;
	cin>>functions;
	HashHeap run(size, functions);
	for(int i=0;i<functions; i++){
		string command = "";
		cin>>command;
		if(command == "insert"){
			int num;
			cin>>num;
			run.insert(num);
		}
		else if(command == "deleteMax"){
			run.deleteMax();
		}
		else if(command =="print"){
			run.print();
		}
		else if(command == "lookup"){
			int num;
			cin>>num;
			run.lookup(num);
		}
		else if(command == "delete"){
			int num;
			cin>>num;
			run.delete_me(num);
		}

	}

}
