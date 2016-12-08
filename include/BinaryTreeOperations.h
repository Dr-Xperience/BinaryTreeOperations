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
        void recurssionPreOrder(void (*process)(T));
        void traverseLevelOrder(void (*process)(T));
        void traversePreOrderTraversal(void (*process)(T));
        void traversePostOrderTraversal(void (*process)(T));
        long heightDFS();
        long diameter();


    protected:
        void preOrderRec(void (*process)(T),typename BinaryTree<T>::Node * node);
    private:
//        T BinaryTreeRoot;
};

#endif // BINARYTREELEVELORDERTRAVERSAL_H
