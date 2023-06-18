/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      State Event

PURPOSE:    Dieses Modul stellt die Funktionen zur Verfuegung, um
            die Zustandsaenderungen der Maschine zu verwalten.

------------------------------------------------------------------------*/

#ifndef _STATE_EVENT
#define _STATE_EVENT

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

// FreeRTOS
#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

// Do not move the includes to the .c file because the caller
// needs them to create the other tasks

// Event-Steuerung
#include "Stopwatch.h"
#include "Timer.h"

// Treiber
#include "Taster_Treiber.h"
#include "Buzzer_Treiber.h"
#include "Display_Treiber.h"
#include "LED_Treiber.h"
#include "Seg_Driver.h"

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

// Enum for the states that can be used by the state event
enum State
{
    STATE_STOPWATCH = 0,
    STATE_TIMER = 1,
};

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// The background task to initialize the state event
// This will create a task for the state event
void StateEventTask(void *argument);

#endif
