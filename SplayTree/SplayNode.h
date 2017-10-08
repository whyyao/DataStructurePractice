 #ifndef SPLAYNODE_H
#define SPLAYNODE_H
#include <iostream>

using namespace std;


class SplayNode{
public:
	SplayNode* left;
	SplayNode* right;
	SplayNode* parent;
	int data;
	SplayNode();
	SplayNode(int data_){
		data = data_;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};


#endif
