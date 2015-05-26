

#include <iostream>
#include "parse_xml.h"
#include "graph.h"

using namespace std;

const string fname = "Coordinates.xml";

int main()
{
    Location_Keeper loc_database(fname);
    loc_database.create_location_nodes();
    // loc_database.print_location_nodes();


        Graph G(loc_database.get_num_locations());



    	G.addEdge(0, 1,7);
    	G.addEdge(0, 3);
    	G.addEdge(1, 4,5);
    	G.addEdge(1, 2);
    	G.addEdge(2, 3);
    	G.addEdge(4, 3);



    	G.print();

    // dijksta();
    return 0;
}
