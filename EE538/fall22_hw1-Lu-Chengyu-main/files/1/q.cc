#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
std::vector<int> Reverse(std::vector<int> input){
    for(unsigned int i = 0; i <(input.size()/2); i++){
        int j = input[i];
        input[i] = input[ input.size()-1-i];
        input[input.size()-1-i] = j;
    }
    return input;
}

std::vector<int> PlusOne(std::vector<int> input){
    if(input.empty()){
        return {};
    }
    for(unsigned int i = 0; i<input.size(); i++){
        if(input[ input.size()-1-i]<0 || input[ input.size()-1-i]>9){
            return {-1};
        }
    }
    for(unsigned int i = 0; i<input.size(); i++){
        if(input[ input.size()-1-i] == 9){
            input[ input.size()-1-i] = 0;
        }
        else{
            input[ input.size()-1-i] += 1;
            return input;
        }
        if(i == (input.size()-1)){
            input.push_back(0);
            input[0]=1;
            return input;
        }
    }
}
