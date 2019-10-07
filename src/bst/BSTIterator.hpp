#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /** Constructor that initialize the current BSTNode
     *  in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->data; }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }
    BSTNode<Data>* getNode(){
		return this->curr;
    }
    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** TODO */
    bool operator==(BSTIterator<Data> const& other) const { 
	    if(this->curr < other.curr || other.curr < this->curr){
		return false;
	    }
	    return true;
    }

    /** TODO */
    bool operator!=(BSTIterator<Data> const& other) const { 
	    if(this->curr < other.curr  || other.curr < this->curr){
		    return true;
            }
	    return false; 
    }

};

#endif  // BSTITERATOR_HPP
