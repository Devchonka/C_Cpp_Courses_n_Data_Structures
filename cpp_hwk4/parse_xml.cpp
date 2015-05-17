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
        //cout << m[1] << endl;
        results_str.push_back((*i)[1]);
    }
    return results_str;
}
