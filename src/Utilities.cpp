#ifndef UTILITIES_CPP
#define UTILITIES_CPP

#include "../headers/Utilities.h"

bool IsZero (double value)
{
    return (fabs (value) <= EPSILON);
}

//-----------------------------------------------------------------------

bool CompareTwo (double k1, double k2)
{
    return (fabs (k1 - k2) <= EPSILON);
}

//-----------------------------------------------------------------------

void CleanBuffer ()
{
    char ch = '\0';

    while (ch = getchar () != '\n' && ch != EOF) {}
}

#endif
