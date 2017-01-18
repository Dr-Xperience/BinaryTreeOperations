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
#ifndef BINARYTREEOPERATIONS_CPP
#define BINARYTREEOPERATIONS_CPP

#ifdef DEBUG
#include <iostream>
#endif  // DEBUG

#include <deque>
#include <queue>
#include <stack>

#include "BinaryTreeOperations.h"
#include "BinaryTree.h"
#include "BinaryTree.cpp"

template <class T>
BinaryTreeOperations<T>::BinaryTreeOperations()
    : BinaryTree<T>()
{
  // ctor
}

template <class T>
BinaryTreeOperations<T>::BinaryTreeOperations(T data)
    : BinaryTree<T>(data)
{
  // ctor
}

// Copy Constructor
template <class T>
BinaryTreeOperations<T>::BinaryTreeOperations(BinaryTreeOperations& b)
    : BinaryTree<T>(b)
{
  // ctor
}

template <class T>
BinaryTreeOperations<T>::~BinaryTreeOperations()
{
  // dtor
}

// Member functions
template <class T>
void BinaryTreeOperations<T>::traverseLevelOrder(void (*process)(T))
{
  if (this->root == nullptr)
    return;

  typedef typename BinaryTree<T>::Node Node;
  Node* node = this->root;

  std::queue<Node*> q;
  q.push(node);

#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG

  while (!q.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      node = q.front();
      q.pop();
      process(node->data);

      if (node->left != nullptr)
        {
          q.push(node->left);
        }

      if (node->right != nullptr)
        {
          q.push(node->right);
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Level Order Traversal loop count :: " << counter << std::endl;
#endif  // DEBUG
}

template <class T>
void BinaryTreeOperations<T>::printLevelOrder(void (*process)(T, bool newLine, bool leaveNode))
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG

  if (this->root == nullptr)
    return;

  typedef typename BinaryTree<T>::Node Node;
  Node* node = this->root;

  std::queue<Node*> q;

  Node* newLevel = new Node;
  newLevel->id = 0;

  q.push(node);
  q.push(newLevel);

  while (!q.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      node = q.front();
      q.pop();

      if (node == nullptr)
        {
          process(T(), false, true);
          continue;
        }
      else if (node->id == 0)
        {
          if (!q.empty())
            {
              process(T(), true, false);
              q.push(newLevel);
            }
          continue;
        }
      else
        process(node->data, false, false);

      q.push(node->left);

      q.push(node->right);
    }

#ifdef DEBUG
  std::cout << std::endl << "Level Order Traversal Print loop count :: " << counter << std::endl;
#endif  // DEBUG
}

template <class T>
void BinaryTreeOperations<T>::preOrderRec(void (*process)(T), typename BinaryTree<T>::Node* node)
{
  if (node == nullptr)
    return;
  process(node->data);
  preOrderRec(process, node->left);
  preOrderRec(process, node->right);
}

template <class T>
void BinaryTreeOperations<T>::recursionPreOrder(void (*process)(T))
{
  preOrderRec(process, this->root);
}

template <class T>
void BinaryTreeOperations<T>::traversePreOrderTraversal(void (*process)(T))
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG

  if (this->root == nullptr)
    return;

  typedef typename BinaryTree<T>::Node Node;
  Node* node = this->root;

  std::stack<Node*> s;
  s.push(node);

  while (!s.empty())
    {
      node = s.top();
      s.pop();
      for (; node != nullptr; node = node->left)
        {
#ifdef DEBUG
          counter++;
#endif  // DEBUG

          process(node->data);

          if (node->right != nullptr)
            s.push(node->right);
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Pre-Order Traversal loop count :: " << counter << std::endl;
#endif
}

template <class T>
void BinaryTreeOperations<T>::traversePostOrderTraversal(void (*process)(T))
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG

  if (this->root == nullptr)
    return;
  typedef typename BinaryTree<T>::Node Node;
  struct Snapshot
  {
    // formal argument of Member Function except the reference and pointers
    Node* node;
    // No memberFunctions Present
    unsigned long stage = 0;
  };

  // Creating manual function stack
  std::stack<Snapshot> s;

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;

  snapshot.node = this->root;
  snapshot.stage = 0;

  s.push(snapshot);

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              if (snapshot.node == nullptr)
                continue;

              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.stage = 0;
                  s.push(snapshot);
                }
              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;

              s.push(snapshot);

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              continue;
            }
          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              process(snapshot.node->data);
              continue;
            }
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Post Order Loop Count :: " << counter << std::endl;
#endif
}

template <class T>
long BinaryTreeOperations<T>::heightDFS()
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG
        /*
         heightDFS(node)
         {
           if(node==null)
            return -1;
      
            l=height(node->left);
            r=height(node->right);
      
            if(l>r)
              return(l+1);
            else
               return(r+1);
         }
        */
  if (this->root == nullptr)
    return -1;

  typedef typename BinaryTree<T>::Node Node;

  struct Snapshot
  {
    // Formal Arguments of function except the reference and pointers
    Node* node;
    // Local Variables
    long leftHeight = -1, rightHeight = -1;
    // stage
    unsigned long stage = 0;
  };

  // function formal arguments/parameters present as references or pointer
  // plus returnVal as return value of the algorithm/function
  long returnVal = -1;  // Default Return Value

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;

  snapshot.node = this->root;
  snapshot.leftHeight = snapshot.rightHeight = -1;
  snapshot.stage = 0;

  // Creating manual function stack
  std::stack<Snapshot> s;

  // simulating function call by pushing the snapshot to s
  s.push(snapshot);

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              if (snapshot.node == nullptr)
                {
                  returnVal = -1;
                  continue;
                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.leftHeight = snapshot.rightHeight = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.leftHeight = returnVal;

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;
              s.push(snapshot);

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.leftHeight = snapshot.rightHeight = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.rightHeight = returnVal;

              if (snapshot.leftHeight > snapshot.rightHeight)
                returnVal = snapshot.leftHeight + 1;
              else
                returnVal = snapshot.rightHeight + 1;
              continue;
            }
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Loop Count of Height of Tree(DFS) :: " << counter << std::endl;
#endif  // DEBUG
  return returnVal;
}

template <class T>
long BinaryTreeOperations<T>::heightBFS()
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG

  if (this->root == nullptr)
    return -1;

  typedef typename BinaryTree<T>::Node Node;
  Node* node = this->root;

  std::queue<Node*> q;

  q.push(node);
  q.push(nullptr);
  long height = 0;

  while (!q.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      node = q.front();
      q.pop();

      if (node == nullptr)
        {
          if (q.empty() == false)
            {
              height++;
              q.push(nullptr);
            }
          continue;
        }

      if (node->left != nullptr)
        q.push(node->left);

      if (node->right != nullptr)
        q.push(node->right);
    }

#ifdef DEBUG
  std::cout << std::endl << "Loop Count of Height of Tree(BFS) :: " << counter << std::endl;
#endif  // DEBUG

  return height;
}

static long Max(long x, long y)
{
  return (x ^ ((x ^ y) & -(x < y)));
}

// diameter with O(N*N) or O(N^2) complexity
template <class T>
long BinaryTreeOperations<T>::diameterN2()
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG
  /**
  //How does diameter algo work
  //
  //Diameter for a node is calculated by
  //getting height of left subtree + right subtree + 2
  // 2 because we need to add left edge and right edge of current node to height as well.
  //
  //This is because like height, diameter is count of edges,
  //We add two to the height of left subtree and right subtree
  //because, we have two edges connecting left subtree and right subtree respectively
  //to form a diameter.
  //
  //Now to get the diameter of the subtree
  //we compare the diameter of node with diameter of left subtree and right subtree
  //which ever is maximum becomes the diameter of subtree
  //
  //We just repeat the same step for every node/subtree
  long diameter(node)
  {
      if(node == null)
          return -1;

      long leftHeight=heightDFS(node->left);
      long rightHeight=heightDFS(node->right);

      long leftDiameter=diameter(node->left);
      long rightDiameter=diameter(node->right);

      return MAX(leftHeight+rightHeight+2,Max(leftDiameter,rightDiameter));
  }
  */

  if (this->root == nullptr)
    return -1;

  typedef typename BinaryTree<T>::Node Node;

  struct Snapshot
  {
    // Formal parameters except the reference and pointers
    Node* node;
    // local variable
    long leftHeight = -1, rightHeight = -1, leftDiameter = -1, rightDiameter = -1;
    // stage
    unsigned long stage = 0;
  };

  // function formal arguments/parameters present as references or pointer
  // plus returnVal as return value of the algorithm/function
  long returnVal = -1;

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;

  snapshot.node = this->root;
  snapshot.leftHeight = snapshot.rightHeight = snapshot.leftDiameter = snapshot.rightDiameter = -1;
  snapshot.stage = 0;

  // Creating manual function stack
  std::stack<Snapshot> s;

  // simulating function call by pushing the snapshot to s
  s.push(snapshot);

  Node* temp = this->root;

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              if (snapshot.node == nullptr)
                {
                  returnVal = -1;
                  continue;
                }

              this->root = snapshot.node->left;
              snapshot.leftHeight = this->heightDFS();
              this->root = snapshot.node->right;
              snapshot.rightHeight = this->heightDFS();

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.leftHeight = snapshot.rightHeight = snapshot.leftDiameter = snapshot.rightDiameter = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.leftDiameter = returnVal;

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;

              s.push(snapshot);

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.leftHeight = snapshot.rightHeight = snapshot.leftDiameter = snapshot.rightDiameter = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.rightDiameter = returnVal;

              returnVal = Max(snapshot.leftHeight + snapshot.rightHeight + 2, Max(snapshot.leftDiameter, snapshot.rightDiameter));
              continue;
            }
        }
    }

  this->root = temp;
#ifdef DEBUG
  std::cout << "\nNumber of Loops for diameter :: " << counter << std::endl;
#endif  // DEBUG

  return returnVal;
}

// Method to return diameter of tree in O(N) complexity
template <class T>
long BinaryTreeOperations<T>::diameter()
{
#ifdef DEBUG
  long counter = 0;
#endif  // DEBUG
        /**
          // calculate diameter along with height this will give us algorithm with complexity O(N)
      
          // conventional height algorithm
          long height(Node * node)
          {
            if(node == nullptr)
                return -1;
      
            long heightLeft = height(node->left);
            long heightRight = height(node->right);
      
            return (Max(heightLeft,heightRight)+1);
          }
      
        // Process of converting height algo to diameter
        // having complexity as O(N)
      
        // As mentioned earlier in diameterN2
        // Diameter of a node is height of left subtree + right subtree + 2
        // (Two because there are two edges connecting the left and right subtree)
      
        // so we can use this in our current height algorithm
      
          long height(Node * node)
          {
            if(node == nullptr)
                return -1;
      
            long heightLeft = height(node->left);
            long heightRight = height(node->right);
      
        // Like height, diameter is count of edges,
        // We add two to the height of left subtree and right subtree,
        // because we have two edges connecting left subtree and right subtree
        // to form a diameter.
      
            diameterNode = heightLeft + heightRight + 1 + 1;
      
        // Here comes the actual problem,
        // we need to get diameter of left subtree and right subtree as well
        // we can solve it by passing a pointer(reference in case of c++)
        // to the height method, which will store the diameter
      
           long height(Node *node, long *diameter) //in explanation I am implementing using pointer
           {                                      //but in actual code it will be reference
      
            if(node == nullptr)
                return -1;
      
            long diameterLeft = 0, diameterRight = 0;
      
            long heightLeft = height(node->left, &diameterLeft);
            long heightRight = height(node->right, &diameterRight);
      
            long diameterNode = heightLeft + heightRight + 2;
      
            *diameter = Max(diameterNode,Max(diameterLeft,diameterRight));
      
            return Max(heightLeft, heightRight)+1;
           }
      
         // We can make it a more optimized (space optimized)
         // (The algo from narasimha karumanchi's book
      
             long height(Node * node, long *diameter)
             {
                if(node == nullptr)
                  return -1;
      
                heightLeft = height(node->left, diameter);
                heightRight = height(node->right, diameter);
      
                // Note: Till this point the diameter variable contains
                // the max of diameter of left and right subtree
      
                // We cleverly gets that by passing same pointer
                // while calculating the height of left subtree
                // and right subtree
      
                if(heightLeft+heightRight+1 > *diameter)
                  *diameter = heightLeft + heightRight + 2;
      
                       //OR
                       // *diameter = Max(heightLeft+heightRight+2,*diameter);
      
                // So, the above comparison while in right subtree
                // will compare current diameter with the one
                // we got from left subtree
      
                // Hence, after getting height from left and right subtree
                // The pointer diameter will contain
                // diameter of either left or right subtree which ever is max
      
                // Then, we just compare the diameter of currentNode with obtained diameter
                // Whichever is Max becomes the diameter of current subtree
      
                // Finally, like regular height algorithm we return the height + 1
                return Max(heightLeft,heightRight) + 1;
             }
      
             The diameter will called as:
             int diameterV = -1;
             diameter(node,&diameterV);
        **/

  if (this->root == nullptr)
    return -1;
  typedef typename BinaryTree<T>::Node Node;

  struct Snapshot
  {
    // Formal parameters except the reference and pointers
    Node* node;
    // No need to make data member for diameter
    // because it is a reference
    //(remember I said
    // I will use diameter as reference in implementation

    // local variable
    long heightLeft = -1, heightRight = -1;

    // stages
    unsigned long stage = 0;
  };

  // function formal arguments/parameters present as references or pointer
  // plus returnVal as return value of the algorithm/function
  long returnVal = -1;
  long diameter = -1;

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;
  snapshot.node = this->root;
  snapshot.heightLeft = snapshot.heightRight = -1;
  snapshot.stage = 0;

  // Creating manual function stack
  std::stack<Snapshot> s;

  // simulating function call by pushing the snapshot to s
  s.push(snapshot);

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case (0):
            {
              if (snapshot.node == nullptr)
                {
                  returnVal = -1;
                  continue;
                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.heightLeft = snapshot.heightRight = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case (1):
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.heightLeft = returnVal;

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;

              s.push(snapshot);

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.heightLeft = snapshot.heightRight = -1;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              else
                returnVal = -1;

              continue;
            }

          case (2):
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              snapshot.heightRight = returnVal;

              diameter = Max(snapshot.heightLeft + snapshot.heightRight + 2, diameter);

              returnVal = Max(snapshot.heightLeft, snapshot.heightRight) + 1;

              continue;
            }
        }
    }

#ifdef DEBUG
  std::cout << "\nNumber of Loops for diameter :: " << counter << std::endl;
#endif  // DEBUG

  // since we want to return diameter as result
  // we will replace returnVal with diameter
  // return returnVal;
  return diameter;
}

// Method to return list containing nodes in diameter of tree
template <class T>
std::deque<unsigned long> BinaryTreeOperations<T>::diameterPrint()
{
/**

std::deque<unsigned long> diameterPrint(Node * node, long &height, long &diameter, deque<unsigned long> &diameterList)
{
    if(node == nullptr)
        return std::deque<unsigned long>();

    long heightLeft = -1, heightRight = -1;

    std::deque<unsigned long> subtreeLeft, subtreeRight;

    if(node->left != nullptr)
    {
        subtreeLeft = diameterPrint(node->left,heightLeft,diameter,diameterList);
    }

    if(node->right != nullptr)
    {
        subtreeRight = diameterPrint(node->right,heightRight,diameter,diameterRight);
    }

    if(heightLeft+heightRight+2 > diameter)
    {
        diameter = heightLeft + heightRight + 2;
        diameterList.clear();
        diameterList.insert(diameterList.end(),subtreeLeft.begin(),subtreeLeft.end());
        diameterList.push_back(node->id);
        diameterList.insert(diameterList.end(),subtreeRight,rbegin(),subtreeRight.rend());
    }

    if(heightLeft>heightRight)
    {
        height = heightLeft+1;
        subtreeLeft.push_back(node->id);
        return subtreeLeft;
    }
    else
    {
        height = heightRight + 1;
        subtreeRight.push_back(node->id);
        return subtreeRight;
    }
}
**/

#ifdef DEBUG
  unsigned long counter = 0;
#endif  // DEBUG

  if (this->root == nullptr)
    {
      return std::deque<unsigned long>();
    }

  typedef typename BinaryTree<T>::Node Node;

  struct Snapshot
  {
    // input parameters except the reference and pointers
    Node* node;

    // local variables
    long heightLeft = -1, heightRight = -1;
    std::deque<unsigned long> subtreeLeft, subtreeRight;

    // stage
    unsigned long stage = 0;
  };

  // function formal arguments/parameters present as references or pointer
  // plus returnVal as return value of the algorithm/function
  long height = -1, diameter = -1;
  std::deque<unsigned long> diameterList, returnVal;

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;

  snapshot.node = this->root;
  // the stage is by default set to 0

  // Creating manual function stack
  std::stack<Snapshot> s;

  // simulating function call by pushing the snapshot to s
  s.push(snapshot);

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              //                if(snapshot.node->left == nullptr && snapshot.node->right == nullptr)
              //                {
              //                    height = 0;
              //                    diameter = 0;
              //                    diameterList.push_back(snapshot.node->id);
              //                    snapshot.subtreeLeft.push_back(snapshot.node->id);
              //                    snapshot.subtreeRight.push_back(snapshot.node->id);
              //                    returnVal = snapshot.subtreeLeft;
              //                    continue;
              //                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.heightLeft = snapshot.heightRight = -1;
                  snapshot.subtreeLeft.clear();
                  snapshot.subtreeRight.clear();
                  snapshot.stage = 0;

                  s.push(snapshot);
                }

              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              if (snapshot.node->left != nullptr)
                {
                  // in this case snapshot.heightRight was passed as reference during function call in algorithm
                  // this will get its value from height which is formal parameter created as reference
                  snapshot.heightLeft = height;
                  snapshot.subtreeLeft = returnVal;
                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;

              s.push(snapshot);

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.heightLeft = snapshot.heightRight = -1;
                  snapshot.subtreeLeft.clear();
                  snapshot.subtreeRight.clear();
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              continue;
            }

          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              if (snapshot.node->right != nullptr)
                {
                  // in this case snapshot.heightRight was passed as reference during function call in algorithm
                  // this will get its value from height which is formal parameter created as reference
                  snapshot.heightRight = height;
                  snapshot.subtreeRight = returnVal;
                }

              if (snapshot.heightLeft + snapshot.heightRight + 2 > diameter)
                {
                  diameter = snapshot.heightLeft + snapshot.heightRight + 2;
                  diameterList.clear();
                  diameterList.insert(diameterList.end(), snapshot.subtreeLeft.begin(), snapshot.subtreeLeft.end());
                  diameterList.push_back(snapshot.node->id);
                  diameterList.insert(diameterList.end(), snapshot.subtreeRight.rbegin(), snapshot.subtreeRight.rend());
                }

              if (snapshot.heightLeft > snapshot.heightRight)
                {
                  height = snapshot.heightLeft + 1;
                  snapshot.subtreeLeft.push_back(snapshot.node->id);
                  returnVal = snapshot.subtreeLeft;
                }
              else
                {
                  height = snapshot.heightRight + 1;
                  snapshot.subtreeRight.push_back(snapshot.node->id);
                  returnVal = snapshot.subtreeRight;
                }

              continue;
            }
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Number of Loops to print diameter :: " << counter << std::endl;
#endif  // DEBUG

  // since we want to return diameterList as result
  // we will replace returnVal with diameterList
  // return returnVal;
  return diameterList;
}

// Method to print all the paths from root to leaves
template <class T>
void BinaryTreeOperations<T>::pathToLeavesPrint(void (*process)(std::deque<unsigned long>&))
{
  /**

  void pathPrint(Node* node, std::deque<unsigned long>& list)
  {
      if(node == nullptr)
          return;

      list.push_back(node->id);

      if(node->left==nullptr && node->right==nullptr)
      {
          print(list);
          return;
      }

      std::deque<unsigned long>::iterator itr;

      itr = list.end();
      itr--; //to move iterator from _M_Node to the last Node
             //check gcc code ("C:\Home\Dr.Xperience\INNOVATE\dissertation\Progs\gcc source+ modified source+compile
  commands\libstdc++-v3\include\bits\stl_list.h")
             //"C:\Home\Dr.Xperience\INNOVATE\dissertation\Progs\gcc source+ modified source+compile commands\libstdc++-v3\src\c++98\list.cc"

      if(node->left != nullptr)
      {
          pathPrint(node->left,list);

          //now move itr to next node after current
          itr++;
          itr = list.erase(itr,list.end()); //erase all nodes after current

          //Now itr = last.end() i.e _M_Node
          //We need to move it back to last element
          itr--;
      }

      if(node->right != nullptr)
      {
          pathPrint(node->right,list);
          itr++;
          itr = list.erase(itr,list.end());
          itr--;
      }
  }//end of function
  **/
  if (this->root == nullptr)
    return;

#ifdef DEBUG
  unsigned long counter = 0;
#endif  // DEBUG

  typedef typename BinaryTree<T>::Node Node;

  struct Snapshot
  {
    // input parameters except the reference and pointers
    Node* node;

    // local variable
    std::deque<unsigned long>::iterator itr;

    // stage
    unsigned long stage = 0;
  };

  // function formal arguments/parameters present as references or pointer
  // plus returnVal as return value of the algorithm/function
  std::deque<unsigned long> list;

  // Creating function call by passing actual argument to formal arguments present in the snapshot
  // and setting stage to 0
  Snapshot snapshot;

  snapshot.node = this->root;

  // Creating manual function stack
  std::stack<Snapshot> s;

  // simulating function call by pushing the snapshot to s
  s.push(snapshot);

  while (!s.empty())
    {
#ifdef DEBUG
      counter++;
#endif  // DEBUG

      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              list.push_back(snapshot.node->id);
              if (snapshot.node->left == nullptr && snapshot.node->right == nullptr)
                {
                  process(list);
                  continue;
                }

              snapshot.itr = list.end();
              snapshot.itr--;

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  snapshot.itr = list.end();
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              if (snapshot.node->left != nullptr)
                {
                  snapshot.itr++;  // increment to point to next element
                  snapshot.itr = list.erase(snapshot.itr, list.end());
                  snapshot.itr--;  // decrement to point to the current element

                  // updating the status of local variable if any
                  // and pushing the snapshot to stage 2
                  // i.e. code to be called after function returns from its first call
                  snapshot.stage = 2;

                  s.push(snapshot);
                }

              if (snapshot.node->right != nullptr)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  snapshot.itr = list.end();
                  snapshot.stage = 0;
                  s.push(snapshot);
                }
              continue;
            }

          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer
              if (snapshot.node->right != nullptr)
                {
                  snapshot.itr++;
                  snapshot.itr = list.erase(snapshot.itr, list.end());
                }
              continue;
            }
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Number of Loops to print paths :: " << counter << std::endl;
#endif  // DEBUG
}

template <class T>
template <typename TT, typename std::enable_if<!(std::is_same<float, TT>::value || std::is_same<double, TT>::value ||
                                                 std::is_same<unsigned int, TT>::value || std::is_same<unsigned long, TT>::value)>::type* a>
int BinaryTreeOperations<T>::isSumEqualsToDataSum(unsigned long sum)
{
  return -1;
}

// Function to check whether sum of node->data values in a path from root to any node in a tree equals a given value
template <class T>
template <typename TT, typename std::enable_if<std::is_same<float, TT>::value || std::is_same<double, TT>::value ||
                                               std::is_same<unsigned int, TT>::value || std::is_same<unsigned long, TT>::value>::type* a>
int BinaryTreeOperations<T>::isSumEqualsToDataSum(unsigned long sum)
{
  /**
  //Algorithm

  int isSumEqualsToDataSum(Node* node, unsigned long sum)
  {
      if(node == nullptr)
          return -1;
      sum = sum - (node->data);

      if(node->left == nullptr && node->right == nullptr)
      {
          return (sum == 0);
      }

      if(node->left != nullptr && sum > 0)
      {
          if(isSumEqualsToDataSum(node->left,sum) == 1)
              return 1;
      }

      if(node->right != nullptr && sum > 0)
      {
          if(isSumEqualsToDataSum(node->right,sum) == 1)
              return 1;
      }

      return (sum == 0) 1 : 0;

      //Alternate if the object to check whether the path from root to leave is equal to sum
      //rather than root to any node
      //then, change return from "return (sum == 0) 1 : 0;" to "return 0;"

  }
  **/

  /**

  //Test cases

  1. Given Tree : nullptr

      a.      Input : sum = anything
              Output : -1

  2.  Given Tree : "1#2@3#4@5@6@7#", Where @ mean new node and # end of level and 1,2,3 are non numeric literals

      a.      Input : sum = anything
              Output : -1

  3.  Given Tree : "1#2@3#4@5@6@7#", Where @ mean new node and # end of level and 1,2,3 are numeric literals

      a.      Input : sum = 0
              Output : 0

      b.      Input : sum = 2
              Output : 0

      c.      Input : sum = 3
              Output : 1

      d.      Input : sum = 7
              Output : 1

      e.      Input : sum = 8
              Output : 8

  4.  Given Tree : "1#", Where @ mean new node and # end of level and 1,2,3 are numeric literals

      a.      Input : sum = 1
              Output : 1

      b.      Input : sum = 8
              Output : 0

  **/
  if (this->root == nullptr)
    return -1;

#ifdef DEBUG
  unsigned long counter = 0;
#endif  // DEBUG

  typedef typename BinaryTree<T>::Node Node;
  struct Snapshot
  {
    // formal parameters except any reference or pointer arguments
    Node* node;
    unsigned long sum;

    // local variables in function
    // none for this algo

    // stage of algorithm
    unsigned long stage = 0;
  };

  // references or pointers in formal parameters of function if any
  // none in this case

  // return value of function as returnVal initialized with default return value
  int returnVal = 0;

  // Creating manual function stack
  std::stack<Snapshot> s;

  // Creating function call i.e isSumEqualsToDataSum(node,5);
  // by passing actual argument to formal arguments present in the snapshot
  Snapshot snapshot;
  snapshot.node = this->root;
  snapshot.sum = sum;

  // stage is by default set to 0 so no need to set it to zero

  s.push(snapshot);

  while (!s.empty())
    {
      snapshot = s.top();
      s.pop();

      switch (snapshot.stage)
        {
          case 0:
            {
              snapshot.sum = snapshot.sum - (snapshot.node->data);

              if (snapshot.node->left == nullptr && snapshot.node->right == nullptr)
                {
                  returnVal = (snapshot.sum == 0) ? 1 : 0;
                  continue;
                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 1
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 1;

              s.push(snapshot);

              if (snapshot.node->left != nullptr && snapshot.sum > 0)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->left;
                  // snapshot.sum = snapshot.sum;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }

              continue;
            }

          case 1:
            {
              // in stage 1 variable returnVal holds the return value
              // from the function call creation made after setting stage=1 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer

              if (snapshot.node->left != nullptr && snapshot.sum > 0)
                {
                  if (returnVal == 1)
                    {
                      returnVal = 1;
                      continue;
                    }
                }

              // updating the status of local variable if any
              // and pushing the snapshot to stage 2
              // i.e. code to be called after function returns from its first call
              snapshot.stage = 2;

              s.push(snapshot);

              if (snapshot.node->right != nullptr && snapshot.sum > 0)
                {
                  // Creating function call by passing actual argument to formal arguments
                  // and setting stage to 0
                  snapshot.node = snapshot.node->right;
                  // snapshot.sum = snapshot.sum;
                  snapshot.stage = 0;

                  s.push(snapshot);
                }
              continue;
            }

          case 2:
            {
              // in stage 2 variable returnVal holds the return value
              // from the function call creation made after setting stage=2 and s.push(snapshot)
              // and any local variable in snapshot passed by reference/pointer during function call
              // will receive value from formal parameters created as reference/pointer

              if (snapshot.node->right != nullptr && snapshot.sum > 0)
                {
                  if (returnVal == 1)
                    {
                      returnVal = 1;
                      continue;
                    }
                }

              returnVal = (snapshot.sum == 0) ? 1 : 0;
              continue;

              // Alternate if the object to check whether the path from root to leave is equal to sum
              // rather than root to any node
              // then, change returnVal from "returnVal = (sum == 0) 1 : 0;" to "returnVal= 0;"
            }
        }
    }

#ifdef DEBUG
  std::cout << std::endl << "Number of Loops to check Sum of path :: " << counter << std::endl;
#endif  // DEBUG

  return returnVal;
}

template <class T>
T BinaryTreeOperations<T>::deepestNodeBFS()
{
  if (this->root == nullptr)
    return T();  // throw some exception

  typedef typename BinaryTree<T>::Node Node;

  Node* node = this->root;

  std::queue<Node*> q;
  q.push(node);

  while (!q.empty())
    {
      node = q.front();
      q.pop();

      if (node->left != nullptr)
        {
          q.push(node->left);
        }

      if (node->right != nullptr)
        {
          q.push(node->right);
        }
    }
  return node->data;
}

#endif
