#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_CONSTRUCTER) {

    BSTNode<int> node(10);
    ASSERT_EQ(node.parent,  nullptr);
    ASSERT_EQ(node.left, nullptr);
    ASSERT_EQ(node.right, nullptr);

}

TEST(BST_NODE_TESTS, TEST_NO_SUCCESSOR) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node1(3);
    BSTNode<int> node2(4);
    BSTNode<int> node3(5);
    node1.right = &node2;
    node2.left = &node3;
    ASSERT_EQ(node1.successor(), &node3);
}
