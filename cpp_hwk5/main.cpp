/**
    CIS 29 : Advanced C++.
    Author: Elena Menyaylenko           Date: 05/29/2015

    Assignment: Graphs and SPTs (Shortest Path Trees), Multi-Threading, Functors/Lambda Expressions,
                Regex, XML files, Advanced STL containers.

                Algorithms implemented: Prim (MST) and Dijkstra (SPT)

    To compile code:
         g++ -std=c++11 *.h *.cpp -o cpp_hwk5
*/

#include "parse_xml.h"
#include "graph.h"

const std::string fname = "Coordinates.xml";
const std::vector<std::string> xml_keywords = {"Address", "City", "State", "Phone", "Latitude", "Longitude"};

int main()
{
    // Create a database of locations that contains disconnected nodes
    Location_Keeper loc_database(fname, xml_keywords);
    loc_database.create_location_nodes();
    // Pass disconnected nodes to a graph to create location web (build incident edges)
    Graph loc_web(loc_database.get_location_nodes());
    loc_web.build_edges();
    loc_web.print_vertices();
    loc_web.print_adjMatrix();
    // The graph contains and MST utility which runs different SPT algorithms
    int start_node = 1;
    loc_web.run_MST(start_node);
    return 0;
}
