#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(SinglyLinkedList ,test1){
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    class SinglyLinkedList linkedlist(v);
    class SinglyLinkedList linkedlist1(linkedlist);
    class SinglyLinkedList linkedlist2;
    for(int i =0 ; i<linkedlist.size(); ++i ){
        EXPECT_EQ(linkedlist[i],linkedlist1[i]);
    }
    linkedlist1.pop_back();
    EXPECT_EQ(linkedlist[1],linkedlist1.back());
    linkedlist1.push_back(3);
    EXPECT_EQ(linkedlist[2],linkedlist1.back());
    for(int i =0 ; i<v.size(); ++i ){
        EXPECT_EQ(linkedlist.convert_to_vector()[i],v[i]);
    }
    linkedlist1.erase(1);
    EXPECT_EQ(linkedlist[0],linkedlist1[0]);
    EXPECT_EQ(linkedlist[2],linkedlist1[1]);
    linkedlist.~SinglyLinkedList();
    linkedlist1.~SinglyLinkedList();
}