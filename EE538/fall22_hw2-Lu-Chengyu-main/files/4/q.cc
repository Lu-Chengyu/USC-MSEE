#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
MyVector::MyVector(){
    data_ = nullptr;
    size_ = 0;
    error_=ErrorCode::kNoError;
}

MyVector::MyVector(int size){
    data_ = new int [size];
    size_ = size;
    error_=ErrorCode::kNoError;
}

MyVector::MyVector(const MyVector& rhs){
    data_ = new int [rhs.size_];
    size_ = rhs.size_;
    for(int i =0; i<rhs.size_; ++i){
        data_[i] = rhs.data_[i];
    }
    error_=ErrorCode::kNoError;
}

MyVector::~MyVector(){
    delete [] data_;
    data_= nullptr;
    size_ = 0;
    error_=ErrorCode::kNoError;
}

void MyVector::push_back(int value){
    int* tmp = new int [size_+1];
    for(int i = 0; i<size_; ++i){
        tmp[i] = data_[i];
    }
    tmp[size_]= value;
    delete [] data_;
    data_ = tmp;
    ++size_;
    error_=ErrorCode::kNoError;
  }

int MyVector::pop_back(){
    if(size_==0){
        error_=ErrorCode::kPopFromEmptyVector;
        return -1;
    }
    int* tmp = new int [size_-1];
    for(int i = 0; i<size_-1; ++i){
        tmp[i] = data_[i];
    }
    int value = data_[size_-1];
    delete [] data_;
    data_ = tmp;
    --size_;
    error_=ErrorCode::kNoError;
    return value;
}

void MyVector::push_front(int value){
    int* tmp = new int [size_+1];
    for(int i = 0; i<size_; ++i){
        tmp[i+1] = data_[i];
    }
    tmp[0]= value;
    delete [] data_;
    data_ = tmp;
    ++size_;
    error_=ErrorCode::kNoError;
}

int MyVector::pop_front(){
    if(size_==0){
        error_=ErrorCode::kPopFromEmptyVector;
        return -1;
    }
    int* tmp = new int [size_-1];
    for(int i = 0; i<size_-1; ++i){
        tmp[i] = data_[i+1];
    }
    int value = data_[0];
    delete [] data_;
    data_ = tmp;
    --size_;
    error_=ErrorCode::kNoError;
    return value;
}

void MyVector::insert(int value, int index){
    if(index<-1 || index>=size_){
        error_=ErrorCode::kIndexError;
        return;
    }
    int* tmp = new int [size_+1];
    for(int i = 0; i<index+1; ++i){
        tmp[i] = data_[i];
    }
    tmp[index+1]= value;
    for(int i = index+2; i<size_+1; ++i){
        tmp[i] = data_[i-1];
    }
    delete [] data_;
    data_ = tmp;
    ++size_;
    error_=ErrorCode::kNoError;
}

int MyVector::at(int index){
    if(index<0 || index>=size_){
        error_=ErrorCode::kIndexError;
        return -1;
    }
    error_=ErrorCode::kNoError;
    return data_[index];
}

int MyVector::find(int item){
    for(int i = 0; i<size_;++i){
        if(data_[i]==item){
            return i;
        }
    }
    error_=ErrorCode::kNotFound;
    return -1;
}

ErrorCode MyVector::get_error() const{
    return error_;
}

int MyVector::size() const{
    return size_;
}

std::vector<int> MyVector::ConvertToStdVector(){
    std::vector<int> temp;
    for(int i=0; i<size_; ++i){
        temp.push_back(data_[i]);
    }
    error_=ErrorCode::kNoError;
    return temp;
}