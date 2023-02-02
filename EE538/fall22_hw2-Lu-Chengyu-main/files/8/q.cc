#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include<algorithm>
#include<set>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
void UniqueVectorNotBySet(std::vector<int> &input){
    std::vector<int> temp;
    for(int i=0; i<input.size();i++){
        if(count(temp.begin(),temp.end(), input[i])==0){
            temp.push_back(input[i]);
        }
    }
    input = temp;
}

void UniqueVectorBySet(std::vector<int> &input){
    std::set <int> temp;
    for(int i=0; i<input.size();i++){
        temp.insert(input[i]);
    }
    std::vector<int> temp1;
    for(auto j=temp.begin(); j!= temp.end(); ++j){
        temp1.push_back(*j);
    }
    input = temp1;
}

std::vector<int> IntersectVectors(std::vector<int> &input1,std::vector<int> &input2){
    std::vector <int> temp, temp1, temp2;
    temp1 = input1;
    temp2 = input2;
    UniqueVectorNotBySet(temp1);
    UniqueVectorNotBySet(temp2);
    for(int i=0; i<temp1.size(); ++i){
        for(int j=0; j<temp2.size();++j){
            if(temp1[i]==temp2[j]){
                temp.push_back(temp1[i]);
            }
        }
    }
    return temp;
}

