#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

// wrong coef
// doxygen

const int NO_ROOTS = 0;                                                  //no roots
const int ONE_ROOT = 1;                                                  //one root
const int TWO_ROOTS = 2;                                                 //two roots
const int INF_ROOTS = 8;                                                 //inf number of roots (kinda inf symbol but turned on 90 degrees lol)
const double EPSILON = 1e-10;

int SolveLinear(double b, double c, double* x1);
int SolveSquare(double a, double b, double c, double* x1, double* x2);
int Dispatcher(double a, double b, double c, double *x1, double *x2);
int Input(double* a, double* b, double* c);
void Output(int nRoots, double x1, double x2);
bool iszero(double eps);

//-----------------------------------------------------------------------

int main()
{
    double a = 0;                                                        //coefficients and roots initialization
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;

    Input(&a, &b, &c);
    int nRoots = Dispatcher(a, b, c, &x1, &x2);
    Output(nRoots, x1, x2);

    return 0;
}

//----------------------------------------------------------------

int Input(double* a, double* b, double* c)
{
    printf("#######################\n"
           "#####     ######     ##\n"
           "####  #########  ######\n"
           "#####    #######    ###\n"
           "#######  #########  ###\n"
           "###     ######     ####\n"
           "#######################\n\n");

    printf("SQUARE EQUATION SOLVER (V1) \nDolgopa City, 2024 \n\n");
    printf("All rights reserved.\n \n");
    printf("Enter coefficients for ax^2+bx+c=0 equation ");
    printf("in the following format: a b c \n \n");

    while(scanf("%lg %lg %lg", a, b, c) != 3)
    {
        while (getchar() != '\n')
        {
        continue;
        }
        printf("Wrong format of input, try again, i believe in you.\n");

    }

    return 0;
}

//----------------------------------------------------------------

int Dispatcher(double a, double b, double c, double *x1, double *x2)
{
    assert(x1 != x2);
    assert(x2 != 0);
    assert(x1 != 0);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(*x1));
    assert(isfinite(*x2));

    if (iszero(a))
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

//----------------------------------------------------------------

int SolveLinear(double b, double c, double* x1)
{
    assert(x1 != 0);
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(*x1));

    if (iszero(b))
    {
        if (iszero(c))
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

//------------------------------------------------------------------------

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != x2);
    assert(x2 != 0);
    assert(x1 != 0);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(*x1));
    assert(isfinite(*x2));

    double Discriminant = b * b - 4 * a * c;

    if (Discriminant < -EPSILON)
    {
        return NO_ROOTS;
    }
    else
    {
        *x1 = (-b - sqrt(Discriminant)) / (2 * a);
        *x2 = (-b + sqrt(Discriminant)) / (2 * a);

        if (iszero(Discriminant) == 1)
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
    assert(x1 != x2);
    assert(x2 != 0);
    assert(x1 != 0);
    assert(isfinite(nRoots));
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

bool iszero(double eps)
{
    return (fabs(eps) <= EPSILON);
}
