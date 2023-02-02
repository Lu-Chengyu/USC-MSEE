#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(Queue ,test1){
    Queue queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    Queue queue1(queue);
    for(int i = 0; i<queue.GetData().size();++i){
        EXPECT_EQ(queue.GetData()[i],queue1.GetData()[i]);
    }
    Queue queue2;
    queue2.Enqueue(4);
    queue2.Enqueue(5);
    Queue queue3;
    queue3 = queue2;
    for(int i = 0; i<queue2.GetData().size();++i){
        EXPECT_EQ(queue2.GetData()[i],queue3.GetData()[i]);
    }
    Queue queue4;
    queue4 = queue3 + queue1;
    queue4.Dequeue();
    EXPECT_EQ(queue4.Front(),2);
    queue4.Dequeue();
    queue4.Dequeue();
    queue4.Dequeue();
    queue4.Dequeue();
    EXPECT_EQ(queue4.IsEmpty(),true);
}