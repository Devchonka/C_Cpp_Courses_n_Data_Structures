#include "graph.h"
using namespace std;


vector<int> MST_Utility::Prim()
{
    vector<int> from(_num_vertices);
    vector<int> to(_num_vertices, INT_MAX);
    vector<bool> mstSet(_num_vertices,0);
    to[0] = 0;
    from[0] = -1;
    int u =0;
    for(int count = 0; count < _num_vertices-1; count++)
    {
        u = minIndex_Prim(to, mstSet);
        mstSet[u] = true;
        for(int v = 0; v < _num_vertices; v++)
        {
            if(_AdjMatrix[u][v] && mstSet[v] == false && _AdjMatrix[u][v] <  to[v])
            {
                from[v]  = u;
            }
            to[v] = _AdjMatrix[u][v];
        }
    }
    return from;
}

int MST_Utility::minIndex_Prim(const vector<int>& key, const vector<bool>& mstSet)
{
    int min = INT_MAX, min_index;
    for(int v = 0; v < _num_vertices; v++)
        if(mstSet[v] == false && key[v] < min)
        {
            min = key[v], min_index = v;
        }
    return min_index;
}

void MST_Utility::print_Prim_MST(const vector<int>& from)
{
    cout << "MST for Undirected Graph using Prim's Algorithm:" << endl<<endl;
    cout<<"  Edge      Weight"<<endl;
    for(int i = 1; i < _num_vertices; i++)
    {
        cout<<setw(3) << right << from[i]<<setw(4) << right <<" - " + to_string(i) << " " << setw(10) << right<< \
            setprecision(4)<<fixed<< _AdjMatrix[i][from[i]] << endl;
    }
    cout<<endl;
}
