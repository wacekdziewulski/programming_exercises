#include <gtest/gtest.h>
#include "QuickFind.hpp"

//
//  0   1---2   3---4
//  |   |   |   |   |
//  5---6   7   8   9
//
TEST(QuickFindTest, basicQuickFindTest) {
    QuickFind qf(10);
    // horizontal
    qf.Union(1, 2);
    qf.Union(3, 4);
    qf.Union(5, 6);
    // vertical
    qf.Union(0, 5);
    qf.Union(1, 6);
    qf.Union(2, 7);
    qf.Union(3, 8);
    qf.Union(4, 9);

    // basic connections
    EXPECT_TRUE(qf.Connected(1, 2));
    EXPECT_TRUE(qf.Connected(3, 8));

    // transient connections
    EXPECT_TRUE(qf.Connected(0, 7));
    EXPECT_TRUE(qf.Connected(5, 2));
    EXPECT_TRUE(qf.Connected(5, 1));
    EXPECT_TRUE(qf.Connected(8, 9));
    EXPECT_TRUE(qf.Connected(1, 7));

    // not connected nodes
    EXPECT_FALSE(qf.Connected(7, 8));
    EXPECT_FALSE(qf.Connected(0, 9));
    EXPECT_FALSE(qf.Connected(7, 4));
    EXPECT_FALSE(qf.Connected(6, 3));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
