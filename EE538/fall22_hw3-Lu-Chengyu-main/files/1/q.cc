
#include "q.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>

// This is not a coding question.
// No need for unit tests for this question.
// TODO: Answer each question asked in the main() function in the README file.
// The following functions are used for measuring the time of an operation. You
// don't need to change them.
//
// StoreStartTime();      -> Stores the current time.
// Operation();           -> The operation we are measuring.
// PrintAndGetDuration(); -> Print the time from StoreStartTime until now.
//
//-----------------------------------------------------------------------------
// No need to change the following definitions!
class MyClass {
 public:
  MyClass() {
    a_ = 0;
    b_ = 0;
    ptr_ = new int;
    std::cout << "Non-parameterized constructor" << std::endl;
  }

  MyClass(int a, int b) {
    ptr_ = new int;
    a_ = a;
    b_ = b;
    std::cout << "Parameterized constructor" << std::endl;
  }

  MyClass(int size) {
    ptr_ = new int;
    a_ = 0;
    b_ = 0;
    for (int i = 0; i < size; i++) {
      v_.push_back(i);
    }
    std::cout << "Parameterized constructor" << std::endl;
  }

  MyClass(const MyClass &rhs) {
    a_ = rhs.a_;
    b_ = rhs.b_;
    v_ = rhs.v_;
    ptr_ = new int;
    *ptr_ = *rhs.ptr_;
    std::cout << "Copy constructor" << std::endl;
  }

  ~MyClass() {
    if (ptr_ != nullptr) {
      delete ptr_;
      ptr_ = nullptr;
    }
    std::cout << "Destructor" << std::endl;
  }

 public:
  std::vector<int> v_;

 private:
  int a_;
  int b_;
  int *ptr_;
};

//-----------------------------------------------------------------------------
// No need to change the following definitions!
// These are some simple functions that we will call from main.

void DoSomething1(MyClass o) { std::cout << "Something 1." << std::endl; }

void DoSomething2(MyClass &o) { std::cout << "Something 2." << std::endl; }

void DoSomething3(MyClass &o) { std::cout << "Something 3." << std::endl; }

void DoSomething4(MyClass &o) {
  MyClass o2 = o;
  std::cout << "Something 4." << std::endl;
}

//-----------------------------------------------------------------------------
int main() {
  // Q1
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q1" << std::endl;
    MyClass o1;
    std::cout << "o1.v_.size(): " << o1.v_.size() << std::endl;
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q2
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q2" << std::endl;
    MyClass o1;
    MyClass o2(1, 3);
    MyClass o3 = o1;
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q3
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q3" << std::endl;
    MyClass o;
    DoSomething1(o);
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q4
  // What is the output? Explain why each line (or group of lines) are printed.
  // Why the output is different than the previous question?
  {
    std::cout << "Q4" << std::endl;
    MyClass o;
    DoSomething2(o);
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q5
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q5" << std::endl;
    MyClass o;
    DoSomething3(o);
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q6
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q6" << std::endl;
    MyClass o;
    DoSomething4(o);
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  {
    // Q7
    // What is the output? Explain why each line (or group of lines) are
    // printed.
    // Notice that std::pair might internally copy objects of MyClass. Please
    // specify those calls.
    std::cout << "Q7" << std::endl;
    std::pair<MyClass, int> p1 = {MyClass(1, 2), 0};
    std::cout << "p1.first.v_.size(): " << p1.first.v_.size() << std::endl;
    std::cout << "p1.second: " << p1.second << std::endl;

    std::pair<MyClass, int> p2 = p1;
    std::cout << "p2.first.v_.size(): " << p2.first.v_.size() << std::endl;
    std::cout << "p2.second: " << p2.second << std::endl;
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q8
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q8" << std::endl;
    for (std::pair<MyClass, int> p = {MyClass(1, 2), 0}; p.second < 3;
         p.second++) {
      p.first.v_.push_back(p.second);
      DoSomething2(p.first);
    }
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q9
  // What is the output? Explain why each line (or group of lines) are printed.
  // Why the destructor is not called? Is this a problem? If so, what is it
  // called?
  {
    std::cout << "Q9" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q10
  // What is the output? Explain why each line (or group of lines) are printed.
  // Why the destructor is called?
  {
    std::cout << "Q10" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
    delete o;
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q11
  // What is the output? Explain why each line (or group of lines) are printed.
  // Notice that std::map might internally copy objects of MyClass. Please
  // specify those calls.
  {
    std::cout << "Q11" << std::endl;
    std::map<int, MyClass> my_map = {//
                                     {0, MyClass()},
                                     {3, MyClass(1, 2)},
                                     {5, MyClass(3, 4)}};
    std::set<int> my_set;

    for (auto e : my_map) {
      my_set.insert(e.first);
    }
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q12
  // What is the output? Explain why each line (or group of lines) are printed.
  // Notice that std::map and set might internally copy objects of MyClass.
  // Please specify those calls.
  {
    std::cout << "Q12" << std::endl;
    std::map<int, MyClass> my_map = {//
                                     {0, MyClass()},
                                     {3, MyClass(1, 2)},
                                     {5, MyClass(3, 4)}};
    std::set<int> my_set;

    for (const auto &e : my_map) {
      my_set.insert(e.first);
    }
  }

  // Similar to the previous question, however in the loop we don't make copies
  // so no copy constructor and no destructor will be called.

  std::cout << "---------------------------------------------------------------"
            << std::endl;
  // Q13
  // What is the output? Explain why each line (or group of lines) are printed.
  {
    std::cout << "Q13" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
    delete o;
  }

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Similar to Q10.

  // Q14
  // What is the output? Explain why each line (or group of lines) are printed.
  // Explain the time of the measured operations.
  {
    std::cout << "Q14" << std::endl;
    StoreStartTime();
    MyClass o(100000000);
    PrintAndGetDuration();

    StoreStartTime();
    for (int i = 0; i < 2; i++) {
      MyClass o2 = o;
      DoSomething1(o2);
      std::cout << "o2.v_.size(): " << o2.v_.size() << std::endl;
    }
    PrintAndGetDuration();
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q15
  // What is the output? Explain why each line (or group of lines) are printed.
  // Explain the time of the measured operations.
  {
    std::cout << "Q15" << std::endl;
    StoreStartTime();
    MyClass o(100000000);
    PrintAndGetDuration();

    StoreStartTime();
    for (int i = 0; i < 2; i++) {
      MyClass o2 = o;
      DoSomething2(o2);
      std::cout << "o2.v_.size(): " << o2.v_.size() << std::endl;
    }
    PrintAndGetDuration();
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;

  // Q16
  // What is the output? Explain why each line (or group of lines) are printed.
  // Notice that std::vector might internally copy objects of MyClass. Please
  // specify those calls.
  // Explain the time of the measured operations.
  {
    std::cout << "Q16" << std::endl;
    StoreStartTime();
    std::vector<MyClass> my_vector = {MyClass(10000000), MyClass(20000000),
                                      MyClass(30000000), MyClass(40000000),
                                      MyClass(50000000), MyClass(60000000),
                                      MyClass(70000000)};
    PrintAndGetDuration();

    StoreStartTime();
    for (auto e : my_vector) {
      std::cout << "e.v_.size(): " << e.v_.size() << std::endl;
    }
    PrintAndGetDuration();

    StoreStartTime();
    for (const auto &e : my_vector) {
      std::cout << "e.v_.size(): " << e.v_.size() << std::endl;
    }
    PrintAndGetDuration();
  }
  std::cout << "---------------------------------------------------------------"
            << std::endl;
  std::cout << "Done!" << std::endl;
}
