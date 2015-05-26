// base it on adjacency matrix since all connected

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;

int dijksta();

const double PI = 3.14159;

class Graph
{
private:
    int m_verticeCount;
    std::vector < std::vector < int > > m_AdjM;

    void init(); // initialize all edges to zero
public:
    Graph(int count) : m_verticeCount(count), m_AdjM({}) {init();}

    //add edge
    void addEdge(int start, int end, int weight = 1)
    {
        m_AdjM[start][end] = weight;
        m_AdjM[end][start] = weight;
    }
    //print graph
    void print();

};

class Location_Node
{
private:
    std::vector<std::string> _contact_info;

    double _longtitude;
    double _latitude;
public:
    Location_Node(): _contact_info({}), _longtitude(0), _latitude(0) {};
    ~Location_Node() {};

    double get_long()
    {
        return _longtitude;
    }
    double get_lat()
    {
        return _latitude;
    }

    void add_contact_info(std::string info)
    {
        _contact_info.push_back(info);
    }

    void set_longi(double longi)
    {
        _longtitude = longi;
    }
    void set_lati(double lati)
    {
        _latitude = lati;
    }

    void print_node()
    {
        for (unsigned i =0; i<_contact_info.size(); i++)
            cout<<_contact_info[i]<<" ";
        cout<<_longtitude<< " "<<_latitude <<endl;
    }

};


class MST_Utility
{
public:
    MST_Utility() {};
    ~MST_Utility() {};

    double Radians(double value)
    {
        return (double)value * PI / 180.0;
    }

    double get_dist(Location_Node&, Location_Node&);

    //static void Dijkstra();
    //std::vector<std::string> extract_substring(std::string);
};

#endif // GRAPH_H
