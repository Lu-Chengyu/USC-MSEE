#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
int ClimbStairs(int n){
    if(n < 0){
        return -1;
    }
    else if(n==0){
        return 0;
    }
    else if(n==1){
        return 1;
    }
    else if(n==2){
        return 2;
    }
    else if(n==3){
        return 4;
    }

    int a = 1;
    int b = 2;
    int c = 4;
    int temp = 0;
    for(int i =4; i <= n; i++){
        temp = a+b+c;
        a = b;
        b = c;
        c = temp;
    }
    return temp;
}