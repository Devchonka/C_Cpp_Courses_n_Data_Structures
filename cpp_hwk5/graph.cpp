//Dijkstra's algorithm
#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>

#include "graph.h"

using namespace std;
#define MAX 100001
#define INF (1<<20)
#define pii pair< int, int >
#define pb(x) push_back(x)

// lambda expression
auto comp = [](const pii &a, const pii &b) -> bool { return a < b; };
priority_queue<pii, vector<pii > , decltype(comp) > Q(comp);


vector<pii > G[MAX];
int D[MAX];
bool F[MAX];

int MST_Utility::Dijkstra()
{
    int i, u, v, w, sz, nodes, edges, starting;
    // create graph
    cout << "Enter the number of vertices and edges: ";
    cin >> nodes >> edges;
    cout << "Enter the edges with weigth: <source> <destination> <weigth>: \n";
    for(i = 0; i < edges; i++)
    {
        cin >> u >> v >> w;
        G[u].pb(pii(v, w));
        G[v].pb(pii(u, w)); // for undirected
    }
    cout << "Enter the source node: ";
    cin >> starting;
    // initialize distance vector
    for(i = 1; i <= nodes; i++)
    {
        D[i] = INF;
    }
    D[starting] = 0;
    Q.push(pii(starting, 0));
    // dijkstra
    while(!Q.empty())
    {
        u = Q.top().first;
        Q.pop();
        if(F[u])
        {
            continue;
        }
        sz = G[u].size();
        for(i = 0; i < sz; i++)
        {
            v = G[u][i].first;
            w = G[u][i].second;
            if(!F[v] && D[u] + w < D[v])
            {
                D[v] = D[u] + w;
                Q.push(pii(v, D[v]));
            }
        }
        F[u] = 1; // done with u
    }
    // result
    for(i = 1; i <= nodes; i++)
    {
        cout << "Node " << i << ", min weight = " << D[i] << endl;
    }
    return 0;
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

void Graph::init(void)
{
    int num_vertices = _vertices.size();
    for(unsigned i = 0; i < num_vertices; i++)
    {
        std::vector < int > row;
        for(unsigned j = 0; j < num_vertices; j++)
        {
            row.push_back(0);
        }
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
            cout << std::setw(3) << std::right << _AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::print_vertices()
{
    cout<<endl;
    for(Location_Node node: _vertices)
    {
        node.print_node();
    }
}

int Graph::get_num_vertices()
{
    return _vertices.size();
}

int Graph:: get_num_edges()
{
    int num_vertices = _vertices.size();
    return num_vertices * (num_vertices-1) / 2;
}

void Graph::addEdge(int from, int to, int weight)
{
    _AdjMatrix[from][to] = weight;
    //_AdjMatrix[to][from] = weight;
}
void Graph::build_edges()
{
    int num_vertices = get_num_vertices();
    for(int j =0; j<num_vertices-1; j++) // not include the diagonal
    {
        int i = j;
        while(i < num_vertices-1)
        {
            //cout<<j<<" "<<i+1<<" " << get_dist(_vertices[j], _vertices[i+1]) << endl;
            addEdge(j, i+1, get_dist(_vertices[j], _vertices[i+1]));
            i++;
        }
        //cout<<endl;
    }
}
