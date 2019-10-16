#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;

  public:
    SmallKDTFixture() {
        vec.emplace_back(Point({1.0, 3.2}));
        vec.emplace_back(Point({3.2, 1.0}));
        vec.emplace_back(Point({5.7, 3.2}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
	vec.emplace_back(Point({1.5, 3.6}));
	vec.emplace_back(Point({6.8, 1.2}));
        kdt.build(vec);
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 7);
}
TEST_F(SmallKDTFixture, TEST_HEIGHT) {
	ASSERT_EQ(kdt.height(), 2);
}
TEST_F(SmallKDTFixture, TEST_DIM) {
	ASSERT_EQ(kdt.getnumDim(), 2);
}
TEST_F(SmallKDTFixture, TEST_ROOT) {
	ASSERT_EQ(kdt.getRoot()->point.features[0], 3.2);
}
TEST_F(SmallKDTFixture, TEST_LEFTROOT){
	ASSERT_EQ(kdt.getRoot()->left->point.features[0],1.0);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({2.0,1.2});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}
