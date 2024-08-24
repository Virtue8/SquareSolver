#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

enum modes
{
    MANUAL = 'm',
    TEST = 't'
};

enum roots
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

struct Coefficients
{
    double a;
    double b;
    double c;
};

struct Roots
{
    double x1;
    double x2;
    int nRoots;
};

struct UnitSample
{
    struct Coefficients coeff;
    struct Roots roots_exp;
    struct Roots roots;

    int TestNumber;
};

// doxygen
// preproccessor
// cmd arg

// split compilation
// files

const double EPSILON = 1e-10;

int SolveLinear (struct Coefficients coeff, struct Roots *roots);
int SolveSemiLinear (struct Coefficients coeff, struct Roots *roots);
int SolveSquare (struct Coefficients coeff, struct Roots *roots);
int Dispatcher(struct Coefficients coeff, struct Roots *roots);

void Menu ();
void ManualMode ();
void TestMode ();
void ModeSwitcher ();
char GetMode ();

void Input (struct Coefficients *coeff);
void Output (struct Roots roots);

void CleanBuffer ();

bool IsZero (double eps);
bool CompareTwo (double k1, double k2);

int UnitTester (struct UnitSample test);

//-----------------------------------------------------------------------

int main ()
{
    Menu ();

    return 0;
}

//-----------------------------------------------------------------------

void Menu ()
{
    printf ("#####################\n"
            "###     ####      ###\n"
            "###  ##  #####  #####\n"
            "###     ######  #####\n"
            "###  #  ######  #####\n"
            "###  ##  #####  #####\n"
            "#####################\n\n");

    printf ("SQUARE EQUATION SOLVER (V1) \n"
            "Dolgopa City, 2024 \n");
    printf ("All rights reserved.\n\n\n");

    printf ("Choose mode: \n"
            "m for Manual Mode\n"
            "t for Test Mode\n");

    ModeSwitcher ();
}

//-----------------------------------------------------------------------

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
             "--------------------------------", counter, nTests - counter);
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

    assert (&test.coeff != NULL);
    assert (&test.roots != NULL);
    assert (&test.roots_exp != NULL);

    if (test.roots_exp.nRoots != test.roots.nRoots || CompareTwo (test.roots_exp.x1, test.roots.x1) == false || CompareTwo (test.roots.x2, test.roots_exp.x2) == false)
    {
        printf ("%s----------\n"
               "|Test #%d |: Incorrect execution:%s a = %lg, b = %lg, c = %lg,\n"
                "%s----------%s                       x1 = %lg, x2 = %lg, nRoots = %d\n\n"
                "            Expected:            x1 = %lg, x2 = %lg, nRoots = %d.\n\n",
                RED, test.TestNumber, RESET, test.coeff.a, test.coeff.b, test.coeff.c, RED, RESET, test.roots.x1, test.roots.x2,
                test.roots.nRoots, test.roots_exp.x1, test.roots_exp.x2, test.roots_exp.nRoots);
        return 0;
    }
    else
    {
        printf ("%s--------- \n"
                "|Test #%d | : Correct execution!\n"
                "--------- %s\n\n", GREEN, test.TestNumber, RESET);
        return 1;
    }
    return 0;
}


//-----------------------------------------------------------------------

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

//-----------------------------------------------------------------------

void Output (struct Roots roots)
{
    assert (isfinite (roots.x1) );
    assert (isfinite (roots.x2) );

    printf ("\nProgram answer: \n\n");    //

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

//-----------------------------------------------------------------------

bool IsZero (double value)
{
    return (fabs (value) <= EPSILON);
}

//-----------------------------------------------------------------------

bool CompareTwo (double k1, double k2)
{
    return (fabs (k1 - k2) <= EPSILON);
}

//-----------------------------------------------------------------------

void CleanBuffer ()
{
    char ch = '\0';

    while (ch = getchar () != '\n' && ch != EOF)
    {

    }
}
