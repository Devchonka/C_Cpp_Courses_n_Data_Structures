/**
    The following classes are defined below:
        RegEx_Utility : (?<=<PaperSize>)(.*?(\n))+.*(?=<\/PaperSize>)
        XMLNode
        PaperSize
        Area
        BarCodeScan
        NodeList
*/

#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <exception>
#include <fstream>

const std::string XML_FILE = "ScanParamsData.xml";

class RegEx_Utility
{
private:
    std::string _contents;
public:
    RegEx_Utility(std::string contents): _contents(contents){};
    ~RegEx_Utility(){};
    void set_contents(std::string);
    std::string extract_substring(std::string);

};

class XML_Node
{
public:
    XML_Node(){};
    virtual ~XML_Node(){};
    virtual void print_contents()=0;

};

class Node_Builder_Utility
{
    std::string _pattern;
    RegEx_Utility _parser;
    std::string _xml_file;
protected:
    std::string read_file(std::string);
    void set_pattern(std::string);
    void set_pattern_2_extract_var();
    void set_pattern_2_extract_lines();
    std::vector<std::string> parse_into_lines(std::string, int);
    void reset_pattern();
    std::string build_node_var_helper(std::string);

public:
    Node_Builder_Utility(const std::string xml_file) : _pattern(""), _parser(""), _xml_file(read_file(xml_file)){};
    ~Node_Builder_Utility(){};
    std::vector<std::string> build_node_var(std::string, int);

};

class PaperSize : public XML_Node
{
private:
    unsigned short _PaperSpecification;
    std::string _StandardName;
    std::string _Orientation;
    unsigned long _Width;
    unsigned long _Height;

public:
    PaperSize(): _PaperSpecification(0), _StandardName(""), _Orientation(""), _Width(0), _Height(0){};
    ~PaperSize(){};
    void print_contents()
    {
        std::cout<<"PaperSize contains: " <<_PaperSpecification<<" " << _StandardName<<" " << _Orientation<<" "
        <<_Width<<" " <<_Height<<std::endl;
    }

};


class Area : public XML_Node
{
private:
    unsigned long _UpperLeftX;
    unsigned long _UpperLeftY;
    unsigned long _Width;
    unsigned long _Height;
    unsigned long _SupportedScanAreaType;

public:
    Area(): _UpperLeftX(0), _UpperLeftY(0), _Width(0), _Height(0), _SupportedScanAreaType(0) {};
    ~Area(){};
    void print_contents()
    {
        std::cout<<"Area contains: " <<_UpperLeftX<<" " << _UpperLeftY<<" " << _Width<<" "
        <<_Height<<" " <<_SupportedScanAreaType<<std::endl;
    }

};

class BarCodeScan : public XML_Node
{
private:
    bool _Enable;
    unsigned short _Type;
    unsigned short _Direction;
    bool _CheckDigit;
    unsigned short _MaxBarCodes;

public:
    BarCodeScan(): _Enable(0), _Type(0), _Direction(0), _CheckDigit(0), _MaxBarCodes(0) {};
    ~BarCodeScan(){};
    void print_contents()
    {
        std::cout<<"BarCodeScan contains: " <<_Enable<<" " << _Type<<" " << _Direction<<" "
        <<_CheckDigit<<" " <<_MaxBarCodes<<std::endl;
    }
};

class NodeList
{
private:
    std::vector<XML_Node*> _nodeList;
public:
    int get_size();
    void vec_insert(XML_Node*);
    void vec_print();
};

#endif // DEFINES_H

