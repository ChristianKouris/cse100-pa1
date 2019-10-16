/** This is the iterator for the BSTNode. The iterator can be traversed 
 *  forward but not backwards, has an equality an inequality operator, and
 *  can be derefrenced.
 *  Author: Christian Kouris
 *  Email: ckouris@ucsd.edu
 *  Sources: cplusplus.com/reference/iterator/
 */

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"
using namespace std;

/** The BSTIterator initializes with a BSTNode pointer and when dereferenced,
 *  returns the BSTNode's data. It uses the successor method to traverse 
 *  forward to the next iterator. In the equality and inequality operators,
 *  the iterator compares the BSTNode pointers to determine equality.
 */
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

        /** Post-increment operator. */
        BSTIterator<Data> operator++(int) {
            BSTIterator before = BSTIterator(curr);
            ++(*this);
            return before;
        }

        /** The equality operator. Checks to see if the node 
         *  pointers are equal */
        bool operator==(BSTIterator<Data> const& other) const { 

            return curr == other.curr;

        }

        /** The inequality operator. Checks to see if the Node pointers 
         *  are not the same 
         */
        bool operator!=(BSTIterator<Data> const& other) const { 

            return curr != other.curr;

        }
};

#endif  // BSTITERATOR_HPP
