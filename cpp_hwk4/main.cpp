/**
    Hwk 4. Multithreading with 4 robot arms.
    Regex.
    Maps and Console Color.
*/

#include <iostream>
#include <unordered_map>
#include <map>

#include "Robot.h"
#include "rlutil.h"
#include "ConsoleColor.h"
#include "parse_xml.h"

using namespace std;
const string FNAME = "RobotData.xml";

void startCV(bool&, condition_variable&, mutex&);
void shared_execute(int, bool&,  mutex&, mutex&, condition_variable&, condition_variable&, \
                    map<string, queue<command_struct>>&, Robot&);
void multitask_robot(map<string, queue<command_struct>>&, Robot&);

void build_string2enum_mapping(unordered_map<string, properties>*);
void build_arm2command_mapping(map<string, queue<command_struct>>&,vector<queue<command_struct>>&);
vector<queue<command_struct>> extract_commands(string);

/**
    Function that starts the conditional variable.
*/
void startCV(bool& ready, condition_variable& cv, mutex& mtx)
{
    unique_lock<mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}


/**
Function which each thread is executing on the shared robot.
*/
void shared_execute(int thread_ID, bool& ready, mutex& start_mu, mutex& exec_mu, condition_variable& start_cv, \
                    condition_variable& exec_cv, map<string,queue<command_struct>>& arm2command, Robot& robot)
{
    unique_lock<mutex> start_lck(start_mu);
    string arm_name = "A"+to_string(thread_ID);
    cout << blue << "Thread "<<arm_name << " waiting...\n";
    while(!ready)
    {
        start_cv.wait(start_lck);    // comment out this line
    }
    //lck.unlock();

    unique_lock<mutex> exec_lck(exec_mu);
    //while(true)
    //{
    if(!arm2command[arm_name].empty())
    {
        robot.setOffOn(arm2command[arm_name].front().offon.to_ulong());
        robot.setSpeed(arm2command[arm_name].front().speed.to_ulong());
        robot.setHorizontal(arm2command[arm_name].front().horizontal.to_ulong());
        robot.setVertical(arm2command[arm_name].front().vertical.to_ulong());
        robot.setTime(arm2command[arm_name].front().time.to_ulong());
        arm2command[arm_name].pop();
        cout << ((robot.Execute() == OK) ? "OK\n" : "ERROR\n");
        //robot.Execute(); // does the sleep_for command
        cout << "Thread " << arm_name << " executed." << endl;
        exec_lck.unlock();
        exec_cv.notify_all();
    }
    else
    {
        exec_lck.unlock();
    }
    //}
}
/**
    Function that creates a smart array of threads, and calls the conditional variable to notify all threads.
    The function joins all threads at the end.
*/
void multitask_robot(map<string, queue<command_struct>>& arm2command, Robot& robot)
{
    condition_variable start_cv;
    condition_variable exec_cv;
    mutex start_mu;
    mutex exec_mu;
    bool ready = false;
    array<thread, 4> threads;
    for(unsigned i = 0; i<threads.size(); i++)
    {
        threads[i] = thread(shared_execute, i+1, ref(ready), ref(start_mu), ref(exec_mu), ref(start_cv), \
                            ref(exec_cv), ref(arm2command), ref(robot));
    }
    cout << yellow << "Threads ready to start execution!"<<endl;
    startCV(ready, start_cv, start_mu);	// go!
    for(auto& th : threads)
    {
        th.join();
    }
    cout<<white<<endl;
}
/**
    Function to help parse XML file notation directly to enum notation.
*/
void build_string2enum_mapping(unordered_map<string, properties>& string2enum)
{
    string2enum.insert(make_pair("Off",OFF));
    string2enum.insert(make_pair("On",ON));
    string2enum.insert(make_pair("Low",LOW));
    string2enum.insert(make_pair("High",HIGH));
    string2enum.insert(make_pair("Clockwise",CLOCKWISE));
    string2enum.insert(make_pair("CounterClockwise",COUNTERCLOCKWISE));
    string2enum.insert(make_pair("Up",UP));
    string2enum.insert(make_pair("Down",DOWN));
}
/**
    Function to test unordered map created.
*/
void print_map(unordered_map<string,properties>& myMap)
{
    for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << endl;
    }
}
/**
    Function to build the mapping from arm_name string to the command struct which came from parse XML file.
*/
void build_arm2command_mapping(map<string, queue<command_struct>>& arm2command, vector<queue<command_struct>>& command_queues)
{
    string arm_name;
    for(int i=0; i<4; i++)
    {
        arm_name = "A"+to_string((i+1));
        arm2command.insert(make_pair(arm_name, command_queues[i]));
    }
}
/**
    Function to extract commands from the file and create a container of several queues of command structs,
    one per robot arm (thread).
*/
vector<queue<command_struct>> extract_commands(string fname)
{
    vector<queue<command_struct>> command_queues(4);
    vector<string> patterns = {"offon", "speed", "horizontal", "vertical", "time"};
    RegEx_Utility regex_util_nodes(read_file(fname));
    vector<string> command_nodes = regex_util_nodes.extract_substring("command");
    // Create a map of XML strings to ENUMS in robot for Command
    unordered_map<string, properties> string2enum;
    build_string2enum_mapping(string2enum);
    command_struct temp_command;
    string temp_command_val;
    // for all the command nodes, parse each node and build Command object
    for(unsigned i =0; i<command_nodes.size(); i++)
    {
        RegEx_Utility regex_util_commands(command_nodes[i]);
        string arm_number = regex_util_commands.extract_substring("robot")[0];
        // extract the rest of the values from that node
        temp_command_val= regex_util_commands.extract_substring(patterns[0])[0];
        temp_command.offon = string2enum[temp_command_val];
        temp_command.errorcode = OK; // Ok since file validated
        temp_command_val= regex_util_commands.extract_substring(patterns[1])[0];
        temp_command.speed = string2enum[temp_command_val];
        temp_command_val= regex_util_commands.extract_substring(patterns[2])[0];
        temp_command.horizontal = string2enum[temp_command_val];
        temp_command_val= regex_util_commands.extract_substring(patterns[3])[0];
        temp_command.vertical = string2enum[temp_command_val];
        temp_command_val= regex_util_commands.extract_substring(patterns[4])[0];
        temp_command.time = (bitset<8>)(atoi(temp_command_val.c_str()));
        command_queues[arm_number[1]-'0'-1].push(temp_command);
    }
    return command_queues;
}
int main()
{
    //parse xml file to build several queues of commands
    vector<queue<command_struct>> command_queues = extract_commands(FNAME);
    //create map from arm number to its queue of commands
    map<string, queue<command_struct>> arm2command;
    build_arm2command_mapping(arm2command, command_queues);
    Robot robot;
    multitask_robot(arm2command, robot);
    return 0;
}
