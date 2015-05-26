#include <iostream>
#include "parse_xml.h"
#include "graph.h"

using namespace std;

const string fname = "Coordinates.xml";

int main()
{
    Location_Keeper loc_database(fname);
    loc_database.create_location_nodes();
    Graph loc_web(loc_database.get_location_nodes());
    //loc_web.print_vertices();
    loc_web.build_edges();
    loc_web.print_adjMatrix();
    return 0;
}
