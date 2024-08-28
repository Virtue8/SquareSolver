#ifndef SOLVE_FUNCS_HEADER
#define SOLVE_FUNCS_HEADER

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

#include "Utilities.h"
#include "InputOutput.h"

enum roots
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

struct Coefficients
{
    double a;
    double b;
    double c;
};

struct Roots
{
    double x1;
    double x2;
    int nRoots;
};

void Dispatcher (struct Coefficients coeff, struct Roots *roots);

void ManualMode ();

void SolveLinear (struct Coefficients coeff, struct Roots *roots);

void SolveSemiLinear (struct Coefficients coeff, struct Roots *roots);

void SolveSquare (struct Coefficients coeff, struct Roots *roots);

#endif
