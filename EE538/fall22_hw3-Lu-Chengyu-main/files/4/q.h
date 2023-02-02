#include <iostream>
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
// A node in the linked list. Already implemented. No need to change.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class SinglyLinkedList {
 private:
  ListNode *head_;  // Pointer to the head of the list.
  int size_;        // The current size of the list.
  int minusOne_ = -1;

 public:
  // Constructor. Already implemented. No need to change.
  SinglyLinkedList() {
    head_ = nullptr;
    size_ = 0;
  }

  // *********************************************************************
  // TODO: Implement the following functions in q.cc.
  // *********************************************************************
  // Write a new parameterized constructor that takes a vector as an input and
  // crates a linked list based on that. Note that your constructor should
  // assign a valid value for head_. Example:
  // Input:  v = {1, 4, 5, 6, 10}
  // The created list: 1->4->5->6->10, and head_ will point to the first node
  // with value 1.
  SinglyLinkedList(const std::vector<int> &v);

  // Copy constructor.
  SinglyLinkedList(const SinglyLinkedList &rhs);

  // Returns true if the list is empty, false otherwise.
  bool empty();

  // Returns the current size of the list.
  int size();

  // Returns a pointer to the head of the list.
  ListNode *head();

  // Insert i at the back of the list.
  void push_back(int i);

  // Removes an item from the back of the list. Returns true if it was
  // successful.
  bool pop_back();

  // Returns the item in the back of the list. Returns -1 if empty.
  int back();

  // Returns a pointer to the back of the list.
  ListNode *GetBackPointer();

  // Returns a pointer to the i(th) element in the list. nullptr if it doesn't
  // exist.
  ListNode *GetIthPointer(int i);

  // Returns the i(th) element in the list. -1 if it doesn't exits.
  int &operator[](int i);

  // Prints the items in the list.
  void print();

  // Write a function that converts the list into a vector. Example:
  // The list: 1->4->5->6->10
  // Output: a vector with value: {1, 4, 5, 6, 10}
  std::vector<int> convert_to_vector();

  // Erases element i from the list if it exists and returns a pointer to item
  // i-1. If item i doesn't exist, returns nullptr. The first item in the list
  // has index 0.

  // Example:
  // Input: 1 -> 5 -> 10 ->20, i= 2.
  // Output: 1 -> 5 -> 20, return value: a pointer to element 5.
  ListNode *erase(int i);

  // Removes duplicate elements and only keeps the first one.
  // Example:
  // Input: 1 -> 5 -> 1 -> 20 -> 4 -> 5 -> 32
  // Output: 1 -> 5 -> 20 -> 4 -> 32
  void remove_duplicates();

  ~SinglyLinkedList();
};
