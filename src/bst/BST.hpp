#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    virtual ~BST() { deleteAll(root); }

    /** TODO */
    virtual bool insert(const Data& item) {
	    if(!root){
		root = new BSTNode<Data>(item);
		isize++;
		iheight++;
	    }
	    BSTNode<Data>* newInsert = root;
	    while(newInsert){
		   if(item < newInsert->data){
			if(newInsert->left){
				newInsert = newInsert->left;
			}else{
				newInsert->left = new BSTNode<Data>(item);
				newInsert->left->parent = newInsert;
				newInsert = newInsert->left;
				isize++;
				iheight = heightCheck(newInsert, iheight);
				return true;
			}
		   }else if(newInsert->data < item){
			   if(newInsert->right){
				newInsert = newInsert->right;
			   }else{
				newInsert->right = new BSTNode<Data>(item);
				newInsert->right->parent = newInsert;
				newInsert = newInsert->right;
				isize++;
				iheight = heightCheck(newInsert, iheight);
				return true;
			   }
		   }else{
			return false;
		   }
	    } 
    }

    /** TODO */
    virtual iterator find(const Data& item) const { 
	    BSTIterator<Data> currIt = begin();
	    while(currIt.getNode()->data < item){
		currIt++;
	    }
	    if(item < currIt.getNode()->data){
		return end();
	    }else{
		return currIt;
	    }
    }


    /** TODO */
    unsigned int size() const { 	    
	    return isize;
    }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const { 
	    if(!root){
		    return true;
	    }
	    return false; 
    }

    /** TODO */
    iterator begin() const { return BST::iterator(root); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
	vector<Data> finalOrder;
     	    if(!root){
		return finalOrder;	
	    }
	orderHelper(root, finalOrder);
	return finalOrder;
    }
    int heightCheck(BSTNode<Data>* tallCheck, int currHeight)const{
	int newHeight = 0;
	while(tallCheck->parent){
		tallCheck = tallCheck->parent;
		newHeight++;
	}
	if(currHeight < newHeight){
		return newHeight;
	}else{
		return currHeight;
	}
    }
  private:
    /** TODO */
    static BSTNode<Data>* first(BSTNode<Data>* root) { 
	    BSTNode<Data>* findRoot = root;
	    while(findRoot->parent){
		    findRoot = findRoot->parent;
	    }
	    return findRoot; 
    }
    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
	    if(!n){
		return;
	    }
	    deleteAll(n->left);
	    deleteAll(n->right);
	    delete n; 
    }
    static void orderHelper(BSTNode<Data>* nodeOrder, vector<Data> &vectorOrder ){
	    while(nodeOrder){
		orderHelper(nodeOrder->left, vectorOrder);
		vectorOrder.push_back(nodeOrder->data);
		orderHelper(nodeOrder->right, vectorOrder);
		return;
	    }
    }


};

#endif  // BST_HPP
