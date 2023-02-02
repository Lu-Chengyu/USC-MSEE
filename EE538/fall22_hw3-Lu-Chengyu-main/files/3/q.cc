#include "q.h"

#include <climits>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
Queue::Queue(const Queue& rhs){
    v_=rhs.v_;
}

 Queue& Queue::operator=(const Queue& rhs){
    v_=rhs.v_;
    return *this;
 }

 Queue Queue::operator+(const Queue& rhs){
    Queue res;
    for(int i = 0; i<rhs.v_.size();++i){
        res.v_.push_back(rhs.v_[i]);
    }
    for(int i = 0; i<v_.size();++i){
        res.v_.push_back(v_[i]);
    }
    return res;
 }

bool Queue::Enqueue(int value){
    v_.push_back(value);
    return true;
}

bool Queue::Dequeue(){
    if(v_.size()==0) return false;
    v_.erase(v_.begin());
    return true;
}

bool Queue::IsEmpty(){
    return v_.empty();
}

int Queue::Front(){
    if(v_.empty()) return -1;
    return v_[0];
}