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

// On every function call the buzzer will beep
#include "Buzzer_Treiber.h"

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
void Set_Taster_Callback(enum Taster taster, void (*callback)(void));

// Sets the callback function if the given taster is pressed long
// Pass a NULL pointer to remove the callback
void Set_Taster_Long_Callback(enum Taster taster, void (*callback)(void));

// Informs the Taster_Treiber that the given taster has been pressed or released
// This function will trigger the callback functions
void Taster_Pressed(enum Taster taster);

// Reads the current state of the given taster and returns it from the stored value
bool Taster_Get(enum Taster taster);

#endif
