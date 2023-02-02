#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
std::vector<int> Flatten3DVector(
    std::vector<std::vector<std::vector<int>>> input){
        std::vector<int> output;
        for(unsigned int i = 0; i<input.size(); i++){
            for(unsigned int j = 0; j< input[i].size(); j++ ){
                for(unsigned int k = 0; k< input[i][j].size(); k++){
                    output.push_back(input[i][j][k]);
                }
            }
        }
        return output;
    }