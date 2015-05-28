/**
    Graph class.
    Implementation based on vertices containing a vector of location nodes (each containing some information about
    a restaurant chain location), and a vector of vectors of weights for the distances between every 2 locations.

    In this use, it is a complete graph (n vertices, n*(n-1)/2 edges).
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;

int dijksta();

class Location_Node
{
private:
    std::vector<std::string> _contact_info;
    double _longitude;
    double _latitude;
public:
    Location_Node(): _contact_info({}), _longitude(0), _latitude(0) {};
    ~Location_Node() {};

    double get_long()
    {
        return _longitude;
    }
    double get_lat()
    {
        return _latitude;
    }
    std::string get_Address()
    {
        return _contact_info[0];
    }
    void add_contact_info(std::string info)
    {
        _contact_info.push_back(info);
    }
    void set_longi(double longi)
    {
        _longitude = longi;
    }
    void set_lati(double lati)
    {
        _latitude = lati;
    }

    void print_node()
    {
        for(unsigned i =0; i<_contact_info.size(); i++)
        {
            cout<<_contact_info[i]<<" ";
        }
        cout<<_longitude<< " "<<_latitude <<endl;
    }
};

class MST_Utility
{
private:
    std::vector < std::vector < int > > _AdjMatrix;
    int _src; // starting node
    int _num_vertices;
public:
    MST_Utility(): _AdjMatrix({}), _src(0), _num_vertices(0){};
    MST_Utility(std::vector < std::vector < int > > AdjMatrix, int src): _AdjMatrix(AdjMatrix), _src(src), \
                                                            _num_vertices(_AdjMatrix[0].size()){};
    ~MST_Utility() {};

    void init(std::vector < std::vector < int > > AdjMatrix, int src)
    {
        _AdjMatrix = AdjMatrix;
        _src = src;
        _num_vertices = _AdjMatrix[0].size();
    }

    void set_src(int);

    std::vector<int> Dijkstra(); // should make static?
    int minDistance(std::vector<int>, std::vector<bool>);

    void printSolution(std::vector<int>);
};

class Graph
{
private:
    std::vector<Location_Node> _vertices;
    std::vector < std::vector < int > > _AdjMatrix;
    MST_Utility _mst_util; //intentional strong coupling here

    void init(); // initialize all edges to zero

protected:
    double Radians(double value)
    {
        return (double)value * M_PI / 180.0;
    }

    double get_dist(Location_Node&, Location_Node&);

public: //_num_vertices(_vertices.size()),
    Graph(std::vector<Location_Node> vertices)
    {
        _vertices = vertices;
        init();
        _mst_util.init(_AdjMatrix, 0);
    }

    void build_edges();
    void addEdge(int, int, int weight = 1);

    void print_adjMatrix();
    void print_vertices();

    void run_MST(int); // takes in starting node

    int get_num_vertices();
    int get_num_edges();
};

#endif // GRAPH_H
