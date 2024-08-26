#include "Header.h"

#ifndef IOD
#define IOD

void Input (struct Coefficients *coeff)
{
    assert (coeff != NULL);

    assert (isfinite (coeff->a) );
    assert (isfinite (coeff->b) );
    assert (isfinite (coeff->c) );

    printf ("Enter coefficients for ax^2+bx+c=0 equation ");
    printf ("in the following format: a b c \n \n");


    while (true)
    {
        if (scanf ("%lg %lg %lg", &coeff->a, &coeff->b, &coeff->c) == 3)
        {
            if (getchar() != '\n')
            {
                printf ("Wrong format of input, try again, i believe in you.\n");
                CleanBuffer ();
            }
            else
            {
                break;
            }
        }
        else
        {
            printf ("Wrong format of input, try again, i believe in you.\n");
            CleanBuffer ();
        }
    }
}

//-----------------------------------------------------------------------

int Dispatcher (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);

    assert (isfinite (coeff.a) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    if (IsZero (coeff.a) )
    {
        return SolveLinear (coeff, roots);
    }
    else if (IsZero (coeff.c) )
    {
        return SolveSemiLinear (coeff, roots);
    }
    else
    {
        return SolveSquare (coeff, roots);
    }
    return 0;
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
