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

template<class T>
class BinaryTreeOperations:public BinaryTree<T>
{
    public:

        //Constructors
        BinaryTreeOperations();
        BinaryTreeOperations(T);
        BinaryTreeOperations(BinaryTreeOperations&);
        virtual ~BinaryTreeOperations();

        //MemberFunction
        void recursionPreOrder(void (*process)(T));
        void traverseLevelOrder(void (*process)(T));
        void printLevelOrder(void (*process)(T,bool newLine, bool leaveNode));
        void traversePreOrderTraversal(void (*process)(T));

        //Complexity O(3N) or O(N) -- it can be reduced to O(N) literally
        //But haven't tried will try sometime
        void traversePostOrderTraversal(void (*process)(T));
        long heightDFS();

        //diameter with O(N*N) or O(N^2) complexity
        long diameterN2();

        //diameter with O(N) complexity
        long diameter();


    protected:
        void preOrderRec(void (*process)(T),typename BinaryTree<T>::Node * node);
    private:
//        T BinaryTreeRoot;
};

#endif // BINARYTREELEVELORDERTRAVERSAL_H
