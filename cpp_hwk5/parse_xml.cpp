#include "parse_xml.h"

using namespace std;

string read_file(const string fname)
{
    ifstream t(fname);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

vector<string> RegEx_Utility::extract_substring(string class_name)
{
    string pattern = "<"+ class_name + ">([\\s\\S]*?)</" + class_name + ">";
    regex r(pattern);
    vector<string> results_str;
    smatch results;
    for(sregex_iterator i = sregex_iterator(_contents.begin(), _contents.end(), r);
            i != std::sregex_iterator();
            ++i)
    {
        std::smatch m = *i;
        // cout << m[1] << endl;
        results_str.push_back((*i)[1]);
    }
    return results_str;
}

void Location_Keeper::create_location_nodes()
{
    RegEx_Utility regex_util(read_file(_fname));
    std::vector<std::string> _location_strings = regex_util.extract_substring("Location");
    const int num_locations = _location_strings.size();
    _location_nodes.resize(num_locations);
    string temp;
    for(int loc_count =0; loc_count< num_locations; loc_count++)
    {
        regex_util.set_contents(_location_strings[loc_count]);
        for(unsigned field_count =0; field_count<_xml_keywords.size(); field_count++)
        {
            temp = regex_util.extract_substring(_xml_keywords[field_count])[0];
            if(field_count<4)
            {
                _location_nodes[loc_count].add_contact_info(temp);
            }
            else if(field_count ==4)
            {
                _location_nodes[loc_count].set_lati(stod(temp));
            }
            else
            {
                _location_nodes[loc_count].set_longi(stod(temp));
            }
        }
    }
}

void Location_Keeper::print_location_nodes()
{
    for(Location_Node node: _location_nodes)
    {
        node.print_node();
    }
}
