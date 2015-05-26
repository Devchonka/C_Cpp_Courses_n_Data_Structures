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
public:
    MST_Utility() {};
    ~MST_Utility() {};

    int Dijkstra(); // should make static?
};

class Graph
{
private:
    std::vector<Location_Node> _vertices;
    std::vector < std::vector < int > > _AdjMatrix;
    MST_Utility _mst_util;

    void init(); // initialize all edges to zero

protected:
    double Radians(double value)
    {
        return (double)value * M_PI / 180.0;
    }

    double get_dist(Location_Node&, Location_Node&);

public: //_num_vertices(_vertices.size()),
    Graph(std::vector<Location_Node> vertices) : _vertices(vertices),  _AdjMatrix({}), _mst_util()
    {
        init();
    }

    void build_edges();
    //add edge
    void addEdge(int, int, int weight = 1);
    //print graph
    void print_adjMatrix();
    void print_vertices();

    int get_num_vertices();
    int get_num_edges();
};

#endif // GRAPH_H
