/*****************************0*0 **********************************************
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
#include <algorithm> // for copy and transform algorithm
#include<iterator>//for ostream_iterator
#include "BinaryTreeOperations.h"
#include "BinaryTreeOperations.cpp"

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
using namespace std;

/** Total code re-base on updated BinaryTree Class
**/

void process(std::string);
std::string process(long id,bool& skip, bool& cont);
void process(long);
void print(std::string,bool,bool);
std::string interactive(long id,bool& skip, bool& cont);
void MemoryBenchmark();
void MemoryBenchmarkWithInsert();

unsigned long static HISTORYPRIVATE = 0;
unsigned long static HISTORYWORKING = 0;


int main()
{
    cout << "Hello world!" << endl;

//    MemoryBenchmark();
//    MemoryBenchmarkWithInsert();



    BinaryTreeOperations<std::string> b("1");

    std::list<std::string> input;
    for(int i=2; i<=160000; ++i)
    {
        // n^2 complexity oh boy
//        b.insert(std::to_string(i));
          input.push_back(std::to_string(i));
//        std::cout<<" i = "<<i<<std::endl;
    }
    b.insert(input);


    std::cout<<std::endl<<"Level Order Traversal :: ";
//        b.traverseLevelOrder(process);
//    b.printLevelOrder(print);

    std::cout<<std::endl<<"Post Order Traversal :: ";
//    b.traversePostOrderTraversal(process);

    std::cout<<std::endl<<"Height of Tree DFS :: "<<b.heightDFS()<<std::endl;
    std::cout<<std::endl<<"Height of Tree BFS :: "<<b.heightBFS()<<std::endl;

    std::cout<<std::endl<<"Diameter of Tree :: "<<b.diameter()<<std::endl;
    std::list<unsigned long> list = b.diameterPrint();

    std::copy(list.begin(),list.end(),std::ostream_iterator<unsigned long>(std::cout," "));
    std::cout<<std::endl;

    /** Creating tree for checking Diameter of Tree which doesn't pass through root
     Tree be like of form

           1
          / \
         2   3
        / \
       4   5
      /   /
     8   10
    /     \
    16      21
    Diameter will be 8,4,2,5,10 or 16-8-4-2-5-10-21
    **/

    b.clear();
//    BinaryTreeOperations<std::string> b1;

    b.insertInteractive(process);

    std::cout<<std::endl<<"Level Order Traversal :: ";
    b.printLevelOrder(print);

    std::cout<<std::endl<<"Post Order Traversal :: ";
    b.traversePostOrderTraversal(process);

//    std::cout<<std::endl<<"Diameter of Tree :: "<<b1.diameterN2()<<std::endl;

    std::cout<<std::endl<<"Diameter of Tree :: "<<b.diameter()<<std::endl;

    list.clear();
    //printing diameter to screen
    list = b.diameterPrint();

//    shortcut to print list on ostream
    std::copy(list.begin(),list.end(),std::ostream_iterator<unsigned long>(std::cout," "));
    std::cout<<std::endl;
//    b.clear();
//
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

    std::cout<<"\nVirtual Memory Used by Process  (MB):: "<<static_cast<float>(virtualMemUsedByMe)/1024/1024<<std::endl;
    std::cout<<"Physical Memory Used by Process (MB):: "<<static_cast<float>(physMemUsedByMe)/1024/1024<<std::endl;

    return 0;
}

std::string interactive(long id,bool& skip, bool& cont)
{
    std::string data,yes,yesSkip;
    std::cout<<std::endl<<"Do you wish to skip node id "<<id<<" (y/n) ::";
    std::cin>>yesSkip;

    std::transform(yesSkip.cbegin(),yesSkip.cend(),yesSkip.begin(),::tolower);

    if(yesSkip.compare("y")==0 || yesSkip.compare("yes")==0)
        skip = true;
    else if(yesSkip.compare("n")==0 || yesSkip.compare("no")==0)
        skip = false;

    if(skip == false)
    {
        std::cout<<std::endl<<"Enter data at node id "<<id<<" :: ";
        std::cin>>data;
    }

    std::cout<<std::endl<<"Do you wish enter more (y/n) :: ";
    std::cin>>yes;

    std::transform(yes.cbegin(),yes.cend(),yes.begin(),::tolower);

    if(yes.compare("y")==0 || yes.compare("yes")==0)
        cont = true;
    else if(yes.compare("n")==0 || yes.compare("no")==0)
        cont = false;

    return data;
}

void process(std::string data)
{
    std::cout<<data<<" ";
}

std::string process(long id,bool& skip,bool& cont)
{
    cont = true;
    skip = false;

    switch (id)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
        case 10:
        case 16:
        {
             return std::to_string(id);
        }
        case 21:
        {
            cont=false;
            return std::to_string(id);
        }
        default:
        {
          skip = true;
          return std::string();
        }
    }

//    return std;
}

void print(std::string data,bool newLine, bool leaveNode)
{
    if(leaveNode == true)
        std::cout<<"N"<<" ";
    else if(newLine == false)
    {

        std::cout<<data<<" ";
    }
    else
        std::cout<<std::endl;
}

void process(long data)
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));
    GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
//  std::cout<<data<<" ";
    if (pmc.PrivateUsage>HISTORYPRIVATE)
        HISTORYPRIVATE=pmc.PrivateUsage;
    if (pmc.WorkingSetSize>HISTORYWORKING)
        HISTORYWORKING=pmc.WorkingSetSize;
}

void MemoryBenchmark()
{
    long N = 1000;
    BinaryTreeOperations<long> b;
    b.createN(N);

    PROCESS_MEMORY_COUNTERS_EX pmc;
    ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));
    GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

    std::cout<<"Number of Nodes :: "<<N<<std::endl;
    std::cout<<"\nVirtual Memory Used by Process after tree Creation (KB):: "<<static_cast<float>(virtualMemUsedByMe)/1024<<std::endl;
    std::cout<<"Physical Memory Used by Process after tree Creation (KB):: "<<static_cast<float>(physMemUsedByMe)/1024<<std::endl;


    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"Recursive Pre-Order Traversal :: ";
    b.recursionPreOrder(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"\nIterative Pre-Order Traversal :: ";
    b.traversePreOrderTraversal(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"\nIterative with \"manual stack\" Pre-Order Traversal :: ";
    b.traversePostOrderTraversal(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

}


void MemoryBenchmarkWithInsert()
{
    long N = 1000000;
    BinaryTreeOperations<long> b(1);

    std::list<long> q;

    for(int i=2; i<N; ++i)
    {
        q.push_back(i);
    }

    b.insert(q);

    PROCESS_MEMORY_COUNTERS_EX pmc;
    ZeroMemory(&pmc, sizeof(PROCESS_MEMORY_COUNTERS_EX));
    GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

    std::cout<<"Number of Nodes :: "<<N<<std::endl;
    std::cout<<"\nVirtual Memory Used by Process after tree Creation (KB):: "<<static_cast<float>(virtualMemUsedByMe)/1024<<std::endl;
    std::cout<<"Physical Memory Used by Process after tree Creation (KB):: "<<static_cast<float>(physMemUsedByMe)/1024<<std::endl;


    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"Recursive Pre-Order Traversal :: ";
    b.recursionPreOrder(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"\nIterative Pre-Order Traversal :: ";
    b.traversePreOrderTraversal(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

    HISTORYPRIVATE=HISTORYWORKING=0;
    std::cout<<std::endl<<"\nIterative with \"manual stack\" Pre-Order Traversal :: ";
    b.traversePostOrderTraversal(process);
    std::cout<<"\nMaximum Virtual Memory Used by Process  (KB):: "<<static_cast<float>(HISTORYPRIVATE)/1024<<std::endl;
    std::cout<<"Maximum Physical Memory Used by Process (KB):: "<<static_cast<float>(HISTORYWORKING)/1024<<std::endl;

}
