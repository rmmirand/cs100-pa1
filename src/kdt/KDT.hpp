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

    /** TODO */
    void build(vector<Point>& points) {
	if(points.empty()){
		return;
	}
	int veclength = points.size();
	int mid = veclength/2;
	numDim = points[0].features.size();
	CompareValueAt compare(0);
	sort(points.begin(), points.end(), compare);
	root = new KDNode(points[mid]);
	iheight++;
	isize = veclength;
	root->left = buildSubtree(points,0, mid, numDim+1, iheight);
	root->right = buildSubtree(points,mid+1, veclength,numDim+1, iheight);
    }
    KDNode* getRoot() {
	return root;
    }
    int getnumDim() {
	    return numDim;
    }
    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) { return nullptr; }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }
    
  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
	    if(start <= end){
		    return nullptr;
	    }	    
	    int median = (end-start)/ 2;
	    int nextDim = (curDim+1) % numDim;
	    CompareValueAt compare(curDim);
	    sort(points.begin()+start, points.begin()+end-1,compare);
	    KDNode* node = new KDNode(points[median+start]);
	    iheight++;
	    node->left = buildSubtree(points,start, median,nextDim, iheight);
	    node->right = buildSubtree(points, median+1, end, nextDim, iheight);
        return node;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {}

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
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
