#include "lexical_parser.h"

using namespace std;


string* read_entire_file(string fname_in)
{
    ifstream ifp;
    ifp.open(fname_in);
    stringstream sstext;
    sstext << ifp.rdbuf();
    string* pText = new string(sstext.str());
    ifp.close();
    return pText;
}

void Patient::print_rec()
{
    cout<< get<0>(_rec) << ", "<< get<1>(_rec) << ", "<< get<2>(_rec) << ", "\
        << get<3>(_rec) << ", "<< get<4>(_rec) << ", "<< get<5>(_rec) << ", "\
        << get<6>(_rec) << endl;
}



DataBase::DataBase(string* pText)
{
}
