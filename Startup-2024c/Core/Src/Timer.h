/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Timer

PURPOSE:    Diese Datei ist für die Event-Steuerung des Timers zuständig.

------------------------------------------------------------------------*/

#ifndef _TIMER
#define _TIMER

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>

//  -------------------------------------------
//  2.     G L O B A L    D E F I N I T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  3.     G L O B A L    C O N S T A N T S
//  ---------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// The background task to initialize the timer
// This will create a task for the timer
void TimerTask(void *argument);

// Increments the configured time
void IncrementTime();

// Decrements the configured time
void DecrementTime();

// Start the timer
void StartTimer();

// Pauses the timer
void PauseTimer();

// Resumes the timer
void ResumeTimer();

// Stops the timer
void ResetTimer();

// Returns the current time
// The time is in tenths of a second
unsigned int GetTimerTime();

// Returns true if the timer is running
bool IsTimerRunning();

// Returns true if the timer is paused
bool IsTimerPaused();

// Returns true if the time is up
bool IsTimeUp();

#endif
