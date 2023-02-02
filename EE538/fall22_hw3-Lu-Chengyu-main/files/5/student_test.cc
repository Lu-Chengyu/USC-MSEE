#include <iostream>
#include <string>
#include <climits>
#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(BinaryTree ,test1){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(0,tree.GetParentIndex(1));
}
TEST(BinaryTree ,test2){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(-1,tree.GetParentIndex(0));
}
TEST(BinaryTree ,test3){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(49,tree.GetParentIndex(100));
}
TEST(BinaryTree ,test4){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(1,tree.GetLeftIndex(0));
}
TEST(BinaryTree ,test5){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(201,tree.GetLeftIndex(100));
}
TEST(BinaryTree ,test6){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(2,tree.GetRightIndex(0));
}
TEST(BinaryTree ,test7){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(202,tree.GetRightIndex(100));
}
TEST(BinaryTree ,test8){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(INT_MAX,tree.FindMin(100));
}
TEST(BinaryTree ,test9){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(1,tree.FindMin(0));
}
TEST(BinaryTree ,test10){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(INT_MIN,tree.FindMax(100));
}
TEST(BinaryTree ,test11){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(8,tree.FindMax(0));
}
TEST(BinaryTree ,test12){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(false,tree.IsLeaf(100));
}
TEST(BinaryTree ,test13){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(true,tree.IsLeaf(7));
}
TEST(BinaryTree ,test14){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    class BinaryTree tree(v);
    EXPECT_EQ(false,tree.IsLeaf(0));
}