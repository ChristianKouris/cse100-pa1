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
    node1.right = &node2; node2.parent = &node1;
    node2.left = &node3; node3.parent = &node2;
    ASSERT_EQ(node1.successor(), &node3);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_IS_PARENT) { 
    BSTNode<int> node1(1);
    BSTNode<int> node2(2);
    BSTNode<int> node3(3);
    BSTNode<int> node4(4);
    BSTNode<int> node5(5);
    BSTNode<int> node6(6);
    node2.left = &node1; node1.parent = &node2;
    node2.right = &node6; node6.parent = &node2;
    node6.left = &node3; node3.parent = &node6;
    node3.right = &node4; node4.parent = &node3;
    node4.right = &node5; node5.parent = &node4;
    ASSERT_EQ(node5.successor(), &node6);
    
}
