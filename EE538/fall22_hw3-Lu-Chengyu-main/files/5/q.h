#include <iostream>
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
// Create a Binary Tree class using a vector (no pointers).
// Assume: the BT only keeps non-negative numbers. Use -1 for nodes that are
// missing.
class BinaryTree {
 public:
  //-----------------------------------------------------------------------------
  // The following is already implemented, don't touch!
  //-----------------------------------------------------------------------------
  // Constructors
  BinaryTree() {}
  BinaryTree(int size) { v_.resize(size, -1); }
  BinaryTree(std::vector<int> const& v) { v_ = v; }

  // Accessing Data. Used only for testing.
  std::vector<int> GetData() { return v_; }
  //-----------------------------------------------------------------------------
  // TODO: Implement the following functions.
  //-----------------------------------------------------------------------------
  // Returns the index of the parent of a node given its index in the tree.
  // Returns -1 if there is no parent.
  int GetParentIndex(int i);

  // Returns the index of the left child of a node given its index. Return the
  // index of the left child even if the left child does not exits, i.e. never
  // return -1;
  int GetLeftIndex(int i);

  // Returns the index of the right child of a node given its index in the tree.
  // Return the index of the right child even if the left child does not exits,
  // i.e. never return -1.
  int GetRightIndex(int i);

  // Returns the minimum value in the subtree with root at index i;
  // If the node at index i does not exist, return INT_MAX.
  int FindMin(int i);

  // Returns the maximum value in the subtree with root at index i;
  // If the node at index i does not exist, return INT_MIN.
  int FindMax(int i);

  // Returns true if the node at index i is a leaf.
  // If the node at index i does not exists, returns false;
  bool IsLeaf(int i);

  // Returns the nodes in the tree with root index i in PreOrder.
  // If the tree was empty or i is invalid, return an empty vector.
  std::vector<int> PreOrder(int i);

 private:
  std::vector<int> v_;
};