#ifndef SOLVE_FUNCS_CPP
#define SOLVE_FUNCS_CPP

#include "../headers/SolveFuncs.h"

void ManualMode ()
{
    Coefficients coeff = {};
    Roots roots = {};

    printf ("\n**Manual Mode**\n\n");

    Input (&coeff);
    Dispatcher (coeff, &roots);
    Output (roots);
}


//-----------------------------------------------------------------------

void Dispatcher (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);

    assert (isfinite (coeff.a) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    if (IsZero (coeff.a) )
    {
        SolveLinear (coeff, roots);
    }
    else if (IsZero (coeff.c) )
    {
        SolveSemiLinear (coeff, roots);
    }
    else
    {
        SolveSquare (coeff, roots);
    }
}

//-----------------------------------------------------------------------

void SolveSemiLinear(struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);
    assert (isfinite (roots->x1) );
    assert (isfinite (roots->x2) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.a) );

    roots->x1 = -coeff.b / coeff.a;
    roots->nRoots = TWO_ROOTS;
}

//-----------------------------------------------------------------------

void SolveLinear (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);
    assert (isfinite (roots->x1) );
    assert (isfinite (roots->x2) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    if (IsZero (coeff.b) )
    {
        if (IsZero (coeff.c) )
        {
            roots->nRoots = INF_ROOTS;
        }
        else
        {
            roots->nRoots = NO_ROOTS;
        }
    }
    else
    {
        if (IsZero (coeff.c) )
        {
            roots->x1 = 0;
            roots->nRoots = ONE_ROOT;
        }
        else
        {
            roots->x1 = -coeff.c / coeff.b;
            roots->nRoots = ONE_ROOT;
        }
    }
}

//-----------------------------------------------------------------------

void SolveSquare (struct Coefficients coeff, struct Roots *roots)
{
    assert (roots != NULL);
    assert (isfinite (roots->x1) );
    assert (isfinite (roots->x2) );
    assert (isfinite (coeff.a) );
    assert (isfinite (coeff.b) );
    assert (isfinite (coeff.c) );

    double Discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;

    if (Discriminant < -EPSILON)
    {
        roots->nRoots = NO_ROOTS;
    }
    else
    {
        Discriminant = sqrt(Discriminant);

        roots->x1 = (-coeff.b - Discriminant) / (2 * coeff.a);
        roots->x2 = (-coeff.b + Discriminant) / (2 * coeff.a);

        if (IsZero (Discriminant) == true)
        {
            roots->nRoots = ONE_ROOT;
        }
        else
        {
            roots->nRoots = TWO_ROOTS;
        }
    }
}

#endif
