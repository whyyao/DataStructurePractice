#include "SplayNode.h"
#include <iostream>
#include <queue>
using namespace std;

class SplayTree{
private:
	SplayNode* rootPtr;

	void setLeft(SplayNode* n1, SplayNode* n2){
		n1 -> left = n2; 
		if(n2 != NULL){
			n2 -> parent = n1;
		}
	}

	void setRight(SplayNode* n1, SplayNode* n2){
		n1 -> right = n2;
		if(n2 != NULL){
			n2 -> parent = n1;
		}
	}
	void replaceChild(SplayNode* gp, SplayNode* splayParent, SplayNode* splay ){
		if(gp->left== splayParent){
			setLeft(gp,splay);
		}
		else if (gp->right==splayParent){
			setRight(gp,splay);
		}
	}

	void splayIt(SplayNode* splayMe, SplayNode* splayParent){
		//cout<<"splaying"<<endl;
		if(splayMe == rootPtr){
			//cout<<"returned"<<endl;
			return;
		}
		
		SplayNode* GPPtr = splayParent -> parent;
		if(GPPtr  != NULL){
			//cout<<"GPPtr = "<<GPPtr -> data<<"current root = "<<rootPtr ->data<<endl;
		}
		//cout<<"gpptr: "<<GPPtr->data<<endl;
/*		if(splayMe->data == rootPtr->data){
			return;
		}*/
		//case1
		if(splayParent->data == rootPtr->data){
			//cout<<"Case1"<<endl;
			rotate(splayMe, splayParent);
			rootPtr = splayMe;
			//cout<<"after splaying print"<<endl;
			//print();
			return;
		}
		//case2
		if(((GPPtr->left == splayParent)&&(splayParent -> left  == splayMe))
			|| ((GPPtr->right== splayParent )&&(splayParent -> right  == splayMe))){
			//cout<<"Zig-Zig"<<endl;
			rotate(splayParent, GPPtr);	
			rotate(splayMe, splayParent);
			/*if(GPPtr == rootPtr){
				cout<<"set root ptr"<<endl;
				rootPtr = splayMe;
			}*/
			
			//print();
			//cout<<"after splaying print"<<endl;
			//print();
			return splayIt(splayMe, splayMe->parent);
		}
		//case3
		if(((GPPtr->left == splayParent )&&(splayParent -> right == splayMe))
			|| ((GPPtr->right== splayParent)&&(splayParent -> left== splayMe))){
			//cout<<"Zig-Zag"<<endl;
			rotate(splayMe, splayParent);
			rotate(splayMe, GPPtr);
			/*if(GPPtr == rootPtr){
				rootPtr = splayMe;
			}*/
			//cout<<"after splaying print"<<endl;
			//print();
			return splayIt(splayMe, splayMe->parent);
		}
	}
	void rotate(SplayNode* childPtr, SplayNode* parentPtr){	
		//cout<<"rotating"<<endl;	
		SplayNode* GPPtr = parentPtr->parent;
		//Child ptr is the children of parent
		if(parentPtr->left==childPtr){
		//	cout<<"left-left"<<endl;
			setLeft(parentPtr, childPtr->right);
			childPtr->parent = NULL;
			setRight(childPtr, parentPtr);
		//	cout<<"after seting"<<endl;
		}else if(parentPtr->right== childPtr){
			//cout<<"right-right"<<endl;
			setRight(parentPtr, childPtr->left);
			childPtr->parent = NULL;
			setLeft(childPtr, parentPtr);
		}
		if(GPPtr != NULL){
			replaceChild(GPPtr, parentPtr, childPtr);
		}
		if(parentPtr == rootPtr){
			//cout<<"setting root ptr to "<<childPtr->data<<endl;
			rootPtr = childPtr;
		}
		//cout<<"done rotating"<<endl;
	}

	SplayNode* search(int target, SplayNode* cursor){
		//cout<<"searching"<<endl;
		if(cursor == NULL){
			return NULL;
		}
		if(cursor-> data == target){
			return cursor;
		}
		if((cursor->right ==NULL) && (cursor->data <target)){
		//	cout<<"return this cursor"<<cursor->data<<endl;
			return cursor;
		}
		if((cursor->left ==NULL) && (cursor->data >target)){
		//	cout<<"return this cursor"<<cursor->data<<endl;
			return cursor;
		}
		if(cursor -> data > target){
		//	cout<<"greater than target"<<endl;
			return search(target, cursor-> left);
		}
		if( cursor -> data < target){
		//	cout<<"smaller than target"<<endl;
			return search(target, cursor->right);
		}

		//cout<<"reach here???"<<endl;
	}

	SplayNode* access(int target){
		//cout<<"accessing"<<endl;
		SplayNode* splayAt = search(target, rootPtr);
		//cout<<"DONE SEARCHING"<<endl;
		//cout<<"done searching "<<splayAt-> data<<endl;
		//dubugging

		if(splayAt == NULL){
			return NULL;
		}
		if(splayAt->data == target){
			splayIt(splayAt, splayAt->parent);
			return rootPtr;
		}
		else{
			//cout<<"else, "<<endl;
			if(splayAt == rootPtr){
			//	cout<<"is the root"<<endl;
				return NULL;
			}
			if(splayAt->parent != NULL){
				splayIt(splayAt, splayAt->parent);
			}
			//cout<<"done accessing"<<endl;
			//cout<<"after splaying, the root is"<<rootPtr->data<<endl;
			return NULL;
		}
	}

	SplayTree* split(int target, SplayNode* treePtr){
		//cout<<"spliting, current root is: "<<rootPtr->data<<endl;
		SplayTree* result = new SplayTree[2];
		SplayNode* root = access(target);
		//cout<<"rootPtr data = "<<rootPtr->data<<endl;
		if(rootPtr->data == target){
			cout<<"item "<<target<<" not inserted; already present"<<endl;
			return NULL;
		}

		if(rootPtr->data > target){
			//cout<<"if"<<endl;
			//cout<<"root->data > target"<<endl;
			result[0].rootPtr = rootPtr->left;
			//cout<<"root left"<<rootPtr->left->data<<endl;
			//cout<<"root right"<<rootPtr->right->data<<endl;
			if(result[0].rootPtr!=NULL){	
				result[0].rootPtr->parent = NULL;
			}
			result[1].rootPtr = rootPtr;
			result[1].rootPtr ->left = NULL;
			//cout<<"done spliting, if"<<endl;
			return result;
		}
		else{
			//cout<<"root -> data <= target"<<endl;
			result[1].rootPtr = rootPtr->right;
			//cout<<"setting left"<<endl;
			if(result[1].rootPtr != NULL){
				result[1].rootPtr->parent = NULL;
			}
			//cout<<"setting right"<<endl;
			result[0].rootPtr = rootPtr;
			result[0].rootPtr->right = NULL;
			//cout<<"before return"<<endl;
			return result;
		}
	}

	SplayTree join(SplayTree t1, SplayTree t2){
		//cout<<"start joining"<<endl;
		if(t1.rootPtr == NULL){
			return t2;
		}
		if(t2.rootPtr == NULL){
			return t1;
		}
		int largestNum = largest(t1.rootPtr);
		//cout<<"found largest, number is "<<largestNum<<endl;
		t1.access(largestNum);	
		SplayNode* connecting = t2.rootPtr;
		t1.rootPtr -> right = connecting;
		connecting->parent = t1.rootPtr;
		//cout<<"done joining"<<endl;
		return t1;
	}

	int largest(SplayNode* cursor){
		//cout<<"start finding largest"<<endl;
		if (cursor->right == NULL){
			return cursor->data;
		}
		else{
			return largest(cursor->right);
		}
	}

	void clearQueue(queue<SplayNode*> queue){
		while(!queue.empty()){
			queue.pop();
		}
	}

public:
	SplayTree(){
		rootPtr = NULL;
	}

	void insert(int inserting){
		//cout<<"inserting"<<endl;
		if(rootPtr == NULL){
			rootPtr = new SplayNode(inserting);
			cout<<"item "<<inserting<<" inserted"<<endl;
			//print();
			return;
		}
		SplayTree* result = split(inserting, rootPtr);
		if(result == NULL){
			return;
		}
		//cout<<"done split"<<endl;
		//cout<<"result[0] data"<<result[0].rootPtr->data<<endl;
		SplayNode* newRoot = new SplayNode(inserting);
		//cout<<"newRoot data"<<newRoot->data<<endl;
		newRoot -> left = result[0].rootPtr;

		newRoot -> right = result[1].rootPtr;

		if(newRoot -> left != NULL){
			newRoot -> left -> parent = newRoot;
		}
		if(newRoot -> right != NULL){		
			newRoot -> right -> parent = newRoot;
		}
		rootPtr = newRoot;
		cout<<"item "<<inserting<<" inserted"<<endl;
		//print();
	}

	void deleteMe(int deleting){
		SplayNode* root = access(deleting);
		if (root == NULL){
			cout<<"item "<<deleting<<" not deleted; not present"<<endl;
			return;
		}
		if(rootPtr -> left == NULL && rootPtr -> right == NULL){
			rootPtr = NULL;
			cout<<"item "<<deleting<<" deleted"<<endl;
			return;	
		}
		//cout<<"done accessing"<<endl;
		SplayTree t1,t2;
		t1.rootPtr = root->left;
		t2.rootPtr = root->right;
		if(t1.rootPtr != NULL){
			t1.rootPtr -> parent = NULL;
		}
		if(t2.rootPtr != NULL){
			t2.rootPtr -> parent= NULL;
		}
		SplayTree temp = join(t1, t2);
		rootPtr = temp.rootPtr;
		cout<<"item "<<deleting<<" deleted"<<endl;
	}
	void find(int target){
		bool temp = finding(target);
		if(temp){
			cout<<"item "<<target<<" found"<<endl;
		}
		else{
			cout<<"item "<<target<<" not found"<<endl;
		}
	}

	bool finding(int target){
		SplayNode* result = access(target);
		if(result == NULL){
			return false;
		}
		else{
			return true;
		}
	}

	void print(){
		//cout<<"printing"<<endl;
		SplayNode* cursor;
		if(rootPtr == NULL){
			return;
		}
		queue<SplayNode*> order;
		//clearQueue(order);

		order.push(rootPtr);
		order.push(NULL);
		while(!order.empty()){
			//cout<<"start printing while"<<endl;
			//bool temp = false;
			cursor = order.front();
			order.pop();
			//if (cursor != NULL){
			//	if(order.empty() && ((cursor->left != NULL) || (cursor -> right != NULL))){
					//order.push(NULL);
			//	}
			//}
			if (cursor == NULL){
				cout<<endl;
				continue;
			}else{
				cout<<cursor->data;
				if(order.front() != NULL){
					cout<<", ";
				}
			}
			if(cursor->left != NULL){
				order.push(cursor->left);
				//temp = true;
			}
			if(cursor->right != NULL){
				order.push(cursor ->right);
				//temp = true;
			}
			if(order.front() == NULL){
				order.push(NULL);
			}
			//if(temp == false && order.front() == NULL){order.push(NULL);}
			//cout<<"size: "<<order.size()<<endl;
			//cout<<"end printing while"<<endl;
		}
		//cout<<"done printing"<<endl;

	}



};

