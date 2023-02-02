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
int IndexOfFirstSpace(std::string& input){
    for(int i=0; i< input.size(); i++){
        if(input[i]==' '){
            return i;
        }
    }
    return -1;
}

void SeparateFirstAndLastNames(std::string& full_name, std::string& first_name,std::string& last_name){
    int space = IndexOfFirstSpace(full_name);
    if(space==-1){
        first_name = full_name;
    }
    else{
        std::string firstname(full_name.begin(),full_name.begin()+space);
        first_name = firstname;
        std::string lastname(full_name.begin()+space+1,full_name.end());
        last_name = lastname;
    }
}

int NumberOfVowels(std::string& input){
    int number = 0;
    std::unordered_set<char> characterSet;
    characterSet.insert('a');
    characterSet.insert('e');
    characterSet.insert('i');
    characterSet.insert('o');
    characterSet.insert('u');
    for(int j=0; j<input.size(); j++){
        if(input[j]<='z'&& input[j]>='a'){
            number += characterSet.count(input[j]);
        }
        else if(input[j]<='Z'&& input[j]>='A'){
            number += characterSet.count((char)(input[j]+32));
        }
    }
    return number;
}

int NumberOfConsonants(std::string& input){
    int number = 0;
    for(int i=0; i<input.size();i++){
        if(input[i]<='z'&& input[i]>='a'||input[i]<='Z'&& input[i]>='A'){
            number++;
        }
    }
    return (number - NumberOfVowels(input));
}

int Reverse(std::string& input){
    char temp;
    for(int i=0;i<(input.size()/2);i++){
        temp = input[i];
        input[i] = input[input.size()-i-1];
        input[input.size()-i-1] = temp;
    }
    return 0;
}