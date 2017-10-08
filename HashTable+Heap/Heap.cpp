
#include <iostream>
#include <math.h>
#include "HeapNode.h"
#include "HashNode.h"
#include <climits>
using namespace std;

class Heap{
private:
	HeapNode* array;
	int current_index;
	int size;
public:
		Heap(){
			current_index = 0;
			array = new HeapNode[10];
		}
		Heap(int size_){
			size = size_;
			current_index = 0;
			array = new HeapNode[size];
			for (int i=0; i<= size; i++){
				array[i].set_data(-INT_MAX);
			}
		}

		Heap(Heap* h){
			size = h->size;
			array = new HeapNode[size];
			for (int i=1 ; i<= size; i++){
				array[i] = h-> array[i];
			}
			current_index = h-> current_index;

		}

		~Heap(){
			delete[] array;
		}

		HeapNode return_index(int index){
			return array[index];
		}

		int insert(int i, HashNode* hash_ptr){
			current_index ++;
			int result = current_index;
			HeapNode *adding = new HeapNode(i,hash_ptr);
			array[current_index]= *adding;
			if(current_index > 1){
				result = percolate_up(current_index);
			}
			return result;
		}
		
		int delete_max(){
			//return the max number
			int num = array[1].get_data();
			if(current_index >1 ){
				array[1].get_hash_ptr() -> set_heap_index(current_index);
				array[current_index].get_hash_ptr() -> set_heap_index(1);
				swap(1, current_index);
				array[current_index].set_data(-INT_MAX);
				current_index--;
				int result = percolate_down(1);
			}
			else if(current_index ==1){
				array[current_index].set_data(-INT_MAX);
				current_index= 0;
			}
			else{
				cout<<"error"<<endl;
				return -INT_MAX;
			}
			return num;
		}

		void delete_item(int index){
			if(current_index >1){
				array[index].get_hash_ptr()-> set_heap_index(current_index);
				array[current_index].get_hash_ptr() -> set_heap_index(index);
				swap(index, current_index);
				array[current_index].set_data(-INT_MAX);
				current_index--;
				int result = percolate_down(index);
			}
			else{
				array[current_index].set_data(-INT_MAX);
				current_index--;
			}
		}

		int percolate_up(int index){
			int final_index=index;
			int i=index;
			int j=floor(i/2);
			while (array[i].get_data() > array[j].get_data()){
				array[i].get_hash_ptr()-> set_heap_index(j);
				array[j].get_hash_ptr()-> set_heap_index(i);
				swap(i, j);
				final_index = j;
				i = j;
				j = floor(j/2);
				if(i<1 || j<1){
					break;
				}
			}
			return final_index;
		}
		int percolate_down(int index){
			int final_index = index;
			int left_child_index = 2* index;
			int right_child_index = 2* index + 1;
			int i= index;
			if (right_child_index > current_index && left_child_index<=current_index){
				if(array[i].get_data() < array[left_child_index].get_data()){
					array[i].get_hash_ptr()-> set_heap_index(left_child_index);
					array[left_child_index].get_hash_ptr()-> set_heap_index(i);
					swap(i,left_child_index);
					final_index = left_child_index;
					return final_index;
				}
				return final_index;
			}
			if(right_child_index > current_index && left_child_index > current_index){
				return final_index;
			}
			while(array[i].get_data() < array[left_child_index].get_data() || array[i].get_data() < array[right_child_index].get_data()){
				if(array[left_child_index].get_data()>array[right_child_index].get_data()){
					array[i].get_hash_ptr()-> set_heap_index(left_child_index);
					array[left_child_index].get_hash_ptr()-> set_heap_index(i);
					swap(i, left_child_index);
					i = left_child_index;
					final_index = left_child_index;
				}
				else{
					array[i].get_hash_ptr()-> set_heap_index(right_child_index);
					array[right_child_index].get_hash_ptr()-> set_heap_index(i);
					swap(i, right_child_index);
					i = right_child_index;
					final_index = right_child_index;
				}
				left_child_index = 2*i;
				right_child_index = 2*i + 1;
				if (right_child_index > current_index && left_child_index<=current_index){
					if(array[i].get_data() < array[left_child_index].get_data()){
						array[i].get_hash_ptr()-> set_heap_index(left_child_index);
						array[left_child_index].get_hash_ptr()-> set_heap_index(i);
						swap(i,left_child_index);
						final_index = left_child_index;
						return final_index ;
					}
					return final_index;

				}
				if(right_child_index > current_index && left_child_index > current_index){
					return final_index;
				}
			}
			return final_index;
		}

		void swap(int index1, int index2){
			int new_i_1 = index2;
			HeapNode temp= array[index2];
			array[index2]= array[index1];
			array[index1]= temp;
		}

		void print(){
			Heap* new_heap = new Heap(this);
			while(new_heap->current_index >= 1){
				cout<<new_heap->delete_max()<<" ";
			}
			cout<<endl;
		}


		void print_heap(){
			cout<<"================"<<endl;
			for(int i=1; i<=current_index; i++){
				cout<<array[i].get_data()<<endl;
			}
		}

};
