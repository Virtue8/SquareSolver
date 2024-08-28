#ifndef TEST_HEADER
#define TEST_HEADER

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

#include "SolveFuncs.h"
#include "Utilities.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_LINE(COLOR, ...) \
printf ("%s", COLOR);\
printf (__VA_ARGS__);\
printf ("%s", RESET)

struct UnitSample
{
    struct Coefficients coeff;
    struct Roots roots_exp;
    struct Roots roots;

    int TestNumber;
};

void TestMode ();

int UnitTester (struct UnitSample test);

#endif
