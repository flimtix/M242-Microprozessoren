/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      LED Treiber

PURPOSE:    Dieser Treiber steuert die LEDs des Mikrocontrollers.

------------------------------------------------------------------------*/

#ifndef _LED_TREIBER
#define _LED_TREIBER

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

// Enum for the LEDs that can be used by the LED driver
enum Led
{
    LED_1 = 0,
    LED_2 = 1,
    LED_3 = 2,
    LED_4 = 3,
};

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

// Semaphore controlling the access to the LEDs
static osSemaphoreId_t ledSemaphoreHandleId;

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Changes the state of the LED to the opposite of its current state
void LED_Toggle(enum Led led);

// Sets the state of the LED to the given state
// state = true: Turn the LED on
// state = false: Turn the LED off
void LED_Set(enum Led led, bool state);

#endif
