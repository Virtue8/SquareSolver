#ifndef UTILITIES_CPP
#define UTILITIES_CPP

#include "../headers/Utilities.h"

void CleanBuffer ()
{
    int cleaner_char = 0;

    while ( (cleaner_char = getchar ()) != '\n' && cleaner_char != EOF) {}
}

//-----------------------------------------------------------------------

bool Skipper ()
{
    int skipper_char = 0;

    while ( (skipper_char = getchar ()) == ' ' || skipper_char == '\t') {}

    if (skipper_char == '\n' || skipper_char == EOF)
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------

bool IsZero (double value)
{
    return (fabs (value) <= EPSILON);
}

//-----------------------------------------------------------------------

bool CompareTwo (double k1, double k2)
{
    return (fabs (k1 - k2) <= EPSILON);
}


#endif
