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

int Dispatcher(struct Coefficients coeff, struct Roots *roots);

void ManualMode ();

int SolveLinear (struct Coefficients coeff, struct Roots *roots);

int SolveSemiLinear (struct Coefficients coeff, struct Roots *roots);

int SolveSquare (struct Coefficients coeff, struct Roots *roots);

#endif
