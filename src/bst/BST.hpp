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

        /** Destructor method for BST. Deletes all nodes using deleteAll
         *  Parameter: root - the root node of the BST
         */
        virtual ~BST() { deleteAll(root); }

        /** A method that inserts a Node into the BST. The method climbs down
         *  the tree utill it finds an empty space for the item. If the item
         *  is already in the tree, the function will not add it again.
         *  Parameter: item - The Data to be added into the tree via a Node
         */
        virtual bool insert(const Data& item) { 

            //empty BST base case
            if( root == 0 ) {
           
                root = new BSTNode<Data>( item );
                iheight = 0;
                isize++;

            }

            //create a pointer for the current node at root track the height
            BSTNode<Data>* currNode = root;
            int currHeight = 0;

            //loop down the tree until we reach where there isn't a node
            while( currNode != nullptr ) {

                //check to see if item is less than the current node
                if( item < currNode->data ) {

                    //check to see if we are at the end
                    if( currNode->left == nullptr ) {

                        // create a copy of the node passed into the parameter
                        // set its parent and the size and height of the tree
                        currNode->left = new BSTNode<Data>( item );
                        currNode->left->parent = currNode;
                        isize++; curHeight++;
                        if( iheight < currHeight ) {
                            iheight = currHeight;
                        }
                        return true;

                    }
                    // make the left node the current node
                    currNode = currNode->left;
                    //increment the height since we are going down a level
                    currHeight++;

                }
                //check to see if item is greater than the current node
                else if( currNode->data < item ) {

                    //check to see if we are at the end
                    if( currNode->right == nullptr ) {

                        // create a copy of the node passed into the parameter
                        // set its parent and the size and height of the tree
                        currNode->right = new BSTNode<Data>( item );
                        currNode->right->parent = currNode;
                        isize++; curHeight++;
                        if( iheight < currHeight ) {
                            iheight = currHeight;
                        }
                        return true;

                    }
                    // if there is a right child, make it the current node
                    currNode = currNode->right;
                    //increment the height since we are going down a branch
                    currHeight++;

                }

                // if the node is already in the tree, don't insert it
                else {
                    return false;
                }

            } //end the loop down the tree

            return true;

        }

        /** Finds the item in the BST and returns an iterator pointing to
         *  the BSTNode which contains the item. If the item is not found,
         *  it returns an iterator that points to a nullptr.
         *  Parameter: item - the Data item that is searched in the BST
         */
        virtual iterator find(const Data& item) const { 

            //recurse down the tree trying to find the node
            BSTNode<Data>* currNode = root;
            while( currNode != nullptr ) { 

                //check to see if item is >, <, = current node
                if( item < currNode->data ) {

                    currNode = currNode->left;

                } else if( currNode->data < item ) { 

                    currNode = currNode->right;

                } else {

                    return BSTIterator<Data>(currNode);

                }


            } //end while loop

            //if we haven't found it, return a nullptr iterator
            return BSTIterator<Data>(nullptr);

        }

        /** Returns the size of the tree */
        unsigned int size() const {

            return isize;

        }

        /** Returns the height of the tree */
        int height() const {

            return iheight;

        }

        /** Returns true if the BST is empty, false if not. */
        bool empty() const {

            return root == 0;

        }

        /** Returns an iterator pointing to the smallest element of this BST.
         *  Uses a helper function, first to find the Node. 
         */
        iterator begin() const { return BST::iterator(first(root)); }

        /** Return an iterator pointing past the last item in the BST.
         */
        iterator end() const { return typename BST<Data>::iterator(0); }

        /** TODO */
        vector<Data> inorder() const { 

            //create an empty vector, order it, and return it
            std::vector<Data> ordered;
            orderNodes( ordered, n ); 
            return ordered; 

        }

    private:
        /** Returns a pointer to the smallest/first node in the BST 
         *  Parameter: root - a pointer to the root Node of the BST
         */
        static BSTNode<Data>* first(BSTNode<Data>* root) {

            //set the current node to the root passed in
            BSTNode<Data>* currNode = root;
            //keep recursing left on the tree
            while( currNode->left != nullptr ) {
                currNode = currNode->left;
            }
            //return the leftmost node which is the smallest/first
            return currNode;

        }

        /** Deletes each node in the BST recursively. First it recurses left,
         *  then it recurses right, and then it deletes the current node.
         *  If the node is null then it returns.
         *  Parameter: n - the current node in the recursion. 
         */
        static void deleteAll(BSTNode<Data>* n) {
            if( n == nullptr ) {
                return;
            }

            //delete left nodes, right node, and then delete current node
            deleteAll(n->left);
            deleteAll(n->right);
            delete n;
        }

        static void orderNodes( vector<Data>& arr, BSTNode<Data>* n ) {

            //base case if null return
            if( n == nullptr ) {
                return;
            }
            //recurse left
            orderNodes( arr, n->left );
            //add to end of vector
            arr.push_back( n->data );
            //recurse right
            orderNodes( arr, n->right );

        }
};

#endif  // BST_HPP
