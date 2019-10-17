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
    vector<Point> vecv;
    KDT kdt;
    KDT kdtkdt;

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
        vecv.emplace_back(Point({1.0, 1.5, 6.87}));
        vecv.emplace_back(Point({2.0, 30.5, 2.9}));
        vecv.emplace_back(Point({3.0, 20.5, 1.0}));
        vecv.emplace_back(Point({4.0, 15.5, 2.5}));
        vecv.emplace_back(Point({5.0, 13.5, 0.5}));
        vecv.emplace_back(Point({6.0, 1.5, 5.3}));
        vecv.emplace_back(Point({7.0, 1.5, 2.1}));
        vecv.emplace_back(Point({8.0, 7.5, 1.0}));
        vecv.emplace_back(Point({10.0, 6.5, 15.43}));
        vecv.emplace_back(Point({11.0, 23.5, 14.1}));
        vecv.emplace_back(Point({12.0, 4.32, 19.3}));
        vecv.emplace_back(Point({13.0, 27.43, 10.4}));
        vecv.emplace_back(Point({14.0, 3.12, 4.2}));
        vecv.emplace_back(Point({15.0, 0.23, 9.12}));
        vecv.emplace_back(Point({16.0, 10.43, 6.6}));
        vecv.emplace_back(Point({17.0, 9.32, 12.3}));
        vecv.emplace_back(Point({18.0, 13.32, 5.3}));
        kdtkdt.build(vecv);
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 7);
}
TEST_F(SmallKDTFixture, TEST_HEIGHT) { ASSERT_EQ(kdt.height(), 2); }
TEST_F(SmallKDTFixture, TEST_DIM) { ASSERT_EQ(kdt.getnumDim(), 2); }
TEST_F(SmallKDTFixture, TEST_ROOT) {
    ASSERT_EQ(kdt.getRoot()->point.features[0], 3.2);
}
TEST_F(SmallKDTFixture, TEST_LEFTROOT) {
    ASSERT_EQ(kdt.getRoot()->left->point.features[0], 1.5);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT2) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({1.8, 3.5});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}
TEST_F(SmallKDTFixture, TEST_3DVEC) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vecv);
    Point queryPoint({4.0, 5.0, 6.0});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdtkdt.findNearestNeighbor(queryPoint), *closestPoint);
}
TEST_F(SmallKDTFixture, TEST_COMPARE) {
    CompareValueAt compare(0);
    Point firstPoint({1.0, 3.2});
    sort(vec.begin(), vec.end(), compare);
    ASSERT_EQ(vec[0], firstPoint);
}
