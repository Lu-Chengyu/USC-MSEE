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
SinglyLinkedList::SinglyLinkedList(const std::vector<int> &v){
    if(!v.empty()){
        ListNode* p2;
        ListNode* node = new ListNode(v[0]);
        head_ = node;
        p2 = head_;
        for(int i =1; i<v.size();++i){
            ListNode* node1 = new ListNode(v[i]);
            p2->next = node1;
            p2 = node1;
        }
        size_ = v.size();
    }
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList &rhs){
    if(rhs.head_ != nullptr){
        ListNode* p1 = rhs.head_;
        ListNode* p2;
        ListNode* node = new ListNode(p1->val);
        head_ = node;
        p2 = head_;
        while(p1->next != nullptr){
            p1 =p1->next;
            ListNode* node1 = new ListNode(p1->val);
            p2->next = node1;
            p2 =node1;
        }
        size_=rhs.size_;
    }
}

bool SinglyLinkedList::empty(){
    if(size_ == 0) return true;
    return false;
}

int SinglyLinkedList::size(){
    return size_;
}

ListNode * SinglyLinkedList::head(){
    return head_;
}

void SinglyLinkedList::push_back(int i){
    ListNode* p1 = head_;
    ListNode* node = new ListNode(i);
    if(p1==nullptr){
        head_ = node;
        size_ = 1;
    }
    else{    
        while(p1->next != nullptr){
            p1 = p1->next;
        }
        p1->next = node;
        size_+=1;
    }
}

bool SinglyLinkedList::pop_back(){
    ListNode* p1 = head_;
    if(p1 == nullptr){
        return false;
    }
    else if(head_->next == nullptr){
        delete head_;
        head_=nullptr;
        size_=0;
        return true;
    }
    while(p1->next->next != nullptr){
        p1 = p1->next;
    }
    delete p1->next;
    p1->next= nullptr;
    size_ -= 1;
    return true;
}

int SinglyLinkedList::back(){
    ListNode* p1 = head_;
    if(p1 == nullptr) return -1;
    while(p1->next != nullptr){
        p1 = p1->next;
    }
    return p1->val;
}

ListNode * SinglyLinkedList::GetBackPointer(){
    ListNode* p1 = head_;
    if(p1 == nullptr) return p1;
    while(p1->next != nullptr){
        p1 = p1->next;
    }
    return p1;
}

ListNode * SinglyLinkedList::GetIthPointer(int i){
    ListNode* p1 = head_;
    if(p1 == nullptr || i<0) return nullptr;
    for(int j = 0; j<i; ++j){
        p1= p1->next;
        if(p1 == nullptr) return nullptr;
    }
    return p1;
}

int & SinglyLinkedList::operator[](int i){
    ListNode* p1 = head_;
    if(p1 == nullptr || i<0) return minusOne_;
    for(int j = 0; j<i; ++j){
        p1= p1->next;
        if(p1 == nullptr) return minusOne_;
    }
    return p1->val;
}

void SinglyLinkedList::print(){
    ListNode* p1 = head_;
    if(p1 != nullptr){
        std::cout<<p1->val<<std::endl;
    }
    while(p1->next != nullptr){
        p1 = p1->next;
        std::cout<<p1->val<<std::endl;
    }
}

std::vector<int> SinglyLinkedList::convert_to_vector(){
    std::vector<int> temp;
    ListNode* p1 = head_;
    if(p1 == nullptr) return temp;
    temp.push_back(p1->val);
    while(p1->next != nullptr){
        p1 = p1->next;
        temp.push_back(p1->val);
    }
    return temp;
}

ListNode * SinglyLinkedList::erase(int i){
    ListNode* p1 = head_;
    ListNode* p2 = nullptr;
    if(head_ == nullptr || i<0) return nullptr;
    if(head_->next == nullptr && i == 0){
        delete head_;
        head_ = nullptr;
        size_ = 0;
        return head_;
    }
    for(int j = 0; j<i; ++j){
        p2 = p1;
        p1= p1->next;
        if(p1 == nullptr) return nullptr;
    }
    if(p2==nullptr){
        p2 = p1->next;
        delete p1;
        head_ = p2;
        size_-=1;
        return nullptr;
    }
    else{
        p2->next = p1->next;
        delete p1;
        size_-=1;
        return p2;
    }

}

void SinglyLinkedList::remove_duplicates(){
    ListNode* p1 = head_;
    ListNode* p2 = nullptr;
    ListNode* p3 = nullptr;
    if(head_==nullptr) return;
    while(p1->next != nullptr){
        p2 = p1->next;
        p3 = p1;
        do{
            if(p2->val == p1->val){
                p3->next = p2->next;
                delete p2;
                size_-=1;
                p2=p3->next;
            }else{
                p3 = p2;
                p2=p3->next;
            }
        }while(p2!= nullptr);
        p1=p1->next;
    }
}

SinglyLinkedList::~SinglyLinkedList(){
    ListNode* p1 = head_;
    if(head_!= nullptr){
        ListNode* p2 = p1->next;
        for(int i =0; i<size_; ++i){
            delete p1;
            p1 = p2;
            if(p1!=nullptr) p2 = p1->next;
        }
        head_=nullptr;
        size_=0;
    }
}