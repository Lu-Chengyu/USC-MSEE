#include <iostream>
#include <string>
#include <vector>

class Queue {
 public:
  // Constructor is already defined. No implementation or modification
  // necessary.
  Queue() {}

  // Copy constructor.
  Queue(const Queue& rhs);

  // Copy assignment.
  // It is used when you have a code like this:
  // Queue q1, q2;
  // q1 = q2;
  // It returns a reference to *this, i.e., at the end of the function, add
  // "return *this;";
  // The return value is used for cases like this:
  // q1 = q2 = q3;
  // This will first call q2.operator=(q3)
  // then the result of this function is passed to q1.operator=(result);
  Queue& operator=(const Queue& rhs);

  // Returns a new queue that has all elements of q2 followed by q1 in order.
  // Example:
  // q1={1, 2, 3}, i.e. front is 1, back is 3
  // q2={4, 5}, i.e. front is 4, back is 5
  // q3 = q1 + q2 = {4, 5, 1, 2, 3}, i.e. front is 4, back is 3
  Queue operator+(const Queue& rhs);

  // Inserts in the back of the queue.
  bool Enqueue(int value);

  // Removes from the front of the queue. If the queue is empty, return false,
  // otherwise true.
  bool Dequeue();

  // Returns true if the queue is empty.
  bool IsEmpty();

  // Returns the value in the front of the queue. If the queue is empty, return
  // -1.
  int Front();

  // No need to change this function. Already implemented.
  std::vector<int> GetData() { return v_; }

 private:
  std::vector<int> v_;
};
