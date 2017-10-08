#include <iostream>
#include "HashTable.cpp"
#include "Heap.cpp"
#include <climits>
using namespace std;

class HashHeap{	
private:
	HashTable* hash;
	Heap* heap;
public:
	HashHeap(){
		hash = new HashTable(97);
		heap = new Heap(10);
	}
	HashHeap(int hash_num, int heap_num){
		hash = new HashTable(hash_num);
		heap = new Heap(heap_num);
	}
	~HashHeap(){
		delete hash;
		delete heap;
	}
	void print_heap(){
		heap->print_heap();
	}
	void print_hash(int i){
		hash->print_hash(i);
	}

	void insert(int inserted){
		if(hash->look_up(inserted) == false){
			HashNode* hash_node = hash->insert(inserted);
			int index = heap->insert(inserted,hash_node);
			hash_node -> set_heap_index(index);
		}
		else{
			cout<<"error: item already exists"<<endl;
			return;
		}
	}

	void lookup(int item){
		if (hash->look_up(item)){
			cout<<"found "<<item<<endl;
		}
		else{
			cout<<item<<" not found"<<endl;
		}
	}

	void deleteMax(){
		int num = heap->delete_max();
		if(num != -INT_MAX){
			cout<<num<<endl;
			hash->delete_item(num);
		}
	}

	void print(){
		heap-> print();
	}

	void delete_me(int item){
		int index = hash->delete_item(item);
		if (index == -1){
			cout<<"error: item not present"<<endl;
			return;
		}
		heap-> delete_item(index);
	}

};
