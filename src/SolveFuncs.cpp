#ifndef SOLVE_FUNCS_CPP
#define SOLVE_FUNCS_CPP

#include "../headers/SolveFuncs.h"

void ManualMode ()
{
    Coefficients coeff = {};
    Roots roots = {};

    printf ("\n**Manual Mode**\n\n");

    Input (&coeff);
    roots.nRoots = Dispatcher (coeff, &roots);
    Output (roots);
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

int SolveSemiLinear(struct Coefficients coeff, struct Roots *roots)
{
    roots->x1 = -coeff.b / coeff.a;
    return TWO_ROOTS;
}

//-----------------------------------------------------------------------

int SolveLinear (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    if (IsZero (coeff.b) )
    {
        if (IsZero (coeff.c) )
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
        roots->x1 = -coeff.c / coeff.b;
        return ONE_ROOT;
    }
}

//-----------------------------------------------------------------------

int SolveSquare (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);
    assert (&coeff != NULL);
    assert (isfinite (roots->x1) );
    assert (isfinite (roots->x2) );
    assert (isfinite (coeff.a) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    double Discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;

    if (Discriminant < -EPSILON)
    {
        return NO_ROOTS;
    }
    else
    {
        Discriminant = sqrt(Discriminant);

        roots->x1 = (-coeff.b - Discriminant) / (2 * coeff.a);
        roots->x2 = (-coeff.b + Discriminant) / (2 * coeff.a);

        if (IsZero (Discriminant) == true)
        {
            return ONE_ROOT;
        }
        else
        {
            return TWO_ROOTS;
        }
    }
}

#endif
