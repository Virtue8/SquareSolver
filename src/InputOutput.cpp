#ifndef INPUT_OUTPUT_CPP
#define INPUT_OUTPUT_CPP

#include "../headers/InputOutput.h"

void Input (struct Coefficients *coeff)
{
    assert (coeff != NULL);

    assert (isfinite (coeff->a) );
    assert (isfinite (coeff->b) );
    assert (isfinite (coeff->c) );

    printf ("Enter coefficients for ax^2+bx+c=0 equation ");
    printf ("in the following format: a b c \n \n");

    int print_param = 0;

    while (true)
    {
        if (scanf ("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c) == 3)
        {
            if (getchar() != '\n')
            {
                print_param = 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            print_param = 1;
        }

        if (print_param == 1)
        {
            printf ("Wrong format of input, try again, i believe in you.\n");
            CleanBuffer ();
        }
        else
        {
            break;
        }
    }
}

//-----------------------------------------------------------------------

void Output (struct Roots roots)
{
    assert (isfinite (roots.x1) );
    assert (isfinite (roots.x2) );

    printf ("\nProgram answer: \n\n");

    switch (roots.nRoots)
    {
        case NO_ROOTS  : printf ("There is no real roots :(");
                         break;

        case ONE_ROOT  : printf ("The only root is %lg.", roots.x1);
                         break;

        case TWO_ROOTS : printf ("Roots are %lg and %lg.", roots.x1, roots.x2);
                         break;

        case INF_ROOTS : printf ("Any root.");
                         break;

        default        : printf ("Error");
                         break;
    }
}

#endif
