#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(Flatten3DVector ,test1){
   std::vector<std::vector<std::vector<int>>> input = {{{1,2},{3,4}},{{5},{6},{}},{{7,8}}};
    std::vector<int> actual1 = Flatten3DVector(input);
    std::vector<int> output = {1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(output, actual1);
}
