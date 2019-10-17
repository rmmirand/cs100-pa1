#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33, 2, 56};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 7);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}
TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST2) {
    // assert failed duplicate insertion
    ASSERT_TRUE(bst.insert(57));
}
TEST_F(SmallBSTFixture, INORDER_TEST) {
    // test inorder function
    vector<int> input{-33, 1, 2, 3, 4, 56, 100};
    ASSERT_EQ(bst.inorder(), input);
}
TEST_F(SmallBSTFixture, FIND_TESTTWO) {
    ASSERT_EQ(bst.find(100).getNode()->data, 100);
}
TEST_F(SmallBSTFixture, FIND_TEST) {
    ASSERT_EQ(bst.find(1).getNode()->data, 1);
}
TEST_F(SmallBSTFixture, FIND_SUCCESSOR) {
    ASSERT_EQ(bst.find(4).getNode()->successor()->data, 56);
}

// TODO: add more BST tests here
