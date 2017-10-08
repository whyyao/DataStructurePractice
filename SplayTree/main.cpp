#include <iostream>
#include "SplayTree.cpp"
#include <string>


using namespace std;
int main(){
	int operations;
	cin>>operations;
	SplayTree run;
	for(int i=0;i<operations;i++){
		string command = "";
		cin>>command;
		if(command == "insert"){
			int num;
			cin>>num;
			run.insert(num);
		}
		else if(command =="print"){
			run.print();
		}
		else if(command == "find"){
			int num;
			cin>>num;
			run.find(num);
		}
		else if(command == "delete"){
			int num;
			cin>>num;
			run.deleteMe(num);
		}

	}

}