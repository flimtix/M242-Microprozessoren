/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Display_Treiber

PURPOSE:    Dieser Treiber ist eine Abstraktion für den Seg_Driver um die Bedienfreundlichkeit zu verbessern

------------------------------------------------------------------------*/

#ifndef _DISPLAY_TREIBER
#define _DISPLAY_TREIBER

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "Seg_Driver.h"

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

// Contains the speed of the flashing effect
enum DisplayFlashSpeed
{
    OFF = 0,
    SLOW = 1,
    FAST = 2,
};

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Initializes the display and updates the display with the given value
// This function should be called once at the beginning of the program
// This will result in a infinite loop which will update the display
void DisplayUpdateTask(void *argument);

// Updates the time of the display
// The time should be in ms
void DisplayTime(unsigned int time);

// Updates the time of the display with a flashing effect
void DisplayFlashTime(unsigned int time, enum DisplayFlashSpeed flashSpeed);

#endif
