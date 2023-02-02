#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include<array>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
int* Concatenate(int* array_1, int size_1, int* array_2, int size_2){
    if(array_1!= nullptr || array_2!=nullptr){
        int* arr = new int[size_1+size_2]; //需要用new来申请一块堆存储，否则会造成内存泄露，是否需要delete？什么时候delete?
        //static int arr[size_1+size_2]; 不可以，因为这里不能使用变量，需要使用常量
        for(int i= 0;i<size_1;++i){
            arr[i]=array_1[i];
        }
        for(int i= 0;i<size_2;++i){
            arr[i+size_1]=array_2[i];
        }
        return arr; // 因为这里返回的是指针，而不是值, 只有指针值被复制了，指针指向的地址值没有被复制
        //delete arr;
    }
    return nullptr;
}

std::vector<int> Concatenate(std::vector<int>& vector_1,std::vector<int>& vector_2){
    std::vector<int> vec;
    vec.insert(vec.end(),vector_1.begin(),vector_1.end());
	vec.insert(vec.end(),vector_2.begin(),vector_2.end());
    return vec;
}