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


#endif
