#include "Header.h"
#include "ModesInfo.h"
#include "SolveFuncs.h"
#include "InputOutputDispatcher.h"
#include "HelpfulFuncs.h"

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
