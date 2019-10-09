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

TEST(BSTTests, EMPTY_TREE_SIZE_TEST) {

    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);

}

TEST(BSTTests, EMPTY_TREE_IS_EMPTY_TEST) {

    BST<int> bst;
    ASSERT_TRUE(bst.empty());

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
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}


TEST_F(SmallBSTFixture, SMALL_INSERT_TEST) {
    // assert nonduplicate insert is true
    ASSERT_TRUE(bst.insert(2));
    // assert size has changed with nonduplicate insert
    ASSERT_EQ(bst.size(), 6);
}

TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    // assert height is 2
    ASSERT_EQ(bst.height(), 2);
    bst.insert( 101010 );
    // assert height has changed to 3 by inserting new level
    ASSERT_EQ(bst.height(), 3);
}

TEST_F(SmallBSTFixture, SMALL_BEGIN_TEST) {
    // assert that the beginning data is -33
    ASSERT_EQ(*(bst.begin()), -33);
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST) {
    // assert find 100 returns 100
    ASSERT_EQ(*(bst.find(100)), 100);
}

TEST_F(SmallBSTFixture, SMALL_IN_ORDER_TEST) {
    vector<int> order = bst.inorder();
    ASSERT_EQ( order[0], -33 );
    ASSERT_EQ( order[1], 1 );
    ASSERT_EQ( order[2], 3 );
    ASSERT_EQ( order[3], 4 );
    ASSERT_EQ( order[4], 100 );
}
// TODO: add more BST tests here
