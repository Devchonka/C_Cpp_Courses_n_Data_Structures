#include <iostream>
#include <unordered_map>
#include <map>

#include "Robot.h"
#include "rlutil.h"
#include "ConsoleColor.h"
#include "parse_xml.h"

using namespace std;
const string FNAME = "RobotData.xml";

void RobotTest();

void startCV(bool&, condition_variable&, mutex&);
void shared_execute(int, bool&, condition_variable&, mutex&, map<string, queue<command_struct>>&, Robot&);
void multitask_robot(bool&, condition_variable&, mutex&, map<string, queue<command_struct>>&, Robot&);

void build_string2enum_mapping(unordered_map<string, properties>*);

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
Function which each thread is executing.
*/
void shared_execute(int thread_ID, bool& ready, condition_variable& cv, mutex& mtx, \
                    map<string,queue<command_struct>>& arm2command, Robot& robot)
{
    unique_lock<mutex> lck(mtx);
    string arm_name = "A"+to_string(thread_ID);
    cout << blue << "Thread "<<arm_name << " waiting...\n";
    while(!ready)
    {
        cv.wait(lck);    // comment out this line
    }

    robot.setOffOn(arm2command[arm_name].front().offon.to_ulong());
    robot.setSpeed(arm2command[arm_name].front().speed.to_ulong());
    robot.setHorizontal(arm2command[arm_name].front().horizontal.to_ulong());
    robot.setVertical(arm2command[arm_name].front().vertical.to_ulong());
    robot.setTime(arm2command[arm_name].front().time.to_ulong());
    arm2command[arm_name].pop();
    robot.Execute();

    cout << "Thread " << arm_name << " executed." << endl;
}

/**
    Function that creates a smart array of threads, and calls the conditional variable to notify all threads.
    The function joins all threads at the end.
*/
void multitask_robot(bool& ready, condition_variable& cv, mutex& mtx, map<string, \
                     queue<command_struct>>& arm2command, Robot& robot)
{
    array<thread, 4> threads;
    for(unsigned i = 0; i<threads.size(); ++i)
    {
        threads[i] = thread(shared_execute, i+1, ref(ready), ref(cv), ref(mtx), ref(arm2command), ref(robot));
    }
    cout << yellow << "Threads ready to start execution!"<<endl;
    startCV(ready, cv, mtx);	// go!
    for(auto& th : threads)
    {
        th.join();
    }
    cout<<white<<endl;
}

void build_string2enum_mapping(unordered_map<string, properties>& string2enum)
{
    //string2enum.insert(make_pair("ZERO",ZERO));
    string2enum.insert(make_pair("Off",OFF));
    string2enum.insert(make_pair("On",ON));
    //string2enum.insert(make_pair("INVALID",INVALID));
    //string2enum.insert(make_pair("OK",OK));
    string2enum.insert(make_pair("Low",LOW));
    string2enum.insert(make_pair("High",HIGH));
    string2enum.insert(make_pair("Clockwise",CLOCKWISE));
    string2enum.insert(make_pair("CounterClockwise",COUNTERCLOCKWISE));
    string2enum.insert(make_pair("Up",UP));
    string2enum.insert(make_pair("Down",DOWN));
    //string2enum.insert(make_pair("MINTIME",MINTIME));
    //string2enum.insert(make_pair("MAXTIME",MAXTIME));
}

void print_map(unordered_map<string,properties>& myMap)
{
    for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << endl;
    }
}

void build_arm2command_mapping(map<string, queue<command_struct>>& arm2command, vector<queue<command_struct>>& command_queues)
{
    string arm_name;
    for(int i=0; i<4; i++)
    {
        arm_name = "A"+to_string((i+1));
        arm2command.insert(make_pair(arm_name, command_queues[i]));
    }
}

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
    for(auto i =0; i<command_nodes.size(); i++)
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
        temp_command.time = string2enum[temp_command_val];

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

    mutex mtx;
    bool ready = false;
    condition_variable cv;
    multitask_robot(ready, cv, mtx, arm2command, robot);


    //RobotTest();
    return 0;
}

void RobotTest()
{
    Robot robot;
    // invalid
    cout << ((robot.Execute() == OK) ? "OK\n" : "EROR\n");
    // valid
    robot.setOffOn(ON);
    robot.setSpeed(HIGH);
    robot.setHorizontal(COUNTERCLOCKWISE);
    robot.setVertical(UP);
    robot.setTime(128);
    cout << ((robot.Execute() == OK) ? "OK\n" : "EROR\n");
}
