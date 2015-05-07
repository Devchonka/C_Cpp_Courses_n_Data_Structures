#include "defines.h"
using namespace std;

/**
RegEx_Utility Definitions
*/
string RegEx_Utility::extract_substring(string pattern)
{
    try
    {
        regex r(pattern);
        smatch results;
        if(regex_search(_contents, results, r))
        {
            //cout << "The match is: " << results[1].str() << endl;
            return results[1].str();
        }
        else
        {
            cout << "Error: no match for pattern."<<endl;
            return "";
        }
    }
    catch(regex_error &e)
    {
        cout << "Error: " << e.what() <<" Code: " << e.code() << endl;
        exit(1);
    }
}

void RegEx_Utility:: set_contents(string contents)
{
    _contents = contents;
}

/**
Node_Builder_Utility
*/
string Node_Builder_Utility:: read_file(const string fname)
{
    ifstream t(fname);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}
void Node_Builder_Utility:: set_pattern(string class_name)
{
    reset_pattern();
    _pattern = "<"+ class_name + ">([^]*)</" + class_name + ">";
}

void Node_Builder_Utility:: set_pattern_2_extract_var()
{
    reset_pattern();
    _pattern = ">([^]*)</";
}

void Node_Builder_Utility:: set_pattern_2_extract_lines()
{
    //cout<<"RESETTING.."<<endl;
    reset_pattern();
    //_pattern = "(.+)+"; // go until newline
    //_pattern = "([^]*)";
    //_pattern = "(.)*";
    _pattern = "?.*\n";
}


void Node_Builder_Utility:: reset_pattern()
{
    _pattern = "";
}

vector<string> Node_Builder_Utility:: parse_into_lines(string many_lines, int num)
{
    cout<<"SHOWING LINES:"<<endl;
    cout<<many_lines;
    vector<string> independent_lines;
    string delimiter = "\n";

    for (int i=0; i< num; i++)
    {
        independent_lines.push_back(many_lines.substr(0, many_lines.find(delimiter))) ;
        many_lines.erase(0, many_lines.find(delimiter) + delimiter.length());
    }
    return independent_lines;
}

/**
 Function to extract all class variables in 1 string
*/
string Node_Builder_Utility:: build_node_var_helper(string class_name)
{
    _parser.set_contents(_xml_file);
    set_pattern(class_name);
    string class_contents = _parser.extract_substring(_pattern);
    return class_contents;
}

/**
 Function to take in entire string variables from the helper, and parse them to individual ones
*/
vector<string> Node_Builder_Utility:: build_node_var(std::string class_name, int num_var)
{
    string class_variables_all = build_node_var_helper(class_name); // get all the variables for 1 class, in 1 string
    //vector<string> class_variables_split; // prepare to split the string into individual variables
    _parser.set_contents(class_variables_all);

    vector<string> class_variables_split = parse_into_lines(class_variables_all, num_var);
    string line, new_var;
    for(int i =0; i<num_var; i++)
    {
        //set_pattern_2_extract_lines();
        line = class_variables_split[i]; // get one line


        //cout<<"LINE EXTRACTED: "<< line;
        regex reg(_pattern);
        class_variables_all = regex_replace(class_variables_all, reg, "");
        //cout<<"\nNEW VARIABLES: "<<class_variables_all<<endl;
        _parser.set_contents(class_variables_all);
        set_pattern_2_extract_var();
        _parser.set_contents(line);
        new_var = _parser.extract_substring(_pattern);
        class_variables_split.push_back(new_var);
        //cout<<"\nNEW VARIABLE: " << new_var<<endl;
    }
    //cout<<"CONTENT: " << class_variables_split[0]<<endl;
    return class_variables_split;
}

/**
XML_Node Definitions: NONE
*/


/**
PaperSize Definitions
*/

/**
Area Definitions
*/

/**
BarCodeScan Definitions
*/

/**
NodeList Definitions
*/

void NodeList:: vec_insert(XML_Node* node)
{
    _nodeList.push_back(node);
}

int NodeList::get_size()
{
    return _nodeList.size();
}

void NodeList:: vec_print()
{
    for (int i = 0; i<get_size(); i++)
       _nodeList[i]->print_contents();
}


