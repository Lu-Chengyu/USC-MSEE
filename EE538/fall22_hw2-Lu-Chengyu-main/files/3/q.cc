#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
float Calculate(int a, int b, Operation operation){
    if(operation == Operation::kAdd){
        return((float)(a+b));
    }
    else if(operation == Operation::kSubtract){
        return((float)(a-b));
    }
    else if(operation == Operation::kDivision){
        return(((float)a)/((float)b));
    }
    else if(operation == Operation::kMultiplication){
        return((float)(a*b));
    }
    else if(operation == Operation::kBitwise_AND){
        return((float)(a&b));
    }
    else if(operation == Operation::kBitwise_OR){
        return((float)(a|b));
    }
    else if(operation == Operation::kBitwise_XOR){
        return((float)(a^b));
    }
    else if(operation == Operation::kShift_right){
        return((float)(a>>b));
    }
    else if(operation == Operation::kShift_left){
        return((float)(a<<b));
    }
}

