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
BinaryTreeOperations<T>::BinaryTreeOperations(T root1):BinaryTree<T>(root1)
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
    T root = this->root;

    std::queue<T> q;
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
        process(root);

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
void BinaryTreeOperations<T>::traversePostOrderTraversal(void (*process)(T))
{
    #ifdef DEBUG
    long counter =0;
    #endif //DEBUG
    struct Snapshot
    {
        T root; //argument of Member Function
        //No memberFunctions Present
        long stage;
    };

    std::stack<Snapshot> s;

    Snapshot snapshot,newSnapshot;

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
                process(snapshot.root);
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

    struct Snapshot
    {
        //Arguments to function
        T root;
        //Local Variables
        long leftHeight, rightHeight;
        //stage
        int stage;
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
    std::cout<<std::endl<<"Loop Count of Height of Tree :: "<<counter<<std::endl;
    #endif // DEBUG
    return returnVal;
}

static long Max(long x, long y)
{
    return(x^((x^y)&-(x<y)));
}

template <class T>
long BinaryTreeOperations<T>::diameter()
{
    #ifdef DEBUG
    long counter = 0;
    #endif // DEBUG
    /**
    long diameter(root)
    {
        if(root == null)
            return 0;

        long leftHeight=heightDFS(root->left);
        long rightHeight=heightDFS(root->right);

        long leftDiameter=diameter(root->left);
        long rightDiameter=diameter(root->right);

        return MAX(leftHeight+rightHeight,Max(leftDiameter,rightDiameter));
    }
    */

    struct Snapshot
    {
        //function argument
        T root;
        //local variable
        long leftHeight,rightHeight,leftDiameter,rightDiameter;
        //stage
        long stage;
    };

    long returnVal;

    Snapshot snapshot;

    snapshot.root = this->root;
    snapshot.leftHeight=snapshot.rightHeight=snapshot.leftDiameter=snapshot.rightDiameter=-1;
    snapshot.stage=0;

    std::stack<Snapshot> s;

    s.push(snapshot);
    T temp = this->root;
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
#endif
