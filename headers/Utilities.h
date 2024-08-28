#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

const double EPSILON = 1e-10;

void CleanBuffer ();

bool Skipper ();

bool IsZero (const double eps);

bool CompareTwo (const double k1, const double k2);

#endif
