/****************************************************************************
    BinaryTreeOperations Library (It uses Iterative technique to perform all operation (Some are iterations converted from recursion).
    Copyright (C) 2016  Anubhav Arun <dr.xperience@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/
#ifndef BINARYTREEOPERATIONS_H
#define BINARYTREEOPERATIONS_H

#include "BinaryTree.h"
#include <deque>
#include <type_traits>

template <class T>
class BinaryTreeOperations : public BinaryTree<T>
{
  public:
  // Constructors
  BinaryTreeOperations();
  BinaryTreeOperations(T);
  BinaryTreeOperations(BinaryTreeOperations&);
  virtual ~BinaryTreeOperations();

  // MemberFunction
  void recursionPreOrder(void (*process)(T));
  void traverseLevelOrder(void (*process)(T));
  void printLevelOrder(void (*process)(T, bool newLine, bool leaveNode));
  void traversePreOrderTraversal(void (*process)(T));

  // Complexity O(3N) or O(N) -- it can be reduced to O(N) literally
  // But haven't tried will try sometime
  void traversePostOrderTraversal(void (*process)(T));
  long heightDFS();
  long heightBFS();

  // diameter with O(N*N) or O(N^2) complexity
  long diameterN2();

  // diameter with O(N) complexity
  long diameter();

  // Method to return the nodes of diameter in linked list
  // Complexity O(N*M), where N= total number of nodes and M is twice the no. of levels of tree
  std::deque<unsigned long> diameterPrint();

  // To print the all the path to leave nodes
  // Complexity O(N*M), where N= total number of nodes and M is total no. of levels of the tree
  void pathToLeavesPrint(void (*process)(std::deque<unsigned long>&));

  // To check whether the sum of node->data in a path from root to any node in a tree equals a given sum value
  // Complexity O(N)
  // using SFINAE and type traits to check, whether T is a numerical value

  // This one when T is not numeric
  template <typename TT = T,
            typename std::enable_if<!(std::is_same<float, TT>::value || std::is_same<double, TT>::value || std::is_same<unsigned int, TT>::value ||
                                      std::is_same<unsigned long, TT>::value)>::type* = nullptr>
  int isSumEqualsToDataSum(unsigned long sum);

  // This one when T is numeric
  template <typename TT = T,
            typename std::enable_if<std::is_same<float, TT>::value || std::is_same<double, TT>::value || std::is_same<unsigned int, TT>::value ||
                                    std::is_same<unsigned long, TT>::value>::type* = nullptr>
  int isSumEqualsToDataSum(unsigned long sum);
  
  T deepestNodeBFS();

  protected:
  void preOrderRec(void (*process)(T), typename BinaryTree<T>::Node* node);

  private:
  //        T BinaryTreeRoot;
};

#endif  // BINARYTREELEVELORDERTRAVERSAL_H
