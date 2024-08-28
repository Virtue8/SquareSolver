#ifndef MENU_CPP
#define MENU_CPP

#include "../headers/Menu.h"

void Menu ()
{
    printf ("###############################\n"
            "####     ######################\n"
            "###  ######    ################\n"
            "###   ####  *  ############ ###\n"
            "#####   ###    ######   ##   ##\n"
            "######  ###### ###### ##### ###\n"
            "##     ####### ### ## ##### ###\n"
            "###############################\n\n");

    printf ("SQUARE EQUATION SOLVER (V1) \n"
            "Dolgopa City, 2024 \n");
    printf ("All rights reserved.\n\n\n");

    ModeSwitcher ();
}

//-----------------------------------------------------------------------

void ModeSwitcher ()
{
    printf ("\nChoose mode: \n"
            "m for Manual Mode\n"
            "t for Test Mode\n\n");

    switch (GetMode () )
    {
        case MANUAL : ManualMode ();
                      break;

        case TEST   : TestMode ();
                      break;

        default     : printf ("\nWrong format of input, try again, i believe in you.\n");
                      ModeSwitcher();
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

#endif
