#include <iostream>
#include "HashNode.h"
#include "HeapNode.h"
using namespace std;

class HashTable{
private:
	HashNode** array;
	int size;
public:
	HashTable(int size_){
		size = size_;
		array = new HashNode*[size];
		for (int i=0; i<size; i++){
			array[i]= NULL;
		}
	}

	~HashTable(){
		delete[] array;
	}

	HashNode* insert(int inserted){
		HashNode* result;
		int pos = (inserted % size);
		if(pos < 0 ){ pos+= size;}
		int counter = 0;
		//insert to non first one
		if(array[pos] != NULL){
			HashNode* ptr = array[pos];
			counter = 1;
			while(ptr->has_next()){
				ptr = ptr -> get_next();
				counter++;
			}
			result = new HashNode(inserted);
			ptr -> set_next(result);
			counter ++;
		}
		//insert to the first one 
		else{
			counter = 1;
			array[pos] = new HashNode(inserted);
			result = array[pos];
		}
		// cout<<"inserted in pos "<<pos<<", location: "<<counter<<", number: "<<inserted<<endl;
		return result;
	}

	int delete_item(int deleted){
		if(look_up(deleted) == true){
		int result = -1;
		int pos = (deleted % size);
		if(pos <0){ pos += size;}
		//dont do anything if there isnt one
		if(array[pos] == NULL){
			return -1;
		}
		//delete if the first node is the target
		if(array[pos] -> get_data() == deleted){
			HashNode* next_node = array[pos] -> get_next();
			result = array[pos]-> get_heap_index();
			delete array[pos];
			array[pos] = next_node;
			return result;
		}
		//find the target if its not the first one
		HashNode* prev_ptr = array[pos];
		HashNode* ptr = array[pos];
		while(ptr != NULL && ptr->get_data() != deleted){
			prev_ptr = ptr;
			ptr = ptr -> get_next();
		}
		prev_ptr -> set_next(ptr->get_next());
		result = ptr -> get_heap_index();
		delete ptr;
		return result;
		}
		else{
			return -1;
		}
	}

	bool look_up(int item){
		int pos = item % size;
		if(pos<0){pos+=size;}
		if(array[pos] == NULL){
			return false;
		}
		else{
			HashNode* ptr = array[pos];
			while(ptr -> has_next()){
				if(ptr->get_data() == item){
					return true;
				}
				ptr = ptr->get_next();
			}	
			if(ptr->get_data() == item){
				return true;
			}

		}
		return false;
	}

	void print_hash(int pos){
		cout<<"=================="<<endl;
		HashNode* ptr = array[pos];
		if(ptr != NULL){
			while(ptr -> has_next()){
				cout<< ptr -> get_data()<<endl;
				ptr = ptr -> get_next();
			}
			cout<< ptr -> get_data()<<endl;
		}
		else{
			cout<<"NO NUMBER IN THIS POS"<<endl;
		}
	}
	

};