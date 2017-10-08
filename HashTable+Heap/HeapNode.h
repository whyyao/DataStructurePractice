#ifndef HEAPNODE_H
#define HEAPNODE_H
#include <iostream>

using namespace std;

class HashNode;

class HeapNode{
private:
	HashNode* hash_ptr;
	int data;
   
public:
	HeapNode(){
		hash_ptr = NULL;
	}
	HeapNode(int data_){
		data = data_;
		hash_ptr = NULL;
	}
	HeapNode(int data_, HashNode* hash_ptr_){
		data = data_;
		hash_ptr = hash_ptr_;
	}

	~HeapNode(){
		hash_ptr = NULL;
	}
	
	HashNode* get_hash_ptr(){
		return hash_ptr;
	}
	void set_hash_ptr(HashNode* hash_ptr_){
		hash_ptr = hash_ptr_;
	}

	void set_data(int data_){
		data = data_;
	}
	int get_data(){
		return data;
	}


	void operator = (HeapNode p){
		data = p.get_data();
		hash_ptr = p.get_hash_ptr();
	}
};

#endif