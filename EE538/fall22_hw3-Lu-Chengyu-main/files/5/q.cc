#include "q.h"
#include <climits>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc
int BinaryTree::GetParentIndex(int i){
    if(i<=0){
        return -1;
    }
    else{
        return ((i-1)/2);
    }
}

int BinaryTree::GetLeftIndex(int i){
    return (i*2+1);
}

int BinaryTree::GetRightIndex(int i){
    return (i*2+2);
}

int BinaryTree::FindMin(int i){
    if(i<v_.size() && i>=0&&v_[i]!=-1){
        return std::min(std::min(v_[i],FindMin(GetLeftIndex(i))), FindMin(GetRightIndex(i)));
    }
    else{
        return INT_MAX;
    }
}

int BinaryTree::FindMax(int i){
    if(i<v_.size()&& i>=0&&v_[i]!=-1){
        return std::max(std::max(v_[i],FindMax(GetLeftIndex(i))), FindMax(GetRightIndex(i)));
    }
    else{
        return INT_MIN;
    }
}

bool BinaryTree::IsLeaf(int i){
    if(GetLeftIndex(i)>=v_.size() && i<v_.size() && i>=0){
        return true;
    }
    else{
        return false;
    }
}

std::vector<int> BinaryTree::PreOrder(int i){
    std::vector<int> temp;
    if(i<v_.size() && i>=0 && v_.size()!=0 && v_[i]!=-1){
        temp.push_back(v_[i]);
        temp.insert(temp.end(), PreOrder(GetLeftIndex(i)).begin(), PreOrder(GetLeftIndex(i)).end());
	    temp.insert(temp.end(), PreOrder(GetRightIndex(i)).begin(), PreOrder(GetRightIndex(i)).end());
        return temp;
    }
    else{
        return temp;
    }
}