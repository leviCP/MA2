#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;


/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();

	const Comparable & findMin() const;
	const Comparable & findMax() const;

	bool contains(const Comparable & x) const;
	void insert(const Comparable & x);
	void remove(const Comparable & x);
	int treeSize() const;
	int treeHeight();
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:

	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt): element(move(theElement)), left(lt), right(rt) {}
	};

	BinaryNode *root;

	BinaryNode * findMin( BinaryNode * t ) const;
	BinaryNode * findMax( BinaryNode * t ) const;
	void makeEmpty( BinaryNode * & t );
	bool contains_h(const Comparable & x, BinaryNode &t) const;
	void insert_h(const Comparable & x, BinaryNode &curNode);
	void remove_h(const Comparable & x, BinaryNode * & rem_node);
	int size_helper(BinaryNode * curNode);
	int height_help(BinaryNode * cur);
	void prt_io_help(BinaryNode* curNode); //io means in order
	
};


/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() {
	this->root = nullptr;
};

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode *& t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}


// // public findMin
template <typename Comparable>
const Comparable & BST<Comparable>::findMin() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable & BST<Comparable>::findMax() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMin(t->right);
    }
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains( const Comparable & x ) const 
{
	
	return contains_h(x, this->root);
}

//definition of private function
/**/
template <typename Comparable>
inline bool BST<Comparable>::contains_h(const Comparable &x, BinaryNode &t) const
{

	if(t->element == x)
	{
		return true;
	}
    if(t == nullptr)//no element x in the list
	{
		return false;
	}
	else if(x < t->element) //go left
	{
		contains_h(x, t->left);
	}
	else if(x > t->element) //go right
	{
		contains_h(x, t->right);
	}
}


// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x) {
	//cout << "**TODO**: insert function" << endl;
	insert_h(x, root);

}

template <typename Comparable>
inline void BST<Comparable>::insert_h(const Comparable &x, BinaryNode &curNode)
{
	if(curNode == nullptr)//hit place to insert
	{
		curNode = new BinaryNode(x, nullptr,nullptr);
	}
	else if(x < curNode->element)
	{
		insert_h(x, curNode->left);
	}
	else if(x < curNode->element)
	{
		insert_h(x, curNode->right);
	}
}



// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove( const Comparable & x ) {
	remove_h(x, this->root);
}

template <typename Comparable>
inline void BST<Comparable>::remove_h(const Comparable &x, BinaryNode *&remNode)
{
	if( remNode == nullptr)
	{
		return; 
	}
	if(x < remNode->element)
	{
		remove_h(x, remNode);
	}
	else if(x > remNode->element)
	{
		remove_h(x, remNode);
	}
	else if(remNode->left != nullptr && remNode != nullptr)
	{
		remNode->element = findMin(remNode->right)->element;
		remove_h(remNode->element, remNode->right);
	}
	else
	{
		BinaryNode *oldNode = remNode;
		remNode = ( remNode->left != nullptr ) ? remNode->left : remNode->right;
		delete oldNode;
	}
}


// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	//cout << "**TODO**: treeSize function" << endl;
	int size = 0;
	return size = size_helper(root);
	
}

template <typename Comparable>
inline int BST<Comparable>::size_helper(BinaryNode *curNode)
{
    if(!curNode)
	{
		return 0;
	}
	else
	{
		return 1 + size_helper(curNode->left) + size_helper(curNode->right);
	}
}


// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight(){

	return height_help(root);
	
}

template <typename Comparable>
inline int BST<Comparable>::height_help(BinaryNode *cur)
{
   if(cur == nullptr)
	{
		return 0;
	}

	int left = height_help(cur->left);
	int right = height_help(cur->right);

	return 1 + max(left, right);
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	prt_io_help(root);
}

template <typename Comparable>
inline void BST<Comparable>::prt_io_help(BinaryNode *curNode)
{
	if(curNode != nullptr)
	{
		prt_io_help(curNode->left);
		cout<<curNode->element<<", "<<endl;
		prt_io_help(curNode->right);
	}
}

// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
	cout << "**TODO**: printLevels function" << endl;
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	cout << "**TODO**: printMaxPath function" << endl;
}

#endif
