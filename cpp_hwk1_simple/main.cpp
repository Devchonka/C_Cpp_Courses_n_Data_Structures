/**
    Elena Menyaylenko
    04/16/2015 C++ Hwk 0
    CodeBlocks 13.12 was the IDE used, Unix OS

    For reference: Most space agencies have several types of thrusters. Considered in this example are:
    1) AOC - Attitude and Orbit Control
    2) MST - Main Satellite Thruster
    3) Hall - Electric Propulsion Hall Thrusters

    These different types of biprop and electrical propulsion thrusters are solely on a bang-bang control system actuated
    by valves. Therefore the given values are based on an average spec value and a tolerance coming from the manufacturer's
    reference performance testing.

    The algorithm below does the following:
    1) in main() the user may choose the input units of a thrust vector (Newtons or Lbf) to test the program
    2) in main() the user may also choose the input prop type (AOC, MST, or Hall)
    3) a vector of arbitrary values of created given the performance values of the selected thruster
    4) based on the selection, either a lbf_thrust or a newton_thrust object is created
        - that object holds the input vector values based on the selection
        - type of thruster
        - unit
    5) the user will have the desired object which holds the thrust values in the desired units

    Note that there is no user interaction here since this is simulation a flight software patch.

*/


#include <iostream>
#include <vector>
#include <string>
#include<cstring>

#include "thrust_classes.h"


using namespace std;

vector<double> get_input_vec(propType, const string, const string, double&);

int main()
{
    /*
    Note that the selections below are not checking spelling since it's assumed we're getting this from software, not user.
    The units coming from flight software are set here as following :
    */
    propType input_prop_type = propType::HALL; // May Be: AOC, MST, or HALL
    const string input_prop_unit = "Newton"; // May be Newton or Lbf
    const string desired_prop_unit = "Lbf"; // May be Newton or Lbf
    /*
        Create the simulated input values asked for by user, and pass on the output values to go into the correct object
    */
    double conv_factor = 1.0;
    vector<double> input_vec = get_input_vec(input_prop_type, desired_prop_unit, input_prop_unit, conv_factor);
    /*
        Find out which object to create to pass on
    */
    if(desired_prop_unit=="Newton")
    {
        Newton_thrust output_object(input_vec, conv_factor);
        cout << "The input values were chosen to be in " << input_prop_unit << " and is shown here: " << endl;
        output_object.show_original_thrust();
        cout <<"\nThe desired values are chosen to be in " << desired_prop_unit << " and are shown here: "<< endl;
        output_object.show_thrust();
    }
    else
    {
        Lbf_thrust output_object(input_vec, conv_factor);
        cout << "The input values were chosen to be in " << input_prop_unit << " and is shown here: " << endl;
        output_object.show_original_thrust();
        cout <<"\nThe desired values are chosen to be in " << desired_prop_unit << " and are shown here: "<< endl;
        output_object.show_thrust();
    }
    cout <<endl;
    return 0;
}

/*
    This function creates the input vector and changes by reference the conversion factor for the desired conversion.
*/
vector<double> get_input_vec(propType input_prop_type, const string desired_prop_unit, const string input_prop_unit, double& conv_factor)
{
    double conversion_factor_input =0;
    double AvgTable_N[ static_cast<int>(propType::THRUSTER_TYPE_COUNT) ]  =
    {
        22.2, 458.0, 1.083
    } ;
    double ToleranceTable_N[ static_cast<int>(propType::THRUSTER_TYPE_COUNT) ]  =
    {
        1.1, 31.0, 0.005
    } ;
    string ThrusterTypeTable[ static_cast<int>(propType::THRUSTER_TYPE_COUNT) ]  =
    {
        "Attitude and Orbit Control", "Main Satellite Thruster", "Electric Propulsion Hall Thruster"
    } ;
    double lbf2N = 4.44820;
    double N2lbf = 0.22481;
    if(input_prop_unit == "Newton")
    {
        conversion_factor_input =1.0;
        if (desired_prop_unit != input_prop_unit)
            conv_factor = N2lbf;
    }
    else
        conversion_factor_input = N2lbf;
        {
            if (desired_prop_unit != input_prop_unit)
            conv_factor = lbf2N;
        }

    vector<double> input_vec;
    double input_min_val_N = AvgTable_N[static_cast<int>(input_prop_type)] - ToleranceTable_N[static_cast<int>(input_prop_type)];
    double input_max_val_N = AvgTable_N[static_cast<int>(input_prop_type)] - ToleranceTable_N[static_cast<int>(input_prop_type)];
    cout << "The input values are for the thruster type: " << ThrusterTypeTable[static_cast<int>(input_prop_type)]<<endl<<endl;;

    for(int i =0; i<5; i++)
    {
        double rand_num = (input_min_val_N + rand() % int(input_min_val_N)) * conversion_factor_input;
        input_vec.push_back(rand_num);
    }
    cout << endl;

    return input_vec;
}
