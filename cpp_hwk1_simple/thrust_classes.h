#ifndef THRUST_CLASSES_H
#define THRUST_CLASSES_H

enum class propType
{
    AOC, MST, HALL, THRUSTER_TYPE_COUNT
};

/**
    This is the generic thrust class from which Newton_thrust and Lbf_thrust will inherit.
    It only contains the original vector of values so that the derived classes may reference it if needed.
*/
class generic_thrust
{
protected:
    std::vector<double> _input_vec;

public:
    generic_thrust(std::vector<double> input_vec): _input_vec(input_vec) {}; // constructor
    virtual ~generic_thrust() {};
};

/**
    The Newton_thrust class gives the right name for the adjusted input vector.
    It contains the converted vector in the correct values as well as the original values.
    It can give out a copy of the thrust values as well as print the original or corrected values.
*/
class Newton_thrust : public generic_thrust
{
public:
    private:
    double _conv_factor;
    std::vector<double> _converted_vec;
public:
    std::vector<double> get_thrust()
    {
        return _converted_vec;
    }
    void show_thrust()
    {
        for(int i =0; i<5; i++)
            std::cout<< _converted_vec[i]<<" ";
    }
    void show_original_thrust()
    {
        for(int i =0; i<5; i++)
            std::cout<< _input_vec[i]<<" ";
    }

    Newton_thrust(std::vector<double> input_vec, double conv_factor): generic_thrust(input_vec), _conv_factor(conv_factor)
    {
        for (int i =0; i <_input_vec.size(); i++)
            _converted_vec.push_back(_input_vec[i] * _conv_factor);
    }
    ~Newton_thrust() {};

};

/**
    The Lbf_thrust class gives the right name for the adjusted input vector.
    It contains the converted vector in the correct values as well as the original values.
    It can give out a copy of the thrust values as well as print the original or corrected values.
*/
class Lbf_thrust : public generic_thrust
{
private:
    double _conv_factor;
    std::vector<double> _converted_vec;
public:
    std::vector<double> get_thrust()
    {
        return _converted_vec;
    }
    void show_thrust()
    {
        for(int i =0; i<5; i++)
            std::cout<< _converted_vec[i]<<" ";
    }
    void show_original_thrust()
    {
        for(int i =0; i<5; i++)
            std::cout<< _input_vec[i]<<" ";
    }

    Lbf_thrust(std::vector<double> input_vec, double conv_factor): generic_thrust(input_vec), _conv_factor(conv_factor)
    {
        for (int i =0; i <_input_vec.size(); i++)
            _converted_vec.push_back(_input_vec[i] * _conv_factor);
    }
    ~Lbf_thrust() {};
};
#endif
