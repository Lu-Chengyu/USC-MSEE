#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the following functions in q.cc.
// 2. Write some unit tests for them in student_test.cc
//-----------------------------------------------------------------------------
// Write a function to flatten a 3D vector into a 1D vector.
// Example:
// Input:
// [
//   [[1, 2], [3, 4]],
//   [[5], [6], []],
//   [[7, 8]]
// ]
// Output: [1, 2, 3, 4, 5, 6, 7, 8].
std::vector<int> Flatten3DVector(
    std::vector<std::vector<std::vector<int>>> input);
