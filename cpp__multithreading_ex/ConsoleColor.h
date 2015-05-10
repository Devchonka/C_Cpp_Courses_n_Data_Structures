#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H
#pragma once
#include <iostream>
#include "rlutil.h"

using namespace std;

inline ostream& blue(ostream &s)
{
    rlutil::setColor(1);
    return s;
}

inline ostream& red(ostream &s)
{
    rlutil::setColor(4);
    return s;
}

inline ostream& green(ostream &s)
{
    rlutil::setColor(2);
    return s;
}

inline ostream& yellow(ostream &s)
{
    rlutil::setColor(14);
    return s;
}


inline ostream& white(ostream &s)
{
    rlutil::setColor(15);
    return s;
}


#endif // CONSOLE_COLOR_H
