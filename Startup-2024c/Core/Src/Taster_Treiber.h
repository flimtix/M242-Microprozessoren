/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Taster Treiber

PURPOSE:    Dieser Treiber liest die Taster des Mikrocontrollers aus.

------------------------------------------------------------------------*/

#ifndef _Taster_Treiber
#define _Taster_Treiber

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

// Contains all possible tasters
enum Taster
{
    TASTER_1 = 0,
    TASTER_2 = 1,
    TASTER_3 = 2,
};

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Sets the callback function for the given taster
// Pass a NULL pointer to remove the callback
// Pass a pointer to a function with the following signature: void FuncName(bool pressed)
void Set_Taster_Callback(enum Taster taster, void (*callback)(bool));

// Reads the current state of the given taster and returns it
// This will not trigger the callback function
// This will result in an hardware access and should not be used in time critical code
bool Taster_Get(enum Taster taster);

// Informs the Taster_Treiber that the given taster has been pressed
void Taster_Pressed(enum Taster taster);

#endif
