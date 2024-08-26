#ifndef HEADER_H
#define HEADER_H

#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define REDLINE(...) \
printf("%s", RED);\
printf(__VA_ARGS__);\
printf("%s", RESET)

#define GREENLINE(...) \
printf("%s", GREEN);\
printf(__VA_ARGS__);\
printf("%s", RESET)

enum modes
{
    MANUAL = 'm',
    TEST = 't'
};

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

struct UnitSample
{
    struct Coefficients coeff;
    struct Roots roots_exp;
    struct Roots roots;

    int TestNumber;
};

const double EPSILON = 1e-10;

int SolveLinear (struct Coefficients coeff, struct Roots *roots);
int SolveSemiLinear (struct Coefficients coeff, struct Roots *roots);
int SolveSquare (struct Coefficients coeff, struct Roots *roots);
int Dispatcher(struct Coefficients coeff, struct Roots *roots);

void Menu ();
void ManualMode ();
void TestMode ();
void ModeSwitcher ();
char GetMode ();

void Input (struct Coefficients *coeff);
void Output (struct Roots roots);

void CleanBuffer ();

bool IsZero (double eps);
bool CompareTwo (double k1, double k2);

int UnitTester (struct UnitSample test);

#endif
