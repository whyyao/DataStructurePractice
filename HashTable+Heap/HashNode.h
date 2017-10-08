#ifndef HASHNODE_H
#define HASHNODE_H
#include <iostream>

using namespace std;

class HeapNode;

class HashNode{
private:
	HashNode* next;
	int heap_index;
	int data;

public:
	HashNode();
	HashNode(int data_){
		data = data_;
		next= NULL;

	}
	HashNode(int data_, int heap_index_){
		data = data_;
		heap_index = heap_index_;
		next = NULL;
	}

	~HashNode(){
		next = NULL;
	}

	HashNode* get_next(){
		return next;
	}
	void set_next(HashNode* p){
		next = p;
	}

	bool has_next(){
		if (next != NULL){
			return true;
		}
		else{
			return false;
		}
	}

	void set_data(int data_){
		data = data_;
	}
	int get_data(){
		return data;
	}

	void set_heap_index(int heap_index_){
		heap_index = heap_index_;
	}
	int get_heap_index(){
		return heap_index;
	}
};

#endif