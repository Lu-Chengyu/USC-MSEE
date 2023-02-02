#ifndef SOL_4_Q
#define SOL_4_Q
#include <iostream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// An enum class representing error
// Don't touch this part!
//-----------------------------------------------------------------------------
enum class ErrorCode {
  kNoError,
  kPopFromEmptyVector,
  // If there is an attempt to access an invalid index
  kIndexError,
  kNotFound
};

//-----------------------------------------------------------------------------
// Implement your own vector class!
// all functions must set the error_ to an appropriate value.
// TODO: Implement these functions in q.cc.
class MyVector {
 public:
  // Creates an empty vector.
  MyVector();

  // Creates a vector of the given size.
  MyVector(int size);

  // Copy constructor.
  MyVector(const MyVector& rhs);

  // Destructor.
  // Should delete data and set it to nullptr. Also set size_ to 0.
  ~MyVector();

  // Inserts the given value at the back of the vector.
  void push_back(int value);

  // Removes and returns a value from the backs of the vector.
  int pop_back();

  // Inserts the given value at the front of the vector.
  void push_front(int value);

  // Removes and returns a value from the front of the vector.
  int pop_front();

  // Inserts the given value after the given index.
  // 1. Create a new dynamic array
  // 2. Copy from the old array until index
  // 3. insert value
  // 4. Copy the rest from the old array.
  // 5. DELETE the array.
  // 6. return the pointer inside the new dynamic array.

  // If the given index is -1, it inserts the item at the very beginning of the
  // vector.
  void insert(int value, int index);

  // Returns the item at the given index.
  int at(int index);

  // Returns the first index of the given item in the vector. Returns -1 if not
  // found.
  int find(int item);

  // Returns the value of error_
  ErrorCode get_error() const;

  // Returns the value of size_
  int size() const;

  // Converts to std::vector. Used for testing.
  std::vector<int> ConvertToStdVector();

 private:
  int* data_;
  int size_;
  ErrorCode error_;
};


#endif /* SOL_4_Q */
