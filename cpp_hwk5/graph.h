/**
    Graph related classes:
    Graph
    MST_Utility
    Location_Node
    COMP (Functor)

    Adjacency matrix implementation since given a complete graph (not sparse matrix).
    Graph given comes from XML file that contains locations of a restaurant chain, such as a node below:

<Location>
    <Address>3240 Coors NW</Address>
    <City>Albuquerque</City>
    <State>NM</State>
    <Phone>(505)839-6966</Phone>
	<Latitude>35.11</Latitude>
	<Longitude>-106.70</Longitude>
</Location>

    A regex utility is used to parse the XML file with provided keywords.

    Weights for the edges are calculated using Haversine formula using the lat and long of the coordinates.
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue> // for priority_queue
#include <iomanip>
#include <cmath> // for M_PI
#include <cfloat> // for DBL_MAX
#include <tuple>

typedef std::pair<int, double> pid;
typedef std::pair<double,double> pdd;

struct COMP //functor for keeping priority queue sorted in order of increasing distance
{
	bool operator()(const pid& a, const pid& b)
	{
		return a.second > b.second;
	}
};
typedef std::priority_queue<pid, std::vector<pid>, COMP> PRIORITY_Q;


class Location_Node
{
private:
    std::vector<std::string> _contact_info;
    pdd _coordinates;
public:
    Location_Node(): _contact_info({}), _coordinates(std::make_pair(0.0,0.0)){};
    ~Location_Node() {};

    double get_long()
    {
        return _coordinates.first;
    }
    double get_lat()
    {
        return _coordinates.second;
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
        _coordinates.first = longi;
    }
    void set_lati(double lati)
    {
        _coordinates.second = lati;
    }

    void print_node() const
    {
        for(auto& i:_contact_info)
            std::cout<<i<<" ";
        std::cout<<std::endl<<std::endl;
    }
};

class MST_Utility
{
private:
    std::vector < std::vector < double > > _AdjMatrix;
    int _src; // starting node
    int _num_vertices;

    void _organize_spt(PRIORITY_Q&, std::vector<int>&, std::vector<double>&); //index, dist pairs
public:
    MST_Utility(): _AdjMatrix({}), _src(0), _num_vertices(0){};
    ~MST_Utility() {};

    void init(std::vector < std::vector < double > > AdjMatrix, int src)
    {
        _AdjMatrix = AdjMatrix;
        _src = src;
        _num_vertices = _AdjMatrix.size();
    }

    void set_src(int);

    PRIORITY_Q Dijkstra(); // should make static if threading?
    int minDist_DijkstraPrim(const std::vector<double>&, const std::vector<bool>&);

    std::vector<int> Prim();
    int minIndex_Prim(std::vector<int>&, std::vector<bool>&);
    void print_Prim_MST(std::vector<int>&);

    void printSolution(PRIORITY_Q&, const std::vector<Location_Node>&);
};

class Graph
{
private:
    std::vector<Location_Node> _vertices;
    std::vector < std::vector < double > > _AdjMatrix; // made symmetric (undirected)
    MST_Utility _mst_util; //intentional strong coupling here

    void init(); // initialize all edges to zero

protected:
    double Radians(double value)
    {
        return (double)value * M_PI / 180.0;
    }

    double get_dist(Location_Node&, Location_Node&);

public:
    Graph(std::vector<Location_Node> vertices): _vertices(vertices), _AdjMatrix({}), _mst_util()
    {
        init();
    }

    void build_edges();
    void addEdge(int, int, double weight = 1.0);

    void print_adjMatrix();
    void print_vertices();

    void run_MST(int); // takes in starting node
    int get_num_vertices();
};

#endif // GRAPH_H
