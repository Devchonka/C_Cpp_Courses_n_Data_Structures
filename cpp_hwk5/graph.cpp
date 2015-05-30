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

/**
    Function to print distance vector.
*/
void MST_Utility::printSolution(PRIORITY_Q& spt_pairs, const vector<Location_Node>& vertices)
{
    while(!spt_pairs.empty())
    {
        pid temp = spt_pairs.top();
        spt_pairs.pop();
        cout<<setw(13)<<left<<"Node #: "+to_string(temp.first)<<setw(10)<<right<< " SPT dist: " << \
            setprecision(1)<<fixed<< temp.second<<endl;
    vertices[temp.first].print_node();
    }
}

/**
    Function returns index of min value that is not yet included in the MST included set
*/
int MST_Utility::minDist_Dijkstra(const vector<double>& dist, const vector<bool>& included_set)
{
    double min_weight = DBL_MAX;
    int min_index =0;
    for(int v = 0; v < _num_vertices; v++)
        if(included_set[v] == false && dist[v] <= min_weight)
        {
            min_weight = dist[v], min_index = v;
        }
    return min_index;
}

void MST_Utility:: _organize_spt(PRIORITY_Q& spt_pairs, \
                                 vector<int>& spt_index, vector<double>& spt_dist)
{
    for(int i =0; i<_num_vertices; i++)
    {
        spt_pairs.push(make_pair(spt_index[i], spt_dist[i]));
    }
}

PRIORITY_Q MST_Utility::Dijkstra()
{
    vector<double> dist(_num_vertices, DBL_MAX);  // all distances start infinite
    vector<bool> sptSet(_num_vertices, 0); // holds true if included in shortest path (shortest path tree set)
    vector<int> SPT_indices;
    dist[_src] = 0; // dist from source to itself
    int u;
    for(int count = 0; count < _num_vertices; count++)
    {
        u = minDist_Dijkstra(dist, sptSet); // returns min element index
        sptSet[u] = true; // mark vertex as visited
        SPT_indices.push_back(u);
        for(int v = 0; v < _num_vertices; v++)  // Update dist value of the adjacent vertices of the picked vertex.
        {
            if(!sptSet[v] && (_AdjMatrix[u][v]) && (dist[u] < DBL_MAX)   // update if not in sptSet, theres an edge u to v
                    && dist[u]+_AdjMatrix[u][v] < dist[v]) // also if total weight of path src to v thru u < current dist[v]
            {
                dist[v] = dist[u] + _AdjMatrix[u][v];
            }
        }
    }
    PRIORITY_Q spt_pairs;
    _organize_spt(spt_pairs, SPT_indices, dist);
    return spt_pairs;
}

void Graph::run_MST(int src)
{
    _mst_util.set_src(src);
    PRIORITY_Q temp = _mst_util.Dijkstra();
    _mst_util.printSolution(temp, _vertices);
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
