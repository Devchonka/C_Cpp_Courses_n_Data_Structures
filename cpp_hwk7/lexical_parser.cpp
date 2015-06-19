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



void DataBase::build_dataBase(std::string* pText)
{
    // build a vector of patient blocks that contain all patient info
    vector<string> patterns = {"name", "age", "gender", "bloodtype", "maritalstatus", "income", "dependents"};
    RegEx_Utility regex_util_nodes(pText);

    //collect barcodes
    bool barcode = true;
    vector<string> patient_code_strings = regex_util_nodes.extract_substring("patient", barcode);

    //collect patient data
    barcode = false;
    vector<string> patient_nodes = regex_util_nodes.extract_substring("patient", barcode);
    array<string,7> temp_vals;
    // for all the patient nodes blocks, parse each node and build Patient objects
    for(unsigned i =0; i<patient_nodes.size(); i++)
    {
        RegEx_Utility regex_util_patients(&patient_nodes[i]);
        for(int j=0; j<temp_vals.size(); j++)
        {
            temp_vals[j]= regex_util_patients.extract_substring(patterns[j], barcode)[0];
        }
        PATIENT_REC temp_tuple = make_tuple(temp_vals[0], (unsigned short) atoi(temp_vals[1].c_str()), \
                                            temp_vals[2][0], temp_vals[3], temp_vals[4], \
                                            (unsigned) atoi(temp_vals[5].c_str()), \
                                            (unsigned short) atoi(temp_vals[6].c_str()));
        Patient* pat = new Patient(temp_tuple);
        cout<< patient_code_strings[i]<<endl;
        //_barcode2Patient.insert(make_pair(atoi(patient_code_strings[i].c_str()), pat));
    }

    delete(pText);
}

DataBase::~DataBase()
{
    for(auto it = _barcode2Patient.begin(); it != _barcode2Patient.end(); it++) {
     delete(it->second);
    }



}

vector<string> RegEx_Utility::extract_substring(string class_name, bool barcode)
{

    string pattern = (barcode)? "</"+ class_name + ">([\\s\\S]*?)<" + class_name + ">": \
                                "<"+ class_name + ">([\\s\\S]*?)</" + class_name + ">";
    regex r(pattern);
    vector<string> results_str;
    smatch results;
    for(sregex_iterator i = sregex_iterator(_contents->begin(), _contents->end(), r);
            i != std::sregex_iterator();
            ++i)
    {
        std::smatch m = *i;
        //cout << m[1] << endl;
        results_str.push_back((*i)[1]);
    }
    return results_str;
}
