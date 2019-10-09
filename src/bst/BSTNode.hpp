#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** TODO */
    BSTNode(const Data& d) : data(d) {
	left=right=parent=0;
    }

    /** TODO */
    BSTNode<Data>* successor() {
	 BSTNode<Data>* nextNode = this;
	 if(!this){
		return nullptr;
	 }
	 if(nextNode->right){
		nextNode = nextNode->right;
		while(nextNode->left){
			nextNode = nextNode->left;
		}
		return nextNode;
	 }else{
		while(nextNode->parent){
			if(!(nextNode < nextNode->parent->left) && !(nextNode->parent->left < nextNode)){
				return nextNode;
			}else{
				nextNode = nextNode->parent;
				
			}
		}
		return nullptr;
	 }
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
