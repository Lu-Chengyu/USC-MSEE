
# HW1 EE538
## University of Southern California
## Instructor: Arash Saifhashemi

Please clone this repository, edit README.md to answer the questions, and fill up functions to finish the homework.

- Please find each question in a separate folder under [file](/file).
- For non-coding questions, fill out the answers in the README file.
- For coding questions, edit the files and check them in.
- For coding questions unless specified, you should add unit tests to the student_test.cc.
  We will clone and test your repo using your tests and some other tests (that are not provided). Your code should pass all of them.
- For submission, please push your answers to Github before the deadline.
- Deadline: Sep 19 by 12:00 pm (noon)
- Rubrics:
  
| Question | Points |
| -------- | ------ |
| 1        | 40     |
| 2        | 20     |
| 3        | 20     |
| 4        | 20     |
| 5        | 20     |
| 6        | 12     |

- Total: 132 points. 100 points is considered full credit.


See [cpp-template](https://github.com/ourarash/cpp-template) for help on installing bazel and debugging.

# Question 1 to 5
Coding question: please refer to [files](/files).

# Question 6
Please write down the worst case runtime complexity of the functions that you implement in this README file. 
For each case, please provide a reason.

Question 1
Reverse -> n/2 -> O(n), because the for loop is from 0 to input.size()/2.
PlusOne -> O(n), because, in the worst case, the for loop is from 0 to input.size().

Question 2
IsPrime -> O(sqrt(n)), because, in the worst case, the for loop is from 2 to sqrt(number).

Question 3
CountNumberOfSpaces -> O(n), because the for loop is from 0 to input.size().

Question 4
Flatten3DVector -> O(n), n is the number of items. Because the for loop take every items out and assign them to the new vector.

Question 5
ClimbStairs -> O(n), because the for loop is from 4 to n.
