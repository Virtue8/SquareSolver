#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

// #define DEBUG

enum roots
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

const double EPSILON = 1e-10;

int SolveLinear(double b, double c, double* x1);
int SolveSquare(double a, double b, double c, double* x1, double* x2);

int Dispatcher(double a, double b, double c, double *x1, double *x2);

int Input(double* a, double* b, double* c);
void Output(int nRoots, double x1, double x2);

void CleanBuffer();

bool IsZero(double eps);
bool CompareTwo(double k1, double k2);

int UnitTester (double a, double b, double c, double x1_exp, double x2_exp, int nRoots_exp);
void AllUnitsTester();

//-----------------------------------------------------------------------

int main()
{
#ifdef DEBUG
    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    Input(&a, &b, &c);
    int nRoots = Dispatcher(a, b, c, &x1, &x2);
    Output(nRoots, x1, x2);

#else

    AllUnitsTester();

#endif

    return 0;
}

//-----------------------------------------------------------------------

int Input(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a != b && a != c && b != c);

    printf("#######################\n"
           "#####     ######     ##\n"
           "####   ########   #####\n"
           "#####   ########   ####\n"
           "######   ########   ###\n"
           "###     ######     ####\n"
           "#######################\n\n");

    printf("SQUARE EQUATION SOLVER (V1) \nDolgopa City, 2024 \n\n");
    printf("All rights reserved.\n \n");
    printf("Enter coefficients for ax^2+bx+c=0 equation ");
    printf("in the following format: a b c \n \n");

    while(scanf("%lg %lg %lg", a, b, c) != 3)
    {
        CleanBuffer();
        printf("Wrong format of input, try again, i believe in you.\n");

    }

    return 0;
}

//-----------------------------------------------------------------------

int Dispatcher(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);
    assert(x2 != NULL);
    assert(x1 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    if (IsZero(a))
    {
        printf("Your equation is linear (b*x + c = 0).\n");
        return SolveLinear(b, c, x1);
    }
    else
    {
        printf("Your equation is square (a*x^2 + b*x + c = 0).\n");
        return SolveSquare(a, b, c, x1, x2);
    }
}

//-----------------------------------------------------------------------

int SolveLinear(double b, double c, double* x1)
{
    assert(x1 != NULL);
    assert(isfinite(b));
    assert(isfinite(c));

    if (IsZero(b))
    {
        if (IsZero(c))
        {
            return INF_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    else
    {
        *x1 = -c / b;
        return ONE_ROOT;
    }

}

//-----------------------------------------------------------------------

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != x2);
    assert(x2 != NULL);
    assert(x1 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double Discriminant = b * b - 4 * a * c;

    if (Discriminant < -EPSILON)
    {
        return NO_ROOTS;
    }
    else
    {
        *x1 = (-b - sqrt(Discriminant)) / (2 * a);
        *x2 = (-b + sqrt(Discriminant)) / (2 * a);

        if (IsZero(Discriminant) == 1)
        {
            return ONE_ROOT;
        }
        else
        {
            return TWO_ROOTS;
        }
    }
}

//-----------------------------------------------------------------------

void Output(int nRoots, double x1, double x2)
{
    assert(isfinite(x1));
    assert(isfinite(x2));

    printf("\nProgram answer: \n\n");

    switch (nRoots)
        {
            case NO_ROOTS: printf("There is no real roots :(");
                           break;

            case ONE_ROOT: printf("The only root is %lg.", x1);
                           break;

            case TWO_ROOTS: printf("Roots are %lg and %lg.", x1, x2);
                            break;

            case INF_ROOTS: printf("Any root.");
                            break;

            default: printf("Error");
                     break;
        }
}

//-----------------------------------------------------------------------

bool IsZero(double value)
{
    return (fabs(value) <= EPSILON);
}

//-----------------------------------------------------------------------

bool CompareTwo(double k1, double k2)
{
    return (fabs(k1 - k2) <= EPSILON);
}

//-----------------------------------------------------------------------

void CleanBuffer()
{
    while (getchar() != '\n') {}
}

//-----------------------------------------------------------------------

void AllUnitsTester()
{
    int counter = 0;

    double x1_exp = -3;
    double x2_exp = 1;
    int nRoots_exp = 2;

    double a = 1;
    double b = 2;
    double c = -3;

    counter += UnitTester(a, b, c, x1_exp, x2_exp, nRoots_exp);

    x1_exp = 5;
    x2_exp = 1;
    nRoots_exp = 2;

    a = 1;
    b = -5;
    c = 4;

    counter += UnitTester(a, b, c, x1_exp, x2_exp, nRoots_exp);

    x1_exp = 1;
    x2_exp = 1;
    nRoots_exp = 1;

    a = 1;
    b = -2;
    c = 1;

    counter += UnitTester(a, b, c, x1_exp, x2_exp, nRoots_exp);

    printf("Total: %d correct, %d incorrect.\n", counter, 3 - counter);
}

//------------------------------------------------------------------------------

int UnitTester (double a, double b, double c, double x1_exp, double x2_exp, int nRoots_exp)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(x1_exp));
    assert(isfinite(x2_exp));

    double x1 = 0;
    double x2 = 0;

    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    if (CompareTwo(nRoots, nRoots_exp) == false || CompareTwo(x1, x1_exp) == false || CompareTwo(x2, x2_exp) == false)
    {
        printf("-- Incorrect execution: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n"
               "Expected: x1 = %lg, x2 = %lg, nRoots = %d.\n\n", a, b, c, x1, x2, nRoots, x1_exp, x2_exp, nRoots_exp);
        return 0;
    }
    else
    {
        printf("++ Correct execution.\n\n");
        return 1;
    }
}
