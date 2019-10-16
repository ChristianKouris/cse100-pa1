#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

TEST(PointTests, TEST_NOT_EQUALS) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);

    vector<double> p2Values{3, 4, 5};
    Point p2(p2Values);

    ASSERT_NE(p1, p2);
}

TEST(PointTests, TEST_DISTANCE) {
    vector<double> p1Values{3, 4, 5, 6};
    vector<double> p2Values{3, 4, 5, 7};

    Point p1(p1Values);
    Point p2(p2Values);

    p1.setDistToQuery(p2);
    ASSERT_DOUBLE_EQ(p1.distToQuery, 1.0);
}

TEST(PointTests, TEST_EQUALS) {

    vector<double> p1Values{1, 10};
    vector<double> p2Values{1, 10};
    
    Point p1(p1Values);
    Point p2(p2Values);

    ASSERT_EQ(p1, p2);

}

TEST(PointTests, TEST_VALUE_AT) {

    vector<double> pointValues{5, 200, 18, 54};
    Point point(pointValues);
    
    ASSERT_EQ(point.valueAt(0), 5);
    ASSERT_EQ(point.valueAt(3), 54);

}

TEST(PointTests, TEST_NUM_DIM) {

    vector<double> pointValues{5, 2, 181, 74, 1, 99, 527};
    Point point(pointValues);
    
    ASSERT_EQ(point.numDim, 7);

}

TEST(PointTests, TEST_COMPARATOR) {

    vector<double> p1Val{1, 2};
    vector<double> p2Val{2, 1};
    Point p1(p1Val);
    Point p2(p2Val);

    vector<Point> points{p1, p2};
    std::sort(points.begin(), points.end(), CompareValueAt(1));

    ASSERT_EQ( points[0].features[0], 2 );

}
