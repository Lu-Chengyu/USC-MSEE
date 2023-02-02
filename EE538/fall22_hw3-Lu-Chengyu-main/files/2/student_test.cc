#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(CheckValidExpression ,test1){
    CPPLib cpplib;
    std::string input1 = "(a+b)";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(CheckValidExpression ,test2){
    CPPLib cpplib;
    std::string input1 = "(a+b)[c*d]{5g+h}";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(CheckValidExpression ,test3){
    CPPLib cpplib;
    std::string input1 = "(a+b]";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = false;
    EXPECT_EQ(output, actual);
}
TEST(CheckValidExpression ,test4){
    CPPLib cpplib;
    std::string input1 = "(7h+[5c)+7]";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = false;
    EXPECT_EQ(output, actual);
}
TEST(CheckValidExpression ,test5){
    CPPLib cpplib;
    std::string input1 = "}";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = false;
    EXPECT_EQ(output, actual);
}
TEST(CheckValidExpression ,test6){
    CPPLib cpplib;
    std::string input1 = "";
    bool actual = cpplib.CheckValidExpression(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(IsPalindrome ,test7){
    CPPLib cpplib;
    std::string input1 = "aba";
    bool actual = cpplib.IsPalindrome(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(IsPalindrome ,test8){
    CPPLib cpplib;
    std::string input1 = "abba";
    bool actual = cpplib.IsPalindrome(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(IsPalindrome ,test9){
    CPPLib cpplib;
    std::string input1 = "(a+b]";
    bool actual = cpplib.IsPalindrome(input1);
    bool output = false;
    EXPECT_EQ(output, actual);
}
TEST(IsPalindrome ,test10){
    CPPLib cpplib;
    std::string input1 = "";
    bool actual = cpplib.IsPalindrome(input1);
    bool output = true;
    EXPECT_EQ(output, actual);
}
TEST(OddChar ,test11){
    CPPLib cpplib;
    std::string input1 = "";
    int actual = cpplib.OddChar(input1);
    int output = 0;
    EXPECT_EQ(output, actual);
}
TEST(OddChar ,test12){
    CPPLib cpplib;
    std::string input1 = "abcddcb";
    int actual = cpplib.OddChar(input1);
    int output = (int)'a';
    EXPECT_EQ(output, actual);
}
TEST(OddChar ,test13){
    CPPLib cpplib;
    std::string input1 = "jiflsjiDfls";
    int actual = cpplib.OddChar(input1);
    int output = (int)'D';
    EXPECT_EQ(output, actual);
}