Q1:
  {
    std::cout << "Q1" << std::endl;
    MyClass o1;
    std::cout << "o1.v_.size(): " << o1.v_.size() << std::endl;
  }
Q1
Non-parameterized constructor
o1.v_.size(): 0
Destructor
ANS: This block calls the non-parameterized constructor. The vector v_ gets initialized because it's a member variable. But the non-parameterized constructor does not push values to the vector v_ so the size of v_should be 0. Finally the block calls the destructor to delete o1.

Q2:
  {
    std::cout << "Q2" << std::endl;
    MyClass o1;
    MyClass o2(1, 3);
    MyClass o3 = o1;
  }
Q2
Non-parameterized constructor
Parameterized constructor
Copy constructor
Destructor
Destructor
Destructor
ANS: This block calls the non-parameterized constructor, parameterized constructor and copy constructor respectiveely. And, finally, it needs to call destructor delete all of them.

Q3:
  {
    std::cout << "Q3" << std::endl;
    MyClass o;
    DoSomething1(o);
  }
Q3
Non-parameterized constructor
Copy constructor
Something 1.
Destructor
Destructor
ANS: This block calls the non-parameterized constructor. And DoSomething1 calls the copy constructor. Then it calls destructor first to remove the parameter it copied. Finally the block calls the destructor to delete o.

Q4:
  {
    std::cout << "Q4" << std::endl;
    MyClass o;
    DoSomething2(o);
  }
Q4
Non-parameterized constructor
Something 2.
Destructor
ANS: This block calls the non-parameterized constructor. And DoSomething2 uses reference instead of copy constructor. Finally the block calls the destructor to delete o.

Q5:
  {
    std::cout << "Q5" << std::endl;
    MyClass o;
    DoSomething3(o);
  }
Q5
Non-parameterized constructor
Something 3.
Destructor
ANS: This block calls the non-parameterized constructor. And DoSomething3 uses reference instead of copy constructor. Finally the block calls the destructor to delete o.

Q6:
  {
    std::cout << "Q6" << std::endl;
    MyClass o;
    DoSomething4(o);
  }
Q6
Non-parameterized constructor
Copy constructor
Something 4.
Destructor
Destructor
ANS: This block calls the non-parameterized constructor. And the parameter of DoSomething4 uses reference instead of copy constructor. But inside DoSomething4 o2 calls copy constructor. Then it calls destructor to remove the o2. Finally the block calls the destructor to delete o.

Q7:
  {
    std::cout << "Q7" << std::endl;
    std::pair<MyClass, int> p1 = {MyClass(1, 2), 0};
    std::cout << "p1.first.v_.size(): " << p1.first.v_.size() << std::endl;
    std::cout << "p1.second: " << p1.second << std::endl;

    std::pair<MyClass, int> p2 = p1;
    std::cout << "p2.first.v_.size(): " << p2.first.v_.size() << std::endl;
    std::cout << "p2.second: " << p2.second << std::endl;
  }
Parameterized constructor
Copy constructor
Destructor
p1.first.v_.size(): 0
p1.second: 0
Copy constructor
p2.first.v_.size(): 0
p2.second: 0
Destructor
Destructor
ANS: This block first calls the parameterized constructor to create MYClass(1,2). Then it calls copy constructor to assign the MYClass(1,2) and 0 to p1. Then destructor is called to delete MYClass(1,2).The vector v_ gets initialized because it's a member variable. But the non-parameterized constructor does not push values to the vector v_ so the size of v_should be 0. p1.second gets assigned the value 0. p2 calls copy constructor to copy the value of p1. So the output of p2 should be the same with p1. Finally p1 and p2 call destructor to be deleted.

Q8:
  {
    std::cout << "Q8" << std::endl;
    for (std::pair<MyClass, int> p = {MyClass(1, 2), 0}; p.second < 3;
         p.second++) {
      p.first.v_.push_back(p.second);
      DoSomething2(p.first);
    }
  }
Q8
Parameterized constructor
Copy constructor
Destructor
Something 2.
Something 2.
Something 2.
Destructor
ANS:This block first calls the parameterized constructor to create MYClass(1,2). Then it calls copy constructor to assign the MYClass(1,2) and 0 to p1. Then destructor is called to delete MYClass(1,2). The for loop has 3 iteration. In each iteration, DoSomething2 is called once. So, Something 2. is printed three times. Then the for loop calls destructor to delete p.

Q9:
  {
    std::cout << "Q9" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
  }
Q9
Parameterized constructor
ANS:This block first calls the parameterized constructor to create MyClass(1,2). And then use the printer o to print it. Because the block uses new to store MyClass(1, 2), it does not use destructor to delete MyClass(1,2).

Q10:
  {
    std::cout << "Q10" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
    delete o;
  }
Q10
Parameterized constructor
Destructor
ANS:This block first calls the parameterized constructor to create MyClass(1,2). And then use the printer o to print it. Because the block uses new to store MyClass(1, 2), it need to  use delete to call destructor to delete MyClass(1,2).

Q11:
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
Q11
Non-parameterized constructor
Copy constructor
Parameterized constructor
Copy constructor
Parameterized constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Copy constructor
Destructor
Copy constructor
Destructor
Copy constructor
Destructor
Destructor
Destructor
Destructor
ANS: Firstly, this block calls non-parameterized constructor. And then call copy constructor to assign {0, MyClass()} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. Secondly, this block calls parameterized constructor. And then call copy constructor to assign {3, MyClass(1, 2)} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. Thirdly, this block calls parameterized constructor. And then call copy constructor to assign {5, MyClass(3, 4)} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. After that this block calls copy constructor three times to assign {0, MyClass()}, {3, MyClass(1, 2)} and {5, MyClass(3, 4)} to my_map. Then, this block call destructor six times to delete {0, MyClass()}, {3, MyClass(1, 2)}, {5, MyClass(3, 4)} and {0, MyClass()}, {3, MyClass(1, 2)}, {5, MyClass(3, 4)} in {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. In the for loop, in each iteration, e is initialized with the copy constructor. After each iteration, e is deleted by calling destructor. There are 3 iterations. Finally, the block calls three destructor to delete {0, MyClass()}, {3, MyClass(1, 2)} and {5, MyClass(3, 4)} in my_map.

Q12:
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
Q12
Non-parameterized constructor
Copy constructor
Parameterized constructor
Copy constructor
Parameterized constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
ANS:Firstly, this block calls non-parameterized constructor. And then call copy constructor to assign {0, MyClass()} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. Secondly, this block calls parameterized constructor. And then call copy constructor to assign {3, MyClass(1, 2)} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. Thirdly, this block calls parameterized constructor. And then call copy constructor to assign {5, MyClass(3, 4)} to {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. After that this block calls copy constructor three times to assign {0, MyClass()}, {3, MyClass(1, 2)} and {5, MyClass(3, 4)} to my_map. Then, this block call destructor six times to delete {0, MyClass()}, {3, MyClass(1, 2)}, {5, MyClass(3, 4)} and {0, MyClass()}, {3, MyClass(1, 2)}, {5, MyClass(3, 4)} in {{0, MyClass()},{3, MyClass(1, 2)},{5, MyClass(3, 4)}}. In the for loop, in each iteration, e uses reference instead of copy constructor. Finally, the block calls three destructor to delete {0, MyClass()}, {3, MyClass(1, 2)} and {5, MyClass(3, 4)} in my_map.

Q13:
  {
    std::cout << "Q13" << std::endl;
    MyClass *o;
    o = new MyClass(1, 2);
    delete o;
  }
Q13
Parameterized constructor
Destructor
ANS:This block first calls the parameterized constructor to create MyClass(1,2). And then use the printer o to print it. Because the block uses new to store MyClass(1, 2), it need to  use delete to call destructor to delete MyClass(1,2).

Q14:
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
Q14
Parameterized constructor
Operation took: 1207 milliseconds
Copy constructor
Copy constructor
Something 1.
Destructor
o2.v_.size(): 100000000
Destructor
Copy constructor
Copy constructor
Something 1.
Destructor
o2.v_.size(): 100000000
Destructor
Operation took: 658 milliseconds
Destructor
ANS:The block uses StoreStartTime() to store the current time into g_start_time. Then it calls parameterized constructor to initilize o. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Then, the block uses StoreStartTime() to store the current time into g_start_time. Then, in the for loop, the block calls copy constructor to assign the value of o to o2 and assign the value of o2 to the prameter of DoSomething1. After DoSomething1, the block call destructor to delete the prameter of DoSomething1. The vector v_ gets initialized because it's a member variable. And the copy constructor push value 100000000 to the vector v_ so the size of v_should be 100000000. After each iteration the block calls destructor to delete o2. This procedure repeats two times. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Finally, the block calls destructor to delete o.

Q15:
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
Q15
Parameterized constructor
Operation took: 1234 milliseconds
Copy constructor
Something 2.
o2.v_.size(): 100000000
Destructor
Copy constructor
Something 2.
o2.v_.size(): 100000000
Destructor
Operation took: 329 milliseconds
Destructor
ANS: The block uses StoreStartTime() to store the current time into g_start_time. Then it calls parameterized constructor to initilize o. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Then, the block uses StoreStartTime() to store the current time into g_start_time. Then, in the for loop, the block calls copy constructor to assign the value of o to o2 and uses reference in DoSomething2. The vector v_ gets initialized because it's a member variable. And the copy constructor push value 100000000 to the vector v_ so the size of v_should be 100000000. After each iteration the block calls destructor to delete o2. This procedure repeats two times. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Finally, the block calls destructor to delete o.

Q16:
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
Q16
Parameterized constructor
Parameterized constructor
Parameterized constructor
Parameterized constructor
Parameterized constructor
Parameterized constructor
Parameterized constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Copy constructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Operation took: 3694 milliseconds
Copy constructor
e.v_.size(): 10000000
Destructor
Copy constructor
e.v_.size(): 20000000
Destructor
Copy constructor
e.v_.size(): 30000000
Destructor
Copy constructor
e.v_.size(): 40000000
Destructor
Copy constructor
e.v_.size(): 50000000
Destructor
Copy constructor
e.v_.size(): 60000000
Destructor
Copy constructor
e.v_.size(): 70000000
Destructor
Operation took: 470 milliseconds
e.v_.size(): 10000000
e.v_.size(): 20000000
e.v_.size(): 30000000
e.v_.size(): 40000000
e.v_.size(): 50000000
e.v_.size(): 60000000
e.v_.size(): 70000000
Operation took: 0 milliseconds
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
ANS: The block uses StoreStartTime() to store the current time into g_start_time. Then the block calls parameterized constructor seven times to initilize MyClass(10000000), MyClass(20000000), MyClass(30000000), MyClass(40000000), MyClass(50000000), MyClass(60000000) and MyClass(70000000). Then the blocks calls copy constructor seven times to assign the them to the first 7 elements of my_vector. After that the block calls destructor seven times to delete MyClass(10000000), MyClass(20000000), MyClass(30000000), MyClass(40000000), MyClass(50000000), MyClass(60000000) and MyClass(70000000). After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Then, the block uses StoreStartTime() to store the current time into g_start_time. Then, in the for loop, the block calls copy constructor to assign the element in my_vector to e. The vector v_ gets initialized because it's a member variable. And the copy constructor push value 100000000 to the vector v_ so the size of v_should be 100000000. After each iteration the block calls destructor to delete e. This procedure repeats seven times. The vector v_ gets initialized with 100000000, 200000000, 300000000, 400000000, 500000000, 600000000 and 700000000 respectively. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Finally, the block calls destructor to delete o. Then, the block uses StoreStartTime() to store the current time into g_start_time. Then, in the for loop, the block uses reference to assign the element in my_vector to e. The vector v_ gets initialized because it's a member variable. And the copy constructor push value 100000000 to the vector v_ so the size of v_should be 100000000. This procedure repeats seven times. The vector v_ gets initialized with 100000000, 200000000, 300000000, 400000000, 500000000, 600000000 and 700000000 respectively. After that, the block uses PrintAndGetDuration() to caculate the difference from the current time to g_start_time in seconds and prints it out. Finally, the seven elements in my_vector calls destructor to be deleted.