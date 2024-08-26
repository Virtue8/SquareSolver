#include "Header.h"

#ifndef SOLVE_FUNCS
#define SOLVE_FUNCS

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
