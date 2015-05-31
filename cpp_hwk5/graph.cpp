//Dijkstra's algorithm
#include <cstdio>
#include <iomanip>
#include <queue>
#include <vector>
#include <iostream>
#include <climits>

#include "graph.h"

using namespace std;

void MST_Utility::set_src(int src)
{
    _src = src;
}

void Graph::run_MST(int src)
{
    // Set starting node for the MST or SPT
    _mst_util.set_src(src);

    // Run and Print Dijkstra's SPT to each node
    vector<double> dijkstra_spt = _mst_util.Dijkstra();
    _mst_util.print_Dijkstra_spt(dijkstra_spt);


    // Run and Print Prim's MST
    vector<int> prim_MST = _mst_util.Prim();
    _mst_util.print_Prim_MST(prim_MST);
}

/**
    Haversine formula for distance calculation.
*/
double Graph::get_dist(Location_Node& loc1, Location_Node& loc2)
{
    double earth_radius = 6372.8; // km
    double dLatitude = Radians(loc2.get_lat()-loc1.get_lat());
    double dLongitude = Radians(loc2.get_long()-loc1.get_long());
    double nA = pow(sin(dLatitude/2.0), 2.0) + cos(Radians(loc1.get_lat())) * \
                cos(Radians(loc2.get_lat())) * pow(sin(dLongitude/2.0), 2.0);
    double nC = 2.0 * atan2(sqrt(nA), sqrt(1.0 - nA));
    return earth_radius * nC;
}

void Graph::init(void) //vector<double> dist(_num_vertices, DBL_MAX)
{
    unsigned num_vertices = _vertices.size();
    for(unsigned i = 0; i < num_vertices; i++)
    {
        std::vector < double > row(num_vertices, 0.0);
        _AdjMatrix.push_back(row);
    }
}

void Graph::print_adjMatrix(void)
{
    cout << "Adjacency Matrix for Undirected is: " << endl;
    unsigned adj_size = _AdjMatrix.size();
    cout << endl << "    ";
    for(unsigned i = 0; i < adj_size ; i++)
    {
        cout << std::setw(3) << std::right << i << " ";
    }
    cout << endl;
    for(unsigned i = 0; i < adj_size; i++)
    {
        cout << std::setw(3) << std::right <<i << " ";
        for(unsigned j = 0; j < _AdjMatrix[i].size(); j++)
        {
            cout << std::setw(3) << std::right << setprecision(0)<<fixed<<_AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::print_vertices()
{
    cout<<endl;
    for(auto it = _vertices.begin(); it != _vertices.end();  ++it)
    {
        cout<< "Node #" << distance(_vertices.begin(), it) << ": ";
        it->print_node();
    }
}

int Graph::get_num_vertices()
{
    return _vertices.size();
}

void Graph::addEdge(int from, int to, double weight)
{
    _AdjMatrix[from][to] = weight;
    _AdjMatrix[to][from] = weight;
}

void Graph::build_edges()
{
    int num_vertices = get_num_vertices();
    for(int j =0; j<num_vertices-1; j++) // not include the diagonal
    {
        int i = j;
        while(i < num_vertices-1)
        {
            addEdge(j, i+1, get_dist(_vertices[j], _vertices[i+1]));
            i++;
        }
    }
    _mst_util.init(_AdjMatrix, 0); // initialize MST utility with new adjacency matrix
}
