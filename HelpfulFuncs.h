#include "Header.h"

#ifndef HELPER
#define HELPER

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

    while (ch = getchar () != '\n' && ch != EOF)
    {

    }
}

#endif
