#include <iostream>
#include <string>

// all functions must set the error_ to an appropriate value.
class CPPLib {
 public:
  //  Given an expression string, find if the input has valid brackets (i.e. { }
  //  or [ ] or ( ) ).
  // An input expression is valid if:
  // Open brackets are closed by the same type of brackets. Open brackets must
  // be closed in the correct order. An empty string is also considered valid.
  // You should only check for the validity of brackets based on the above
  // rules, i.e. ‘(‘, ‘)’, ‘[‘, ‘]’, ‘{‘, ‘}’, not the rest of the expression.
  // Example 1: Input: "(a+b)" Output: true
  // Example 2: Input: "(a+b)[c*d]{5g+h}" Output: true
  // Example 3: Input: "(a+b]" Output: false
  // Example 4: Input: "(7h+[5c)+7]" Output: false
  // Example 5: Input: "{2k+[5j]}" Output: true
  // Example 6: Input: "{2k++[5--*j]}" Output: true
  bool CheckValidExpression(const std::string& input);

  // Checks if a string is a palindrome.
  // An empty string is a palindrome.
  // A non empty string is a palindrome if it is equal to its reverse string.

  // Example 1: Input: "aba", output: true
  // Example 2: Input: "abba", output: true

  // You cannot use any std:: function.
  // Your memory usage should be O(1).
  bool IsPalindrome(const std::string& input);

  // Given a string, every letter appears even number of times except for one.
  // Find that letter!

  // Any solution that work is acceptable, but see if you can implement it while
  // keeping your memory usage as O(1).
  int OddChar(const std::string& input);
};
