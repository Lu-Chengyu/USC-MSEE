
// Define a new C++ enum type called Operation that has members for add,
// subtract, division,  subtraction, bitwise AND, bitwise OR, bitwise XOR, shift
// right, and shift left:
enum class Operation {
  kAdd,
  kSubtract,
  kDivision,
  kMultiplication,
  kBitwise_AND,
  kBitwise_OR,
  kBitwise_XOR,
  kShift_right,
  kShift_left
};

// Given two integers, returns the result of the operation based on the given
// operator.
float Calculate(int a, int b, Operation operation);
