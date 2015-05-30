#ifndef PARSE_XML_H
#define PARSE_XML_H

#include <string>
#include <fstream>
#include <regex>
#include <vector>

#include "graph.h"

std::string read_file(const std::string);

class RegEx_Utility
{
private:
    std::string _contents;
public:
    RegEx_Utility(std::string contents): _contents(contents) {};
    ~RegEx_Utility() {};
    void set_contents(std::string newContents)
    {
        _contents = newContents;
    }
    std::vector<std::string> extract_substring(std::string);
};

class Location_Keeper
{
private:
    std::string _fname;
    std::vector<std::string> _xml_keywords;
    std::vector<Location_Node> _location_nodes; // the only valuable thing to the user

public:
    Location_Keeper(std::string fname, const std::vector<std::string>& xml_keywords): _fname(fname), \
    _xml_keywords(xml_keywords), _location_nodes({}){};
    ~Location_Keeper() {};

    void create_location_nodes();
    void print_location_nodes();
    std::vector<Location_Node> get_location_nodes()
    {
        return _location_nodes;
    }
};
#endif // PARSE_XML_H
