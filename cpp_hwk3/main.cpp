/*********************************************************************************
** 													    Spring, 2015
** Advanced C++ Hwk 3
**  Written By: Menyaylenko, Elena
**
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**
**  Assignment: Store XML file data in an object oriented way and display to screen.
**
    Procedure:
    CLASSES:
        RegEx_Utility
        Node_Builder_Utility
        XMLNode
        PaperSize
        Area
        BarCodeScan
        NodeList

    1) Read xml file to get xml file string
    2) Run xml file string through RegEx class utility to get out class contents string
    3) Pass string class contents into constructor of every class to create each of 3 classes
    4) Push 3 nodes into NodeList class
    5) Print contents of NodeList


    To compile code:
         g++ -std=c++11 *.cpp *.h -o cpp_hw3
    To run Valgrind:
         valgrind --tool=memcheck --leak-check=yes ./cpp_hw3

************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector> // NOT NEEDED ANY MORE

#include "defines.h"

using namespace std;


int main()
{
    Node_Builder_Utility node_builder (XML_FILE);
    vector<string> class_names = {"PaperSize", "Area", "BarCodeScan"};
    vector<int> class_num_var = {5, 5, 5};

    PaperSize* p_node = new PaperSize();
    Area* a_node = new Area();
    BarCodeScan* b_node = new BarCodeScan();

    for (unsigned int i =0; i < class_names.size(); i++)
        node_builder.build_node_var(class_names[i], class_num_var[i]);

    NodeList node_list;
    node_list.vec_insert(p_node);
    node_list.vec_insert(a_node);
    node_list.vec_insert(b_node);

    node_list.vec_print();

    delete p_node; delete a_node; delete b_node;
    return 0;
}
