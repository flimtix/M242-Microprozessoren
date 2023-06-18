/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Stopwatch

PURPOSE:    Diese Datei ist für die Event-Steuerung der Stopwatch zuständig.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "Stopwatch.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

// The current state of the stopwatch
static bool isStopwatchRunning = false;
// The current state of the intermediate time
static bool isShowingIntermediateTime = false;

// The current time of the stopwatch in tenths of a second
static unsigned int currentTime = 0;
// The intermediate time of the stopwatch in tenths of a second
static unsigned int intermediateTime = 0;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// The background task to initialize the stopwatch
void StopwatchTask(void *argument)
{
    while (true)
    {
        // Only increase the time if the stopwatch is running
        if (IsStopwatchRunning())
        {
            // Increase the time by one tenth of a second
            currentTime++;
        }

        // Increase the time every tenth of a second
        osDelay(100);
    }
}

// Starts the stopwatch
void StartStopwatch()
{
    isShowingIntermediateTime = false;
    isStopwatchRunning = true;
}

// Stops the stopwatch
void StopStopwatch()
{
    isShowingIntermediateTime = false;
    isStopwatchRunning = false;
}

// Resets the stopwatch
void ResetStopwatch()
{
    // Only reset the stopwatch if it is not running
    if (!IsStopwatchRunning())
    {
        // Reset the stopwatch
        isStopwatchRunning = false;
        isShowingIntermediateTime = false;

        currentTime = 0;
        intermediateTime = 0;
    }
}

// Shows the intermediate time
void ShowIntermediateTime()
{
    intermediateTime = currentTime;
    isShowingIntermediateTime = true;
}

// Returns either the current time or the intermediate time
unsigned int GetStopwatchTime()
{
    if (isShowingIntermediateTime)
    {
        return intermediateTime;
    }
    else
    {
        return currentTime;
    }
}

// Retuns if the stopwatch is running
bool IsStopwatchRunning()
{
    return isStopwatchRunning;
}

// Returns if the intermediate time is showing
bool IsShowingIntermediateTime()
{
    return isShowingIntermediateTime;
}