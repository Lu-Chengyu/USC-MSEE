#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the following functions in q.cc.
// 2. Write some unit tests for them in student_test.cc

//-----------------------------------------------------------------------------
// Given a vector, return its reversed version.
// Examples:
// Input: [1,2,3]  =>	Output: [3, 2, 1].
// Note: you should not use any function from std::.
// You should not use any container from std:: except for vectors.
std::vector<int> Reverse(std::vector<int> input);

//-----------------------------------------------------------------------------
// Given a positive integer represented by an array of digits, add one to that
// number.
// If the input was invalid, (i.e. digits are not between 0 to 9), return {-1};
// Examples:
// Input: [1,2,3]  =>	Output: [1,2,4].
// Explanation: [1,2,3] represents number 123. Then 123 + 1 = 123 which is
// represented by [1, 2, 4].
//
// Input: [1, 9]	=> Output: [2,0]
//
// Input: [9,9,9]  =>  Output: [1,0,0,0]
//
// Input: [12]  =>  Output: [-1]   // Invalid input!
std::vector<int> PlusOne(std::vector<int> input);
