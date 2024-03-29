/** Rosa Miranda
 *  KNNHelper pseudocode from CSE Discussion Week 2
 *  KDT file provides the structure for building a kdt,
 *  a function for finding the nearest neighbor of a query point
 *  their helper functions and variables.
 * */
#ifndef KDT_HPP
#define KDT_HPP
#define MAGIC_NUMBER 2
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

    /** TODO */
    //build method to create the bst with a given vector
    void build(vector<Point>& points) {
        if (points.empty()) {
            return;
        }
        isize = points.size();
        numDim = points[0].numDim;
        root = buildSubtree(points, 0, isize, 0, iheight);
    }
    int getnumDim() { return numDim; }
    KDNode* getRoot() { return root; }
    /** TODO */
    //function to find point on kdt with least distance to query point
    Point* findNearestNeighbor(Point& queryPoint) {
        if (isize == 0) {
            return nullptr;
        }

        threshold = numeric_limits<double>::max();
        findNNHelper(root, queryPoint, 0);
        return &nearestNeighbor;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** TODO */
    //returns size
    unsigned int size() const { return isize; }

    /** TODO */
    //returns height
    int height() const { return iheight; }

  private:
    /** TODO */
    //build function recursive helper method
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start == end) {
            return nullptr;
        }
        CompareValueAt compare(curDim);
        sort(points.begin() + start, points.begin() + end - 1, compare);
        int median = floor((start + end) / MAGIC_NUMBER);
        KDNode* node = new KDNode(points[median]);
        height++;
        if (height > iheight) {
            iheight = height;
        }
        node->left = buildSubtree(points, start, median,
                                  ((curDim + 1) % numDim), height);
        node->right = buildSubtree(points, median + 1, end,
                                   ((curDim + 1) % numDim), height);
        return node;
    }

    /** TODO */
    //nearest neighbor recursive helper function
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        if (!node) {
            return;
        }
        // Initiates recursion
        if (queryPoint.valueAt(curDim) >= node->point.valueAt(curDim)) {
            findNNHelper(node->right, queryPoint, ((curDim + 1) % numDim));
            // Decides whether to check left subtree
            if (node->left) {
                node->left->point.setDistToQuery(queryPoint);
                if (node->left->point.distToQuery < threshold) {
                    findNNHelper(node->left, queryPoint,
                                 ((curDim + 1) % numDim));
                }
            }

        } else {
            findNNHelper(node->left, queryPoint, ((curDim + 1) % numDim));
            // decides whether to check right subtree
            if (node->right) {
                node->right->point.setDistToQuery(queryPoint);
                if (node->right->point.distToQuery < threshold) {
                    findNNHelper(node->right, queryPoint,
                                 ((curDim + 1) % numDim));
                }
            }
        }
	//sets current point as threshold
        node->point.setDistToQuery(queryPoint);
        if (node->point.distToQuery < threshold) {
            nearestNeighbor = node->point;
            threshold = node->point.distToQuery;
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    // Recursively deletes nodes in KDT
    static void deleteAll(KDNode* n) {
        if (!n) {
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }
    // Add your own helper methods here
};
#endif  // KDT_HPP
