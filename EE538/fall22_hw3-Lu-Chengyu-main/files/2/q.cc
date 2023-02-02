#include "q.h"

#include <climits>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include  <map>
#include <stack>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
bool CPPLib::CheckValidExpression(const std::string& input){
    std::map<char,char> my_map ={{')','('},{']','['},{'}','{'}};
    std::stack <char> brackets;
    for(int i=0;i<input.size();++i){
        if(input[i]=='('||input[i]=='['||input[i]=='{'){
            brackets.push(input[i]);
        }
        else if((input[i]==')'||input[i]==']'||input[i]=='}')&&brackets.empty()){
            return false;
        } 
        else if((input[i]==')'||input[i]==']'||input[i]=='}')&&brackets.top()!=my_map[input[i]]){
            return false;
        }
        else if((input[i]==')'||input[i]==']'||input[i]=='}')&&brackets.top()==my_map[input[i]]){
            brackets.pop();
        }
    }
    if(brackets.empty()) return true;
    else return false;
}

bool CPPLib::IsPalindrome(const std::string& input){
    if(input.size()==0) return true;
    const char * front, * back;
    front = &input[0];
    back = &input[input.size()-1];
    while(front<back){
        if(*front!=*back) return false;
        front+=1;
        back-=1;
    }
    return true;
}

int CPPLib::OddChar(const std::string& input){
    int result = 0;
    for(int i =0;i<input.size();++i){
        result^=input[i];
    }
    return result;
}