#include "Header.h"

#ifndef MODES_INFO
#define MODES_INFO

void ModeSwitcher ()
{
    switch (GetMode () )
    {
        case MANUAL : ManualMode ();
                      break;

        case TEST   : TestMode ();
                      break;

        default     : printf("Wrong format of input, try again, i believe in you.\n");
                      ModeSwitcher ();
    }
}

//-----------------------------------------------------------------------

char GetMode ()
{
    while (true)
    {
        int ch1 = getchar ();
        int ch2 = getchar ();

        if (ch2 == '\n')
        {
            if (ch1 == MANUAL)
            {
                return MANUAL;
            }
            else if (ch1 == TEST)
            {
                return TEST;
            }
        }
        else
        {
            CleanBuffer ();
            return 0;
        }
    }
}

//-----------------------------------------------------------------------

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

void TestMode ()
{
    printf ("\n**Test mode (Unit Testing)**\n\n");
    const int nTests = 9;
    int counter = 0;

    UnitSample test[nTests] = {//     a     b     c     x1_exp   x2_exp   nRoots_exp    x1    x2    nRoots       TestNumber
                                    {{1,    2,   -3},   {-3,     1,       TWO_ROOTS},   {0,   0,    NO_ROOTS},     1},
                                    {{1,    -5,  4},    { 1,     4,       TWO_ROOTS},   {0,   0,    NO_ROOTS},     2},
                                    {{1,    -2,  1},    { 1,     1,       ONE_ROOT},    {0,   0,    NO_ROOTS},     3},
                                    {{1,    25,  0},    {-25,    0,       TWO_ROOTS},   {0,   0,    NO_ROOTS},     4},
                                    {{0,    -2,  1},    { 0.5,   0,       ONE_ROOT},    {0,   0,    NO_ROOTS},     5},
                                    {{3,    4,   5},    { 0,     0,       NO_ROOTS},    {0,   0,    NO_ROOTS},     6},
                                    {{1,    3.5, 2.5},  {-2.5,  -1,       TWO_ROOTS},   {0,   0,    NO_ROOTS},     7},
                                    {{0,    0,   0},    { 0,     0,       NO_ROOTS},    {0,   0,    NO_ROOTS},     8},    //invalid test
                                    {{0,    0,   0},    { 0,     0,       INF_ROOTS},   {0,   0,    NO_ROOTS},     9}};

    for (int i = 0; i < nTests; i++)
    {
        test[i].roots.nRoots = Dispatcher(test[i].coeff, &test[i].roots);
        counter += UnitTester(test[i]);
    }

    printf("\n--------------------------------\n"
             "Total: %d correct, %d incorrect.\n"
             "--------------------------------\n", counter, nTests - counter);
}

//------------------------------------------------------------------------------

int UnitTester(struct UnitSample test)
{
    assert (isfinite (test.TestNumber) );

    assert (isfinite (test.coeff.a) );
    assert (isfinite (test.coeff.b) );
    assert (isfinite (test.coeff.c) );

    assert (isfinite (test.roots_exp.x1) );
    assert (isfinite (test.roots_exp.x2) );
    assert (isfinite (test.roots_exp.nRoots) );

    assert (isfinite (test.roots.x1) );
    assert (isfinite (test.roots.x2) );
    assert (isfinite (test.roots.nRoots) );

    if (test.roots_exp.nRoots != test.roots.nRoots || CompareTwo (test.roots_exp.x1, test.roots.x1) == false || CompareTwo (test.roots.x2, test.roots_exp.x2) == false)
    {
        REDLINE("----------\n"
                "|Test #%d |: Incorrect execution: a = %lg, b = %lg, c = %lg,\n"
                "----------                        x1 = %lg, x2 = %lg, nRoots = %d\n\n"
                "             Expected:            x1 = %lg, x2 = %lg, nRoots = %d.\n\n",
                test.TestNumber, test.coeff.a, test.coeff.b, test.coeff.c, test.roots.x1, test.roots.x2,
                test.roots.nRoots, test.roots_exp.x1, test.roots_exp.x2, test.roots_exp.nRoots);
        return 0;
    }
    else
    {
        GREENLINE("--------- \n"
                  "|Test #%d | : Correct execution!\n"
                  "--------- \n\n", test.TestNumber);
        return 1;
    }
    return 0;
}

#endif
