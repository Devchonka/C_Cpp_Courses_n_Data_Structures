#include "graph.h"
using namespace std;

vector<double> MST_Utility::Dijkstra()
{
    vector<double> dist(_num_vertices, DBL_MAX);
    vector<bool> sptSet(_num_vertices, 0);
    dist[_src] = 0;
    for(int count = 0; count < _num_vertices-1; count++)
    {
        int u = minDist_Dijkstra(dist, sptSet);
        sptSet[u] = 1;
        for(int v = 0; v < _num_vertices; v++)
        {
            if(!sptSet[v] && _AdjMatrix[u][v] && (dist[u] != DBL_MAX) \
                    && dist[u]+_AdjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + _AdjMatrix[u][v];
            }
        }
    }
    return dist;
}


/**
    Function returns index of min value that is not yet included in the MST included set
*/
int MST_Utility::minDist_Dijkstra(const vector<double>& dist, const vector<bool>& included_set)
{
    double min_weight = DBL_MAX;
    int min_index =0;
    for(int v = 0; v < _num_vertices; v++)
        if(included_set[v] == false && dist[v] < min_weight)
        {
            min_weight = dist[v], min_index = v;
        }
    return min_index;
}

/**
    Function to print distance vector.
*/
void MST_Utility::print_Dijkstra_spt(const vector<double>& dist)
{
    cout << "SPT for Undirected Graph using Dijkstra's Algorithm:" << endl<<endl;
    cout<<"  Edge      Weight"<<endl;
    for(int i = 1; i < _num_vertices; i++)
    {
        cout<<setw(3) << right << 0 <<setw(4) << right <<" - " + to_string(i) << " " << setw(10) << right<< \
            setprecision(4)<<fixed<< dist[i] << endl;
    }
    cout<<endl;
}

