#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"                    //refact color mechanics
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

struct UnitSample
{
    double a;
    double b;
    double c;

    double x1_exp;
    double x2_exp;

    int nRoots_exp;
    int TestNumber;
};

struct Coeff
{
    double a;
    double b;
    double c;
};

struct Roots
{
    double x1;
    double x2;
};

// files
// doxygen
// struct for coefficients for roots

const double EPSILON = 1e-10;

int SolveLinear (double b, double c, double* x1);
int SolveSquare (double a, double b, double c, double* x1, double* x2);

int Dispatcher(double a, double b, double c, double *x1, double *x2, char ModeState);

void Menu ();
void ManualMode ();
void TestMode ();
void ModeSwitcher(char *ModeState);

void Input (double* a, double* b, double* c);
void Output (int nRoots, double x1, double x2);

void CleanBuffer ();

bool IsZero (double eps);
bool CompareTwo (double k1, double k2);

int UnitTester (struct UnitSample test);
void AllUnitsTester ();

char ModeState = 0;

//-----------------------------------------------------------------------

int main ()
{
    Menu ();

    return 0;
}

//-----------------------------------------------------------------------

void Menu ()
{
    printf ("#######################\n"
            "#####     ######     ##\n"
            "####   ########   #####\n"
            "#####   ########   ####\n"
            "######   ########   ###\n"
            "###     ######     ####\n"
            "#######################\n\n");

    printf ("SQUARE EQUATION SOLVER (V1) \n"
            "Dolgopa City, 2024 \n");
    printf ("All rights reserved.\n\n\n");

    printf ("Choose mode: \n"
            "m for Manual Mode\n"
            "t for Test Mode\n");

    ModeSwitcher(&ModeState);
}

//-----------------------------------------------------------------------

void ModeSwitcher(char *ModeState)
{
    char mode;
    scanf ("%c", &mode);

    switch (mode)
    {
        case MANUAL : ManualMode ();
                      *ModeState = MANUAL;
                      break;

        case TEST   : TestMode ();
                      break;

        default     : CleanBuffer ();
                      printf("Wrong format of input, try again, i believe in you.\n");
                      ModeSwitcher(ModeState);
    }
}

//-----------------------------------------------------------------------

void ManualMode ()
{
    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    printf ("**Manual Mode**\n\n");

    Input (&a, &b, &c);

    int nRoots = Dispatcher (a, b, c, &x1, &x2, ModeState);
    Output (nRoots, x1, x2);
}

//-----------------------------------------------------------------------

void TestMode ()
{
    printf ("**Test mode (Unit Testing)**\n\n");
    AllUnitsTester ();
}

//-----------------------------------------------------------------------

void Input (double* a, double* b, double* c)
{
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);
    assert (a != b && a != c && b != c);

    printf ("Enter coefficients for ax^2+bx+c=0 equation ");
    printf ("in the following format: a b c \n \n");

    while (scanf ("%lg %lg %lg", a, b, c) != 3)
    {
        CleanBuffer ();
        printf("Wrong format of input, try again, i believe in you.\n");
    }
}

//-----------------------------------------------------------------------

int Dispatcher (double a, double b, double c, double *x1, double *x2, char ModeState)
{
    assert (x1 != x2);
    assert (x2 != NULL);
    assert (x1 != NULL);

    assert (isfinite (a) );
    assert (isfinite (b) );
    assert (isfinite (c) );

    if (IsZero (a) )
    {
        if (ModeState = MANUAL)
        {
        printf ("Your equation is linear (b*x + c = 0).\n");
        }
        return SolveLinear (b, c, x1);
    }
    else if (IsZero (c) )
    {
        x2 = 0;
        if (ModeState = MANUAL)
        {
        printf ("Your equation is semi-square (a*x^2 + b*x = 0).\n"
                "One of the roots is x = %lg.\n"
                "Now the equation is linear.\n", *x2);
        }
        return SolveLinear (a, b, x1);
    }
    else
    {
        if (ModeState = MANUAL)
        {
        printf ("Your equation is square (a*x^2 + b*x + c = 0).\n");
        }
        return SolveSquare (a, b, c, x1, x2);
    }
}

//-----------------------------------------------------------------------

int SolveLinear (double b, double c, double* x1)
{
    assert (x1 != NULL);
    assert (isfinite (b) );
    assert (isfinite (c) );

    if (IsZero (b) )
    {
        if (IsZero (c) )
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

//-----------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2)
{
    assert (x1 != x2);
    assert (x2 != NULL);
    assert (x1 != NULL);

    assert (isfinite (a) );
    assert (isfinite (b) );
    assert (isfinite (c) );

    double Discriminant = b * b - 4 * a * c;

    if (Discriminant < -EPSILON)
    {
        return NO_ROOTS;
    }
    else
    {
        Discriminant = sqrt(Discriminant);

        *x1 = (-b - Discriminant) / (2 * a);
        *x2 = (-b + Discriminant) / (2 * a);

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

void Output (int nRoots, double x1, double x2)
{
    assert (isfinite (x1) );
    assert (isfinite (x2) );

    printf ("\nProgram answer: \n\n");

    switch (nRoots)
        {
            case NO_ROOTS:  printf ("There is no real roots :(");
                            break;

            case ONE_ROOT:  printf ("The only root is %lg.", x1);
                            break;

            case TWO_ROOTS: printf ("Roots are %lg and %lg.", x1, x2);
                            break;

            case INF_ROOTS: printf ("Any root.");
                            break;

            default: printf ("Error");
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

    while ( ch = getchar () != '\n' && ch != EOF) {}
}

//-----------------------------------------------------------------------

void AllUnitsTester ()
{
    UnitSample test1 = {1, 2, -3, -3, 1, TWO_ROOTS, 1};
    UnitSample test2 = {1, -5, 4, 5, 1, TWO_ROOTS, 2};
    UnitSample test3 = {1, -2, 1, 1, 1, ONE_ROOT, 3};
    UnitSample test4 = {1, 25, 0, -25, 0, ONE_ROOT, 4};
    UnitSample test5 = {0, -2, 1, 0.5, 0, ONE_ROOT, 5};
    UnitSample test6 = {3, 4, 5, 0, 0, NO_ROOTS, 6};
    UnitSample test7 = {1, 2.5, -1.5, -3, 0.5, TWO_ROOTS, 7};
    UnitSample test8 = {0, 0, 3, 0, 0, NO_ROOTS, 8};
    UnitSample test9 = {0, 0, 0, 0, 0, INF_ROOTS, 9};


    int counter = 0;

    counter += UnitTester (UnitSample (test1) );
    counter += UnitTester (UnitSample (test2) );
    counter += UnitTester (UnitSample (test3) );
    counter += UnitTester (UnitSample (test4) );
    counter += UnitTester (UnitSample (test5) );
    counter += UnitTester (UnitSample (test6) );
    counter += UnitTester (UnitSample (test7) );
    counter += UnitTester (UnitSample (test8) );
    counter += UnitTester (UnitSample (test9) );

    printf("-----------------------------------"
           "Total: %d correct, %d incorrect.\n"
           "-----------------------------------", counter, 9 - counter);
}

//------------------------------------------------------------------------------

int UnitTester(struct UnitSample test)
{
    assert (isfinite (test.a) );
    assert (isfinite (test.b) );
    assert (isfinite (test.c) );
    assert (isfinite (test.x1_exp) );
    assert (isfinite (test.x2_exp) );

    double x1 = 0;
    double x2 = 0;

    int nRoots = Dispatcher (test.a, test.b, test.c, &x1, &x2, ModeState);



    if (nRoots != test.nRoots_exp || CompareTwo (x1, test.x1_exp) == false || CompareTwo (x2, test.x2_exp) == false)
    {
        printf ("%s----------\n"
               "|Test #%d |: Incorrect execution:%s a = %lg, b = %lg, c = %lg,\n"
                "%s----------%s                            x1 = %lg, x2 = %lg, nRoots = %d\n\n"
                "               Expected: x1 = %lg, x2 = %lg, nRoots = %d.\n\n",
                RED, test.TestNumber, RESET, test.a, test.b, test.c, RED, RESET, x1, x2,
                nRoots, test.x1_exp, test.x2_exp, test.nRoots_exp);
        return 0;
    }
    else
    {
        printf ("%s--------- \n"
                "|Test #%d | : Correct execution.\n"
                "--------- %s\n\n", GREEN, test.TestNumber, RESET);
        return 1;
    }
}
