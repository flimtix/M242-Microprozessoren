/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Buzzer_Treiber

PURPOSE:    Dieser Treiber steuert den Buzzer an.

------------------------------------------------------------------------*/

#ifndef _NewTemplate
#define _NewTemplate

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

// Semaphore controlling the access to the LEDs
static osSemaphoreId_t buzzerSemaphoreHandleId;

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Beep the buzzer for a given length in ms
void Buzzer_Beep(int length);

#endif
