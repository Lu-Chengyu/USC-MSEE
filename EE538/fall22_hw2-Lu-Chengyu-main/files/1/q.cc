#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_set>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
int CountCharacters(std::string& input, std::vector<char> characters){
    int number = 0;
    std::unordered_set<char> characterSet;
    for(int i = 0; i<characters.size(); i++){
        characterSet.insert(characters[i]);
    }
    
    for(int j=0; j<input.size(); j++){
        if(input[j]<='z'&& input[j]>='a'){
            number += characterSet.count(input[j]);
            number += characterSet.count((char)(input[j]-32));
        }
        else if(input[j]<='Z'&& input[j]>='A'){
            number += characterSet.count(input[j]);
            number += characterSet.count((char)(input[j]+32));
        }
        else{
            number += characterSet.count(input[j]);
        }
    }
    return number;
}
