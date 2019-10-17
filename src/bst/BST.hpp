/** Rosa Miranda
 * A12107125
 * CSE100-A00
 * 
 *Ishikevish, Liz,Niema Moshiri. "3.3 BST Trees" STEPIK Accessed October 2019
 * This file holds the necessary information to build a bst, insert into the tree,
 * find a node on the tree, delete the tree, move through the tree in order
 * and all of its variables.
 */
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
    /** destructor */
    virtual ~BST() { deleteAll(root); }

    /** TODO */
    /** inserts a new node if item doesn't already exist, updates size and
     * height */
    virtual bool insert(const Data& item) {
        if (!root) {
            root = new BSTNode<Data>(item);
            isize++;
            iheight++;
            return true;
        }
	//The following code decides the position of the new node
        BSTNode<Data>* newInsert = root;
        while (newInsert) {
            if (item < newInsert->data) {
                if (newInsert->left) {
                    newInsert = newInsert->left;
                } else {
                    newInsert->left = new BSTNode<Data>(item);
                    newInsert->left->parent = newInsert;
                    newInsert = newInsert->left;
                    isize++;
                    iheight = heightCheck(newInsert, iheight);
                    return true;
                }
            } else if (newInsert->data < item) {
                if (newInsert->right) {
                    newInsert = newInsert->right;
                } else {
                    newInsert->right = new BSTNode<Data>(item);
                    newInsert->right->parent = newInsert;
                    newInsert = newInsert->right;
                    isize++;
                    iheight = heightCheck(newInsert, iheight);
                    return true;
                }
            } else {
                return false;
            }
        }
	return false;
    }

    /** TODO */
    /** looks for item in a bst, returns iterator */
    virtual iterator find(const Data& item) const {
        BSTIterator<Data> currIt = begin();
        if (!root) {
            return end();
        }
        while (currIt != end() && currIt.getNode()->data < item) {
            currIt++;
        }
        if (currIt == end()) {
            return currIt;
        } else if (item < currIt.getNode()->data) {
            return end();
        } else {
            return currIt;
        }
    }
    /** TODO */
    //returns size
    unsigned int size() const { return isize; }

    /** TODO */
    //returns height
    int height() const { return iheight; }

    /** TODO */
    //returns true if bst is empty
    bool empty() const {
        if (!root) {
            return true;
        }
        return false;
    }

    /** TODO */
    //returns an iterator pointing to the first item of the BST
    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    //returns a sorted vector of the BST nodes
    vector<Data> inorder() const {
        vector<Data> finalOrder;
        if (!root) {
            return finalOrder;
        }
        orderHelper(root, &finalOrder);
        return finalOrder;
    }
    /*  checks the the height of the current node against the bst height*/
    int heightCheck(BSTNode<Data>* tallCheck, int currHeight) const {
        int newHeight = 0;
        while (tallCheck->parent) {
            tallCheck = tallCheck->parent;
            newHeight++;
        }
        if (currHeight < newHeight) {
            return newHeight;
        } else {
            return currHeight;
        }
    }

  private:
    /** TODO */
    //returns the smallest node in the BST
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* beginning = root;
        if (!root) {
            return nullptr;
        }
        while (beginning->left) {
            beginning = beginning->left;
        }
        return beginning;
    }
    /** TODO */
    //recursively deletes all the nodes
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (!n) {
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }
    /**Helper method for inorder, recursively moves through bst and returns a
     * sorted vector*/
    static void orderHelper(BSTNode<Data>* nodeOrder,
                            vector<Data>* vectorOrder) {
        while (nodeOrder) {
            orderHelper(nodeOrder->left, vectorOrder);
            vectorOrder->push_back(nodeOrder->data);
            orderHelper(nodeOrder->right, vectorOrder);
            return;
        }
    }
};

#endif  // BST_HPP
