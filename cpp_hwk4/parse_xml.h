#ifndef PARSE_XML_H
#define PARSE_XML_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

std::string read_file(const std::string);

class RegEx_Utility
{
private:
    std::string _contents;
public:
    RegEx_Utility(std::string contents): _contents(contents){};
    ~RegEx_Utility(){};
    void set_contents(std::string);
    std::vector<std::string> extract_substring(std::string);
};

#endif // PARSE_XML_H
