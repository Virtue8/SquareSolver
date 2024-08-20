#include <stdio.h>
#include <math.h>
#include <TXLib.h>

const int SS_INF_ROOTS = 8;

int SolveSquare(double a, double b, double c, double* x1, double* x2);

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    printf("Square equation solver \n");
    printf("Enter coefficients in the following format: a b c \n");
    scanf("%lg %lg %lg", &a, &b, &c);
    printf("Answer: ");

    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    switch (nRoots)
    {
        case 0: printf("No roots :(");
            break;

    case 1: printf("The only root is %lg.", x1);
            break;

    case 2: printf("Roots are %lg and %lg.", x1, x2);
            break;

    case SS_INF_ROOTS: printf("Any root.");
                       break;

    default: printf("Error");
             break;

    }

return 0;
}

// TODO dispetcher   linear square

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    if (a == 0 && b == 0 && c != 0)
    {
        return 0;
    }
    else if (a == 0 && b == 0 && c == 0)
    {
        return SS_INF_ROOTS;
    }
    else if (a == 0 && b != 0 && c != 0)
    {
        return 1;
    }
        else
        {
            double D = b*b - 4*a*c;

            if (D < 0)
            {
                return 0;
            }

            else if (D == 0)
            {
                return 1;
            }

                else
                {
                    return 2;
                }

            *x1 = 0.5*(-b+sqrt(D));
            *x2 = 0.5*(-b-sqrt(D));

        }
}
