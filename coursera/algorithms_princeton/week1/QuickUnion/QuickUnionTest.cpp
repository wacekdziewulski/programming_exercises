#include <gtest/gtest.h>
#include "QuickUnion.hpp"

//
// 9  0-
// |  | \
// 8  6  7
// |  |  |
// 4  5  2
// |     |
// 3     1
//
TEST(QuickUnionTest, basicQuickUnionTest) {
    QuickUnion qu(10);
    // horizontal
    qu.Union(1, 2);
    qu.Union(3, 4);
    qu.Union(5, 6);
    // vertical
    qu.Union(0, 5);
    qu.Union(1, 6);
    qu.Union(2, 7);
    qu.Union(3, 8);
    qu.Union(4, 9);

    // basic connections
    EXPECT_TRUE(qu.Connected(1, 2));
    EXPECT_TRUE(qu.Connected(3, 8));

    // transient connections
    EXPECT_TRUE(qu.Connected(0, 7));
    EXPECT_TRUE(qu.Connected(5, 2));
    EXPECT_TRUE(qu.Connected(5, 1));
    EXPECT_TRUE(qu.Connected(8, 9));
    EXPECT_TRUE(qu.Connected(1, 7));

    // not connected nodes
    EXPECT_FALSE(qu.Connected(7, 8));
    EXPECT_FALSE(qu.Connected(0, 9));
    EXPECT_FALSE(qu.Connected(7, 4));
    EXPECT_FALSE(qu.Connected(6, 3));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
