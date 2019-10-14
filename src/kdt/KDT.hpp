#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    /** builds a balanced KDT tree from a set of points.  */
    void build(vector<Point>& points) {

        //check to see if vector is empty and return
        if( points.size() == 0 ) {
            return;
        }
        //set member variables for the root Node
        isize = 1; iheight = 0; 
        //define new variables to help organize logic
        unsigned int curDim = 0;
        unsigned int start = 0; unsigned int end = points.size();
        unsigned int median = (start+end)/2;

        //sort the points vector
        std::sort(points.begin(), points.end(), CompareValueAt(curDim));
        //set the median of the sorted list as the rood of the KDT
        root = new KDNode( points[median] );
        
        //call the helper method for the root's children
        root->left = buildSubtree( points, start, median, curDim + 1, 1 );
        root->right = buildSubtree( points, median + 1, end, curDim + 1, 1 );

    }

    /** Return the point in the KDT that is the closest to the queryPoint.
     *  Has a best case time of iheight and a worst case time of isize.
     *  Parameter: queryPoint - The point that we want the nearest neighbor
     */
    Point* findNearestNeighbor(Point& queryPoint) {

        //check to see if the tree is empty
        if( root == 0 ) { return nullptr; }

        //set root as the nearest neighbor and set it's distance
        nearestNeighbor = root->point;
        nearestNeighbor.setDistToQuery( queryPoint );
        unsigned int curDim = 0;

        //check to see if the query point dim is > or <= to root's point
        if( queryPoint.features[curDim] < root->point.features[curDim] ) {

            //recurse down the right since it's closer to point's dim
            findNNHelper( root->right, queryPoint, curDim+1 );
            
            //calculate x-x0 for whatever dim 0
            double dimDist = pow( root->point.features[curDim] - 
                                  queryPoint.features[curDim], 2.0 );
            //if distance in one dim is closer than nearest neighbor, recurse
            if( dimDist < nearestNeighbor.distToQuery ) {
                findNNHelper( root->left, queryPoint, curDim+1 );
            }

        } else {

            //recurse down the left since it's closer to root point's dim
            findNNHelper( root->left, queryPoint, curDim+1 );
            
            //calculate x-x0 for whatever dimension we're at
            double dimDist = pow( root->point.features[curDim] - 
                                  queryPoint.features[curDim], 2.0 );
            //if dim 0 distance is shorter than closest neighbor, recurse
            if( dimDist < nearestNeighbor.distToQuery ) {
                findNNHelper( root->right, queryPoint, curDim+1 );
            }
        
        }

        return &nearestNeighbor;

    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        //remove the compiler warnings 
        queryRegion.empty();
        return vector<Point>(0);
    }

    /** Returns the size of the KDT */
    unsigned int size() const { return isize; }

    /** Returns the height of the KDT */
    int height() const { return iheight; }

  private:
    /** Recursive function to build the balanced KD Tree level by level.
     *  Each level takes a section of the vector, sorts it, finds a new
     *  median root, and repeats with the subvectors
     *  Parameter: points - a vector of points to serve as the KDT data
     *  Parameter: start - the inclusive start index of the subvector
     *  Parameter: end - the exclusive end index of the subvector
     *  Parameter: curDim - The current dimension of the recursion level
     *  Parameter: height - the current height of the level
     */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if( start == end) {
            return nullptr;
        }
        //sort this part of the list
        std::sort(points.begin() + start, points.begin() + end, 
                  CompareValueAt(curDim % points[0].numDim) );

        //allocate memory for the median Node
        unsigned int median = (start+end)/2;
        KDNode * medNode = new KDNode( points[median] );

        //recurse left and right
        medNode->left = buildSubtree( points, start, median, 
                                      curDim + 1, height + 1 );
        medNode->right = buildSubtree( points, median + 1, end,
                                       curDim + 1, height + 1 );
        
        //increment size and check to see if height is taller than current
        isize++;
        if( iheight < height ) {
            iheight = height;
        }
        //return the Node
        return medNode;
        
    }

    /** A helper method to help find the nearest neighbor and to 
     *  reduce the branches we search. At each level, this method
     *  determines which side of the node the querypoint falls under.
     *  Parameter: node - the current node inn our traversal
     *  Parameter: queryPoint - the point we want to find the neighbor of
     *  Parameter: curDim - the current dimension of the point in traversal
     */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {

        //if we are at the end, return
        if( node == nullptr ) { return; }

        //check to see if this current node's point is the closest to query
        node->point.setDistToQuery( queryPoint );
        if( nearestNeighbor.distToQuery < node->point.distToQuery ) {
            nearestNeighbor = node->point;
        }

        //check to see if the query point dim is > or <= to node's point
        if( queryPoint.features[curDim] < node->point.features[curDim] ) {

            //recurse down the right since it's closer to point's dim
            findNNHelper( node->right, queryPoint, curDim+1 );
            
            //calculate x-x0 for whatever dimension we're at
            double dimDist = pow( node->point.features[curDim] - 
                                  queryPoint.features[curDim], 2.0 );
            //if distance in one dim is closer than nearest neighbor, recurse
            if( dimDist < nearestNeighbor.distToQuery ) {
                findNNHelper( node->left, queryPoint, curDim+1 );
            }

        } else {

            //recurse down the left since it's closer to point's dim
            findNNHelper( node->left, queryPoint, curDim+1 );
            
            //calculate x-x0 for whatever dimension we're at
            double dimDist = pow( node->point.features[curDim] - 
                                  queryPoint.features[curDim], 2.0 );
            //if distance in one dim is closer than nearest neighbor, recurse
            if( dimDist < nearestNeighbor.distToQuery ) {
                findNNHelper( node->right, queryPoint, curDim+1 );
            }
        
        }

    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {
    // remove the compiler warnings
    node->point.features[0]++;
    curBB.empty();
    queryRegion.empty();
    curDim++;

    }

    /** Deletes all of the KDT nodes from the heap.
     *  Parameter: n - the pointer to the current node in the recursion.
     */
    static void deleteAll(KDNode* n) {

        if( n == nullptr ) {
            return;
        }
        deleteAll( n->left );
        deleteAll( n->right );
        delete n;

    }

    // Add your own helper methods here
};
#endif  // KDT_HPP
