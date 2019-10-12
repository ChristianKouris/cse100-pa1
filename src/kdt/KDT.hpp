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
        isize = 1; iheight = 0; curDim = 0; 
        //define new variables to help organize logic
        unsigned int start = 0; unsigned int end = points.size();
        unsigned int median = (start+end)/2;

        //sort the points vector
        std::sort(points.begin(), points.end(), CompareValueAt(curDim));
        //set the median of the sorted list as the rood of the KDT
        root = new KDNode( points[median] );
        
        //call the helper method for the root's children
        root->left = buildSubtree( points, start, median, curDim + 1, 1 )
        root->right = buildSubtree( points, median + 1, end, curDim + 1, 1 )

    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) { return nullptr; }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
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
                  CompareValueAt(curDim % points.begin().curDim) );

        //allocate memory for the median Node
        unsigned int median = (start+end)/2;
        KDTNode * medNode = new KDTNode( points[median] );

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

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {}

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

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
