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

        /** This is the initializer for the constructor of the BSTNode. The
         *  data variable is set and the parent and children nodes are null
         *  Parameter: data - the general data that the Node will represent
         */
        BSTNode(const Data& d) : data(d) {

            parent = nullptr;
            right = nullptr;
            left = nullptr;

        }

        /** The successor function will return the smallest value node
         *  that has a greater data value than the current node
         */
        BSTNode<Data>* successor() {

            //Case 1: successor is in the right subtree
            BSTNode<Data>* successor = right;
            // it will only go through this loop if right exists
            while( successor != nullptr ) {

                //after we go right the first time, we only want to go left
                if( successor->left != nullptr ) {
                    successor = successor->left;
                } else {
                    return successor;
                }

            }

            //Case 2: successor is a parent
            successor = this;
            //loop through the parents to see if they branch left
            while (successor->parent != nullptr ) {

                if( successor->parent->left == successor) {
                    return successor->parent;
                }

                successor = successor->parent;

            }

            //Case 3: there is no successor
            return nullptr;

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
