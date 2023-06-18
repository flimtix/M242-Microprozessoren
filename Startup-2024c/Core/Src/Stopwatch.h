/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Stopwatch

PURPOSE:    Diese Datei ist für die Event-Steuerung der Stopwatch zuständig.

------------------------------------------------------------------------*/

#ifndef _STOPWATCH
#define _STOPWATCH

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

// The background task to initialize the stopwatch
// This will create a task for the stopwatch
void StopwatchTask(void *argument);

// Starts the stopwatch
void StartStopwatch();

// Stops the stopwatch
void StopStopwatch();

// Resets the stopwatch
void ResetStopwatch();

// Shows the intermediate time
// The intermediate time is the time between the time when the method was called
// The time will continue to run in the background
void ShowIntermediateTime();

// Returns either the current time or the intermediate time
// The time is in tenths of a second
unsigned int GetStopwatchTime();

// Returns true if the stopwatch is running
bool IsStopwatchRunning();

// Returns true if the stopwatch is showing the intermediate time
bool IsShowingIntermediateTime();

#endif
