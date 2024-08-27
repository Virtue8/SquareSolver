#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

const double EPSILON = 1e-10;

void CleanBuffer ();
bool IsZero (double eps);
bool CompareTwo (double k1, double k2);

#endif
