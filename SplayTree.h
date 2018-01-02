#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <stdbool.h>
#include <assert.h>
#include "Exceptions.h"

using namespace Sexceptions;

template <class T, class C>
class SplayTree {
public://FIXME: node is now public!!!!!
	class Node {
	public:
		T data;
		int sumOfRightTree;
		int sumOfLeftTree;
		Node *right;
		Node *left;
		Node *father;

		Node(const T &data) : data(data), right(NULL), left(NULL), father(NULL) {}

		Node(const Node &node) : data(node.data), right(node.right), left(node.left), father(node.father) {}

		Node &operator=(const Node &node) {
			if (this == &node) {
				return *this;
			}
			data = node.data;
			right = node.right;
			left = node.left;
			father = node.father;
			return *this;
		}

		bool operator==(const Node &node) const {
			return (data == node.data && right == node.right && left == node.left && father == node.father);
		}

		bool operator!=(const Node &node) const {
			return !(*this == node);
		}


	};

	Node *root;
	C compare;

	SplayTree(const C compare) : root(NULL), compare(compare) {}

	~SplayTree()//FIXME: delete anything else??? maybe splaytree???
	{
		this->destroyTreeFromNode(root);
		//compare = NULL;
	}


	void zig(Node *x) {
		if (x == NULL) {
			return;
		}
		Node *y = x->father;
		if (y == NULL) {
			return;
		}
		Node *B = x->right;
		Node *z = y->father;
		x->father = z;
		x->right = y;
		y->father = x;
		y->left = B;
		if (B != NULL) {
			B->father = y;
		}
		if (z != NULL) {
			if (z->left == y) {//FIXME: should be *?
				z->left = x;
				root = x;//FIXME:why???
				return;
			}
			z->right = x;
		}
	}

	void zag(Node *x) {
		if (x == NULL) {
			return;
		}
		Node *y = x->father;
		if (y == NULL) {
			return;
		}
		Node *B = x->left;
		Node *z = y->father;
		x->father = z;
		x->left = y;
		y->father = x;
		y->right = B;
		if (B != NULL) {
			B->father = y;
		}
		if (z != NULL) {
			if (z->left == y) {//FIXME: should be *?
				z->left = x;
				root = x;
				return;
			}
			z->right = x;
		}
	}

void splay(Node* x){
	if(x == NULL || root == NULL || x == root){
		return;
	}
	while(x->father != NULL){
		Node* y = x->father;
		if(y->father == NULL){
			if(y->left == x){
				zig(x);
				root = x;
				return;
			}
			zag(x);
			root = x;
			return;
		}
		Node* z = y->father;
		if(z->father == NULL){
			if(y->left == x && z->left == y){
				zig(x);
				zig(x);
			}
			else if(y->right == x && z->right == y){
				zag(x);
				zag(x);
			}
			else if(y->left == x && z->right == y){
				zig(x);
				zag(x);
			}
			else{
				zag(x);
				zig(x);
			}
			root = x;
		}
		else{
			if(y->left == x && z->left == y){
				zig(x);
				zig(x);
			}
			else if(y->right == x && z->right == y){
				zag(x);
				zag(x);
			}
			else if(y->left == x && z->right == y){
				zig(x);
				zag(x);
			}
			else{
				zag(x);
				zig(x);
			}
		}
	}
	root = x;
}

    Node* findMinNode(){
	if(root == NULL){
		return NULL;
	}
	Node* current = root;
    while (current->left != NULL)
        current = current->left;
    splay(current);
    return current;

}

Node* findMaxNode(){
	if(root == NULL){
				return NULL;
	}
	Node* current = root;
    while (current->right != NULL)
        current = current->right;
    splay(current);
    return current;
}

Node* find_aux(Node* given_root, const T& data){
	if(given_root == NULL){
		return NULL;
	}
	if(given_root->left == NULL && given_root->right == NULL){
		return given_root;
	}
	if(compare(given_root->data,data) == 0){
		return given_root;
	}
	Node* found;
	if(compare(given_root->data,data) < 0 && given_root->right != NULL){
		found = find_aux(given_root->right, data);
		//splay(found);
		return found;
	}
	else if(compare(given_root->data,data) > 0 && given_root->left != NULL){
		found = find_aux(given_root->left, data);
		//splay(found);
		return found;
	}
	return given_root;
}

Node* find(const T& data){
		Node* found = find_aux(root, data);
		splay(found);
		return found;
}

void destroyTreeFromNode(Node *node){
    if(node == NULL) return;
    destroyTreeFromNode(node->right);
    destroyTreeFromNode(node->left);
    delete node;
}

void insert(const T& data){
	if(this == NULL){
		return;
	}
	if(this->root == NULL){
		try{
			Node* new_root = new Node(data);
			this->root = new_root;
			return;
		}
		catch(...){
			throw OutOfMemory();
		}
	}
	Node* found = find(data);
	if(compare(found->data, data) == 0){
		throw AlreadyExist();
	}
	SplayTree* t1;
	try{
		t1 = new SplayTree(compare);
	}
	catch(...){
		throw OutOfMemory();
	}
	SplayTree* t2;
	try{
		t2 = new SplayTree(compare);
	}
	catch(...){
		delete t1;
		throw OutOfMemory();
	}
	split(this, &t1, &t2, data);
	Node* new_root;
	try{
		new_root = new Node(data);
	}
	catch(...){
		delete t1;
		delete t2;
		throw OutOfMemory();
	}
	this->root = new_root;
	this->root->left = t1->root;
	if(t1->root != NULL){
		t1->root->father = this->root;
	}
	this->root = join(this, t2)->root;
	t1->root = NULL;
	delete t1;
	t2->root = NULL;
	delete t2;
}

void remove(const T& data){
	if(this == NULL || this->root == NULL){
		throw NotExist();
	}
	if(compare(find(data)->data, data) != 0){
		throw NotExist();
	}
	SplayTree* t1;
	try{
		t1 = new SplayTree(compare);
	}
	catch(...){
		throw OutOfMemory();
	}
	t1->root = this->root->left;
	if(t1->root != NULL){
		t1->root->father = NULL;
	}
	SplayTree* t2;
	try{
		t2 = new SplayTree(compare);
	}
	catch(...){
		delete t1;
		throw OutOfMemory();
	}
	t2->root = this->root->right;
	if(t2->root != NULL){
		t2->root->father = NULL;
	}
	Node* removed = this->root;
	delete removed;
	if(t1->root == NULL && t2->root == NULL){
		this->root = NULL;
		delete t1;
		delete t2;
		return;
	}
	this->root = join(t1,t2)->root;
	t1->root = NULL;
	delete t1;
	t2->root = NULL;
	delete t2;
}



};

template <class T, class C>
SplayTree<T,C>* join(SplayTree<T,C>* tree1, SplayTree<T,C>* tree2){
	if(tree1 == NULL || tree1->root == NULL){
		return tree2;
	}
	if(tree2 == NULL || tree2->root == NULL){
		return tree1;
	}
	tree1->findMaxNode();
	tree1->root->right = tree2->root;//FIXME:should be copy??
	tree2->root->father = tree1->root;
	return tree1;
}

template <class T, class C>
void split(SplayTree<T,C>* tree, SplayTree<T,C>** tree1, SplayTree<T,C>** tree2, const T& pivit){
	if(tree == NULL){
		*tree1 = NULL;
		*tree2 = NULL;
		return;
	}
	(*tree1)->compare = tree->compare;
	(*tree2)->compare = tree->compare;
	if(tree->root == NULL){
		(*tree1)->root = NULL;
		(*tree2)->root = NULL;
		return;
	}
	tree->find(pivit);
	if(tree->compare(tree->root->data,pivit) <= 0){//FIXME:should be copy???
		(*tree1)->root = tree->root;
		(*tree2)->root = tree->root->right;
		if((*tree2)->root != NULL){
			(*tree2)->root->father = NULL;
		}
		(*tree1)->root->right = NULL;
		return;
	}
	(*tree2)->root = tree->root;
	(*tree1)->root = tree->root->left;
	if((*tree1)->root != NULL){
		(*tree1)->root->father = NULL;
	}
	(*tree2)->root->left = NULL;
}


#endif /* SPLAYTREE_H_ */
