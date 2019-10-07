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

            //create a pointer for the current node at root track the height
            BSTNode<Data>* currNode = root;
            int currHeight = 0; 

            //loop down the tree until we reach where there isn't a node
            while( currnode != nullptr ) {

                //check to see if item is less than the current node
                if( item.data < currNode->data ) {

                    // make the left node the current node
                    currNode = currNode->left;
                    //increment the height since we are going down a level
                    currHeight++;

                }
                //check to see if item is greater than the current node
                else if( currNode->data < item.data ) {

                    // if there is a right child, make it the current node
                    currNode = currNode->right;
                    //increment the height since we are going down a branch
                    currHeight++;

                }

                // if the node is already in the tree, don't insert it
                else {
                    return false;
                }

            }

            // now we are at the position where this new node should be
            // create a copy of the node passed into the parameter
            BSTNode<Data>* copyNode = new BSTNode<Data>( item.data );
            currNode = copyNode;
            //increment size and check to see if the height grew
            isize++;
            if( iheight < currheight ) {

                iheight = currheight;

            }
            return true;

        }

        /** TODO */
        virtual iterator find(const Data& item) const { 

            //recurse down the tree trying to find the node
            BSTNode<Data>* currNode = root;
            while( currNode != nullptr ) { 

                //check to see if item is >, <, = current node
                if( item < currnode ) {

                    currNode = currNode->left;

                } else if( currNode < item ) { 

                    currNode = currNode->right;

                } else {

                    return BSTIterator<Data>(currNode);

                }


            } //end while loop

            //if we haven't found it, return a nullptr iterator
            return BSTIterator<Data>(nullptr);

        }

        /** TODO */
        unsigned int size() const {

            return isize;

        }

        /** TODO */
        int height() const {

            return iheight;

        }

        /** TODO */
        bool empty() const {

            return root == 0;

        }

        /** TODO */
        iterator begin() const { return BST::iterator(first(root)); }

        /** Return an iterator pointing past the last item in the BST.
         */
        iterator end() const { return typename BST<Data>::iterator(0); }

        /** TODO */
        vector<Data> inorder() const {}

    private:
        /** TODO */
        static BSTNode<Data>* first(BSTNode<Data>* root) { return 0; }

        /** TODO */
        static void deleteAll(BSTNode<Data>* n) {
            if( n == nullptr ) {
                return;
            }

            //delete left nodes, right node, and then delete current node
            deleteAll(n->left);
            deleteAll(n->right);
            delete n;
        }
};

#endif  // BST_HPP
