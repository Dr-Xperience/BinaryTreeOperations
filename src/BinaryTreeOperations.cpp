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
#include<iostream>
#endif // DEBUG

#include <list>
#include<queue>
#include<stack>

#include "BinaryTreeOperations.h"
#include "BinaryTree.h"
#include "BinaryTree.cpp"


template<class T>
BinaryTreeOperations<T>::BinaryTreeOperations():BinaryTree<T>()
{
    //ctor
}

template<class T>
BinaryTreeOperations<T>::BinaryTreeOperations(T data):BinaryTree<T>(data)
{
    //ctor
}

//Copy Constructor
template<class T>
BinaryTreeOperations<T>::BinaryTreeOperations(BinaryTreeOperations& b):BinaryTree<T>(b)
{
    //ctor
}

template<class T>
BinaryTreeOperations<T>::~BinaryTreeOperations()
{
    //dtor
}

//Member functions
template<class T>
void BinaryTreeOperations<T>::traverseLevelOrder(void (*process)(T))
{
    if(this->root == nullptr)
        return;

    typedef typename BinaryTree<T>::Node Node;
    Node* root = this->root;

    std::queue<Node*> q;
    q.push(root);

    #ifdef DEBUG
    long counter = 0;
    #endif // DEBUG

    while(!q.empty())
    {
        #ifdef DEBUG
        counter ++;
        #endif // DEBUG

        root=q.front();q.pop();
        process(root->data);

        if(root->left != nullptr)
        {
            q.push(root->left);
        }

        if(root->right != nullptr)
        {
            q.push(root->right);
        }
    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Level Order Traversal loop count :: "<<counter<<std::endl;
    #endif // DEBUG
}


template<class T>
void BinaryTreeOperations<T>::printLevelOrder(void (*process)(T,bool newLine, bool leaveNode))
{
    #ifdef DEBUG
    long counter = 0;
    #endif // DEBUG

    if(this->root == nullptr)
        return;

    typedef typename BinaryTree<T>::Node Node;
    Node* root=this->root;

    std::queue<Node*> q;

    Node* newLevel = new Node;
    newLevel->id = 0;

    q.push(root);
    q.push(newLevel);

    while(!q.empty())
    {
    #ifdef DEBUG
    counter++;
    #endif // DEBUG

        root= q.front(); q.pop();

        if(root == nullptr)
        {
             process(T(),false,true);
             continue;
        }
        else if(root->id == 0)
        {
            if(!q.empty())
            {
                process(T(),true,false);
                q.push(newLevel);
            }
            continue;
        }
        else
          process(root->data,false,false);


       q.push(root->left);

       q.push(root->right);
    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Level Order Traversal Print loop count :: "<<counter<<std::endl;
    #endif // DEBUG

}

template<class T>
void BinaryTreeOperations<T>::preOrderRec(void (*process)(T),typename BinaryTree<T>::Node * root)
{
    if(root == nullptr)
        return;
    process(root->data);
    preOrderRec(process,root->left);
    preOrderRec(process,root->right);
}

template<class T>
void BinaryTreeOperations<T>::recursionPreOrder(void (*process)(T))
{
    preOrderRec(process,this->root);
}

template<class T>
void BinaryTreeOperations<T>::traversePreOrderTraversal(void (*process)(T))
{
    #ifdef DEBUG
    long counter=0;
    #endif // DEBUG

    if(this->root == nullptr)
        return;

    typedef typename BinaryTree<T>::Node Node;
    Node * root = this->root;

    std::stack<Node*> s;
    s.push(root);

    while(!s.empty())
    {
        root= s.top(); s.pop();
        for(;root != nullptr;root=root->left)
        {
            #ifdef DEBUG
            counter++;
            #endif // DEBUG

            process(root->data);

            if(root->right != nullptr)
                s.push(root->right);
        }
    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Pre-Order Traversal loop count :: "<<counter<<std::endl;
    #endif
}

template<class T>
void BinaryTreeOperations<T>::traversePostOrderTraversal(void (*process)(T))
{
    #ifdef DEBUG
    long counter =0;
    #endif //DEBUG

    if(this->root == nullptr)
        return;
    typedef typename BinaryTree<T>::Node Node;
    struct Snapshot
    {
        Node* root; //argument of Member Function
        //No memberFunctions Present
        unsigned long stage=0;
    };

    std::stack<Snapshot> s;

    Snapshot snapshot;

    snapshot.root=this->root;
    snapshot.stage=0;

    s.push(snapshot);

    while(!s.empty())
    {
        #ifdef DEBUG
        counter++;
        #endif // DEBUG

        snapshot = s.top(); s.pop();

        switch(snapshot.stage)
        {
            case 0:
            {
                if(snapshot.root == nullptr)
                    continue;

                snapshot.stage=1;
                s.push(snapshot);

                if(snapshot.root->left != nullptr)
                {
                    snapshot.root=snapshot.root->left;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                continue;
            }

            case 1:
            {
                snapshot.stage=2;
                s.push(snapshot);

                if(snapshot.root->right != nullptr)
                {
                    snapshot.root=snapshot.root->right;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                continue;
            }
            case 2:
            {
                process(snapshot.root->data);
                continue;
            }

        }

    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Post Order Loop Count :: "<<counter<<std::endl;
    #endif

}

template<class T>
long BinaryTreeOperations<T>::heightDFS()
{
    #ifdef DEBUG
    long counter =0;
    #endif // DEBUG
/*
 heightDFS(root)
 {
   if(root==null)
    return -1;

    l=height(root->left);
    r=height(root->right);

    if(l>r)
      return(l+1);
    else
       return(r+1);
 }
*/
    if(this->root == nullptr)
        return -1;

    typedef typename BinaryTree<T>::Node Node;

    struct Snapshot
    {
        //Arguments to function
        Node* root;
        //Local Variables
        long leftHeight = -1 , rightHeight = -1;
        //stage
        unsigned long stage = 0;
    };

    long returnVal = -1; //Default Return Value

    Snapshot snapshot;

    snapshot.root = this->root;
    snapshot.leftHeight=snapshot.rightHeight=-1;
    snapshot.stage=0;

    std::stack<Snapshot>s;
    s.push(snapshot);

    while(!s.empty())
    {
        #ifdef DEBUG
        counter++;
        #endif // DEBUG

        snapshot=s.top(); s.pop();

        switch(snapshot.stage)
        {
            case 0:
            {
                if(snapshot.root==nullptr)
                {
                    returnVal=-1;
                    continue;
                }

                snapshot.stage=1;
                s.push(snapshot);

                if(snapshot.root->left != nullptr)
                {
                    snapshot.root= snapshot.root->left;
                    snapshot.leftHeight=snapshot.rightHeight=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case 1:
            {
                snapshot.leftHeight = returnVal;
                snapshot.stage=2;
                s.push(snapshot);

                if(snapshot.root->right != nullptr)
                {
                    snapshot.root = snapshot.root->right;
                    snapshot.leftHeight=snapshot.rightHeight=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case 2:
            {
                snapshot.rightHeight=returnVal;

                if(snapshot.leftHeight>snapshot.rightHeight)
                    returnVal=snapshot.leftHeight+1;
                else
                    returnVal=snapshot.rightHeight+1;
                continue;
            }

        }

    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Loop Count of Height of Tree(DFS) :: "<<counter<<std::endl;
    #endif // DEBUG
    return returnVal;
}

template<class T>
long BinaryTreeOperations<T>::heightBFS()
{
    #ifdef DEBUG
    long counter =0;
    #endif // DEBUG

    if(this->root == nullptr)
        return -1;

    typedef typename BinaryTree<T>::Node Node;
    Node *root = this->root;

    std::queue<Node*> q;

    q.push(root);
    q.push(nullptr);
    long height = 0;

    while(!q.empty())
    {
        #ifdef DEBUG
        counter ++;
        #endif // DEBUG

        root = q.front(); q.pop();

        if(root == nullptr )
        {
            if(q.empty() == false)
            {
                height++;
                q.push(nullptr);
            }
            continue;
        }

        if(root->left != nullptr)
            q.push(root->left);

        if(root->right != nullptr)
            q.push(root->right);
    }

    #ifdef DEBUG
    std::cout<<std::endl<<"Loop Count of Height of Tree(BFS) :: "<<counter<<std::endl;
    #endif // DEBUG

    return height;
}

static long Max(long x, long y)
{
    return(x^((x^y)&-(x<y)));
}

//diameter with O(N*N) or O(N^2) complexity
template <class T>
long BinaryTreeOperations<T>::diameterN2()
{
    #ifdef DEBUG
    long counter = 0;
    #endif // DEBUG
    /**
    //How does diameter algo work
    //
    //Diameter for a node is calculated by
    //getting height of left subtree + right subtree + 1
    // 1 because we need to add current edge to height as well.
    //
    //Now to get the diameter of the subtree
    //we compare the diameter of node with diameter of left subtree and right subtree
    //which ever is maximum becomes the diameter of subtree
    //
    //We just repeat the same step for every node/subtree
    long diameter(root)
    {
        if(root == null)
            return 0;

        long leftHeight=heightDFS(root->left);
        long rightHeight=heightDFS(root->right);

        long leftDiameter=diameter(root->left);
        long rightDiameter=diameter(root->right);

        return MAX(leftHeight+rightHeight+1,Max(leftDiameter,rightDiameter));
    }
    */

    if(this->root == nullptr)
        return -1;

    typedef typename BinaryTree<T>::Node Node;

    struct Snapshot
    {
        //function argument
        Node* root;
        //local variable
        long leftHeight = -1, rightHeight = -1,leftDiameter = -1,rightDiameter = -1;
        //stage
        unsigned long stage=0;
    };

    long returnVal=-1;

    Snapshot snapshot;

    snapshot.root = this->root;
    snapshot.leftHeight=snapshot.rightHeight=snapshot.leftDiameter=snapshot.rightDiameter=-1;
    snapshot.stage=0;

    std::stack<Snapshot> s;

    s.push(snapshot);
    Node* temp = this->root;
    while(!s.empty())
    {
        #ifdef DEBUG
        counter++;
        #endif // DEBUG

        snapshot = s.top(); s.pop();

        switch(snapshot.stage)
        {
            case 0:
            {
                if(snapshot.root == nullptr)
                {
                    returnVal=-1;
                    continue;
                }

                this->root=snapshot.root->left;
                snapshot.leftHeight = this->heightDFS();
                this->root=snapshot.root->right;
                snapshot.rightHeight = this->heightDFS();

                snapshot.stage=1;
                s.push(snapshot);

                if(snapshot.root->left != nullptr)
                {
                    snapshot.root = snapshot.root->left;
                    snapshot.leftHeight=snapshot.rightHeight=snapshot.leftDiameter=snapshot.rightDiameter=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case 1:
            {
                snapshot.leftDiameter=returnVal;
                snapshot.stage=2;
                s.push(snapshot);

                if(snapshot.root->right != nullptr)
                {
                    snapshot.root = snapshot.root->right;
                    snapshot.leftHeight=snapshot.rightHeight=snapshot.leftDiameter=snapshot.rightDiameter=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case 2:
            {
                snapshot.rightDiameter=returnVal;
//                 #ifdef DEBUG
//                    std::cout<<"\n snapshot.leftHeight = "<<snapshot.leftHeight<<std::endl;
//                    std::cout<<"\n snapshot.rightHeight = "<<snapshot.rightHeight<<std::endl;
//                 #endif // DEBUG
                returnVal = Max(snapshot.leftHeight+snapshot.rightHeight+1,Max(snapshot.leftDiameter,snapshot.rightDiameter));
                continue;
            }

        }
    }

    this->root=temp;
    #ifdef DEBUG
    std::cout<<"\nNumber of Loops for diameter :: "<<counter<<std::endl;
    #endif // DEBUG

    return returnVal;
}


template <class T>
long BinaryTreeOperations<T>::diameter()
{
    #ifdef DEBUG
    long counter=0;
    #endif // DEBUG
    /**
      // calculate diameter along with height this will give us algorithm with complexity O(N)

      // conventional height algorithm
      long height(Node * root)
      {
        if(root == nullptr)
            return -1;

        long heightLeft = height(root->left);
        long heightRight = height(root->right);

        return (Max(heightLeft,heightRight)+1);
      }

    // Process of converting height algo to diameter
    // having complexity as O(N)

    // As mentioned earlier in diameterN2
    // Diameter of a node is height of left subtree + right subtree + 1

    // so we can use this in our current height algorithm

      long height(Node * root)
      {
        if(root == nullptr)
            return -1;

        long heightLeft = height(root->left);
        long heightRight = height(root->right);

        diamterNode = heightLeft + heightRight + 1;

    // Here comes the actual problem,
    // we need to get diameter of left subtree and right subtree as well
    // we can solve it by passing a pointer(reference in case of c++)
    // to the height method, which will store the diameter

       long height(Node *root, long *diameter) //in explanation I am implementing using pointer
       {                                      //but in actual code it will be reference

        if(root == nullptr)
            return -1;

        long diameterLeft = diameterRight = 0;

        long heightLeft = height(root->left, &diameterLeft);
        long heightRight = height(root->right, &diameterRight);

        diameterNode = heightLeft + heightRight + 1;

        *diameter = Max(diameterNode,Max(diameterLeft,diameterRight));

        return Max(heightLeft, heightRight)+1;
       }

     // We can make it a more optimized (space optimized)
     // (The algo from narasimha karumanchi's book

         long height(Node * root, long *diameter)
         {
            if(root == nullptr)
              return -1;

            heightLeft = height(root->left, diameter);
            heightRight = height(root->right, diameter);

            // Note: Till this point the diameter variable contains
            // the max of diameter of left and right subtree

            // We cleverly gets that by passing same pointer
            // while calculating the height of left subtree
            // and right subtree

            if(heightLeft+heightRight+1 > *diameter)
              *diameter = heightLeft + heightRight + 1;

                   //OR
                   //*diameter = Max(heightLeft+heightRight+1,*diameter);

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
         diameter(root,&diameterV);
    **/

    if(this->root == nullptr)
        return -1;
    typedef typename BinaryTree<T>::Node Node;

    struct Snapshot
    {
        //input parameters
        Node * root;
        //No need to make data member for diameter
        //because it is a reference
        //(remember I said
        //I will use diameter as reference in implementation

        //local variable
        long heightLeft=-1,heightRight=-1;

        //stages
        unsigned long stage = 0;

    };

    Snapshot snapshot;
    snapshot.root=this->root;
    snapshot.heightLeft=snapshot.heightRight = -1;
    snapshot.stage = 0;

    std::stack<Snapshot> s;
    s.push(snapshot);

    long returnVal =-1;
    long diameter = -1;
    while(!s.empty())
    {
        #ifdef DEBUG
        counter++;
        #endif // DEBUG

        snapshot = s.top();
        s.pop();

        switch(snapshot.stage)
        {
            case(0):
            {
                if(snapshot.root == nullptr)
                  {
                     returnVal = -1;
                     continue;
                  }
                snapshot.stage = 1;
                s.push(snapshot);

                if(snapshot.root->left != nullptr)
                {
                    snapshot.root = snapshot.root->left;
                    snapshot.heightLeft=snapshot.heightRight=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case(1):
            {
                snapshot.heightLeft = returnVal;
                snapshot.stage = 2;
                s.push(snapshot);

                if(snapshot.root->right != nullptr)
                {
                    snapshot.root = snapshot.root->right;
                    snapshot.heightLeft=snapshot.heightRight=-1;
                    snapshot.stage=0;
                    s.push(snapshot);
                }
                else
                    returnVal=-1;

                continue;
            }

            case(2):
            {
                snapshot.heightRight = returnVal;

                diameter = Max(snapshot.heightLeft+snapshot.heightRight+1,diameter);

                returnVal = Max(snapshot.heightLeft,snapshot.heightRight)+1;

                continue;
            }
        }
    }


    #ifdef DEBUG
    std::cout<<"\nNumber of Loops for diameter :: "<<counter<<std::endl;
    #endif // DEBUG

    //since we want to return diameter as result
    //we will replace returnVal with diameter
    //return returnVal;
    return diameter;
}

//Program to
template<class T>
std::list<unsigned long> BinaryTreeOperations<T>::diameterPrint()
{
    /**

    std::list<unsigned long> diameterPrint(Node * root, long &height, long &diameter, list<long> &diameterList)
    {
        long heightLeft = heightRight = -1;

        std::list<unsigned long> subtreeLeft, subtreeRight;

        if(root->left != nullptr)
        {
            subtreeLeft = diameterPrint(root->left,heightLeft,diameter,diameterList);
        }

        if(root->right != nullptr)
        {
            subtreeRight = diameterPrint(root->right,heightRight,diameter,diameterRight);
        }

        if(heightLeft+heightRight+1 > diameter)
        {
            diameterList.clear();
            diameterList.insert(diameterList.begin(),subtreeLeft.begin(),subtreeLeft.end());
            diameterList.push_back(root->id);
            diameterList.insert(diameterList.begin(),subtreeRight,begin(),subtreeRight.end());
            diameter = heightLeft + heightRight + 1;
        }

        if(heightLeft>heightRight)
        {
            height = heightLeft+1;
            subtreeLeft.push_back(root->id);
            return subtreeLeft;
        }
        else
        {
            height = heightRight + 1;
            subtreeRight.push_front(root->id);
            return subtreeRight;
        }
    }
    **/

    #ifdef DEBUG
    unsigned long counter=0;
    #endif // DEBUG

    if(this->root == nullptr)
      {
         return std::list<unsigned long>();
      }

    typedef typename BinaryTree<T>::Node Node;

    struct Snapshot
    {
        //input parameters except reference
        Node * root;

        //local variables
        long heightLeft=-1,heightRight=-1;
        std::list<unsigned long> subtreeLeft, subtreeRight;

        //stage
        unsigned long stage=0;
    };

    Snapshot snapshot;

    snapshot.root = this->root;

    std::stack<Snapshot> s;
    s.push(snapshot);

    long height=-1, diameter=-1;
    std::list<unsigned long> diameterList,returnVal;

    while(!s.empty())
    {
        #ifdef DEBUG
        counter ++;
        #endif // DEBUG

        snapshot = s.top(); s.pop();

        switch(snapshot.stage)
        {
            case 0:
            {
                snapshot.stage = 1;
                s.push(snapshot);

                if(snapshot.root->left != nullptr)
                {
                    snapshot.root = snapshot.root->left;
                    snapshot.heightLeft=snapshot.heightRight=-1;
                    snapshot.subtreeLeft.clear();
                    snapshot.subtreeRight.clear();
                    snapshot.stage = 0;
                    s.push(snapshot);
                }

                continue;
            }

            case 1:
            {
                if(snapshot.root->left != nullptr)
                {
                    snapshot.heightLeft = height;
                    snapshot.subtreeLeft = returnVal;
                }

                snapshot.stage = 2;
                s.push(snapshot);


                if(snapshot.root->right != nullptr)
                {
                    snapshot.root = snapshot.root->right;
                    snapshot.heightLeft=snapshot.heightRight=-1;
                    snapshot.subtreeLeft.clear();
                    snapshot.subtreeRight.clear();
                    snapshot.stage = 0;
                    s.push(snapshot);
                }
                continue;
            }

            case 2:
            {
                if(snapshot.root->right != nullptr)
                {
                    snapshot.heightRight = height;
                    snapshot.subtreeRight = returnVal;
                }

                if(snapshot.heightLeft+snapshot.heightRight + 1 > diameter)
                {
                    diameterList.clear();
                    diameterList.insert(diameterList.end(),snapshot.subtreeLeft.begin(),snapshot.subtreeLeft.end());
                    diameterList.push_back(snapshot.root->id);
                    diameterList.insert(diameterList.end(),snapshot.subtreeRight.rbegin(),snapshot.subtreeRight.rend());
                    diameter = snapshot.heightLeft + snapshot.heightRight + 1;
                }

                if(snapshot.heightLeft>snapshot.heightRight)
                {
                    height = snapshot.heightLeft + 1;
                    snapshot.subtreeLeft.push_back(snapshot.root->id);
                    returnVal=snapshot.subtreeLeft;
                }
                else
                {
                    height = snapshot.heightRight + 1;
                    snapshot.subtreeRight.push_back(snapshot.root->id);
                    returnVal=snapshot.subtreeRight;
                }

                continue;
            }
        }

    }


    #ifdef DEBUG
    std::cout<<std::endl<<"Number of Loops to print diameter :: "<<counter<<std::endl;
    #endif // DEBUG

    return diameterList;
}

#endif
