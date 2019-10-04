#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);

    iter++;

    ASSERT_EQ(iter, nullptr);
}

TEST(BST_IERATOR_TEST, TEST_ITERATOR_EQUALS) {

    BSTNode<int> node(100);
    BSTIterator<int> iter1(&node);
    BSTIterator<int> iter2(&node);

    ASSERT_EQ(iter1 == iter2, true);
    ASSERT_EQ(iter1 != iter2, false);

}

TEST(BST_IERATOR_TEST, TEST_ITERATOR_NOT_EQUALS) {

    BSTNode<int> node(100);
    BSTNode<int> node2(100);
    BSTIterator<int> iter1(&node);
    BSTIterator<int> iter2(&node2);

    ASSERT_EQ(iter1 == iter2, false);
    ASSERT_EQ(iter1 != iter2, true);

}
