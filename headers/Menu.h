#ifndef MENU_HEADER
#define MENU_HEADER

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

#include "Test.h"
#include "SolveFuncs.h"
#include "Utilities.h"
#include "InputOutput.h"

enum modes
{
    MANUAL = 'm',
    TEST = 't'
};

void Menu ();
void ModeSwitcher ();
char GetMode ();

#endif
