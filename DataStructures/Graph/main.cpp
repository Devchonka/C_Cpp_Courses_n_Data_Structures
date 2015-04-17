/**

An implementation for directed graph. Input dataset info below.

Directed graph (each unordered pair of nodes is saved once): roadNet-CA.txt
California road network
Nodes: 1965206 Edges: 5533214
Column 1: From Node
Column 2: To Node

Dataset obtained from Stanford SNAP: http://snap.stanford.edu/data/

Dataset info: http://snap.stanford.edu/data/roadNet-CA.html

*/


#include <iostream>

using namespace std;
const string FNAME = "roadNet-CA.txt";
bool readData(vector<int>*, int&);


int main()
{
   vector<int>* testVec = new vector<int>;
    int arSize =0;
    readData(testVec, arSize);
    cout<<arSize<<endl;
    delete testVec;
    return 0;
}

bool readData(vector<Athlete*>* testVec, int& hashSi)
{
    ifstream fileHandle;
    fileHandle.open(FNAME);

    bool ableToPopulate = fileHandle.good();

    if (ableToPopulate)
    {
        string line =" ";
        int fromNode =0, toNode =0;
        while (getline(fileHandle, line))
        {
            parseInput(line,name,country,sport,date,age,medals,year);
            Sport winStats(country,year,sport,date);
            Athlete* athlete = new Athlete(name, age, medals, winStats);
            testVec->push_back(athlete);
            numObjects++;
        }
        fileHandle.close();
        hashSi = hashSize(numObjects);
    }
    else
        printErrorMsg(Error::BAD_IFILE);
    return ableToPopulate;
}
