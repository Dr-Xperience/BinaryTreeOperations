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
#include <iostream>
#include <string>
#include "BinaryTreeOperations.h"
#include "BinaryTreeOperations.cpp"
using namespace std;

struct Node
{
    std::string data;
    Node *left;
    Node *right;
};
void process(Node*);
int main()
{
    cout << "Hello world!" << endl;

    Node * root = new Node;

    root->data="1"; root->left=nullptr; root->right=nullptr;

    BinaryTreeOperations<Node *> b(root);

    for(int i=2;i<=8;++i)
    {
        root = new Node;
        root->data=std::to_string(i);
        root->left=root->right=nullptr;
        b.insertBack(root);
        std::cout<<" i = "<<i<<std::endl;
    }

    std::cout<<std::endl<<"Level Order Traversal :: ";
    b.traverseLevelOrder(process);

    std::cout<<std::endl<<"Post Order Traversal :: ";
    b.traversePostOrderTraversal(process);

    std::cout<<std::endl<<"Height of Tree :: "<<b.heightDFS()<<std::endl;

    return 0;
}

void process(Node* root)
{
    std::cout<<root->data<<" ";
}
