#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

const int NO_ROOTS = 0;                                                  //no roots
const int ONE_ROOT = 1;                                                  //one root
const int TWO_ROOTS = 2;                                                 //two roots
const int INF_ROOTS = 8;                                                 //infinite number of roots (kinda infinity symbol but turned on 90 degrees lol)

int SolveLinear(double b, double c, double* x1);
int SolveSquare(double a, double b, double c, double* x1, double* x2);
int Dispatcher(double a, double b, double c, double *x1, double *x2);
int Input(double* a, double* b, double* c);
void Output(int nRoots, double x1, double x2);

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
        printf("SQUARE EQUATION SOLVER (V1) \nDolgopa City, 2024 \n");
        printf("All rights reserved.\n \n");
        printf("Enter coefficients for ax2+bx+c=0 equation ");
        printf("in the following format: a b c \n \n");
        scanf("%lg %lg %lg", a, b, c);
        printf("Program answer: \n \n");
        return 0;
     }

//----------------------------------------------------------------

int Dispatcher(double a, double b, double c, double *x1, double *x2)
{

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
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
            printf("Your equation is linear (x*b + c = 0).\n");
            return SolveLinear(b, c, x1);
        }
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
    *x1 = -c / b;
    return ONE_ROOT;
}

//------------------------------------------------------------------------

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    double Discriminant = b * b - 4 * a * c;

    if (Discriminant < 0)
    {
        return NO_ROOTS;
    }
    else
    {
        *x1 = (-b - sqrt(Discriminant)) / (2 * a);
        *x2 = (-b + sqrt(Discriminant)) / (2 * a);

        if (Discriminant == 0)
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
