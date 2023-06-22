/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Buzzer_Treiber

PURPOSE:    Dieser Treiber steuert den Buzzer an.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "Buzzer_Treiber.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

// Timeout for the semaphore before it will throw an error
#define SEMAPHORE_TIMEOUT 100

// Default delay between the buzzer checks in ms
#define DEFAULT_BUZZER_DELAY 10

// Semaphore controlling the access to the buzzer
osSemaphoreId_t buzzerSemaphoreHandleId;

// Keep track of the biggest length of the buzzer
static long buzzUntil = 0;

// State of the buzzer
static bool isBuzzerOn = false;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

// Toggle the buzzer state
void SetBuzzer(bool buzzerState)
{
    // Only toggle the buzzer if the buzzer state is different
    if (isBuzzerOn == buzzerState)
    {
        return;
    }

    // Update the buzzer state
    isBuzzerOn = buzzerState;

    // Semaphore controlling the access to the buzzer
    osSemaphoreAcquire(buzzerSemaphoreHandleId, SEMAPHORE_TIMEOUT);

    // Make the buzzer beep (false = the buzzer is on)
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, !buzzerState);

    // Release the semaphore
    osSemaphoreRelease(buzzerSemaphoreHandleId);
}

// Check if the buzzer should be turned off
bool IsBuzzTimeReached()
{
    // The buzzer should be turned off if the buzzUntil is lower than the current time
    return buzzUntil <= osKernelGetTickCount();
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Initializes the buzzer and updates the buzzer task
// This task will control the state of buzzer in the background
void BuzzerTask(void *argument)
{
    // Variable to keep track of the current time that the buzzer is waiting for
    long currentBuzzUntil = 0;

    while (true)
    {
        // Only beep the buzzer if the buzzer is off and there is a delay
        if (!IsBuzzTimeReached())
        {
            SetBuzzer(true);
        }

        // Check if the time of the buzzer is reached
        if (IsBuzzTimeReached())
        {
            // The buzzer is not needed so wait for the default delay before checking again
            osDelay(DEFAULT_BUZZER_DELAY);
        }
        else
        {
            // Update the current time that the buzzer is waiting for
            currentBuzzUntil = buzzUntil;

            // Wait for the buzzer to finish
            osDelayUntil(currentBuzzUntil);
        }

        // Only turn off the buzzer if the buzzer is on and there is no call
        if (IsBuzzTimeReached())
        {
            SetBuzzer(false);
        }
    }
}

// Beep the buzzer for a given length in ms
void Buzzer_Beep(int length)
{
    // Negative length is not supported by the buzzer
    if (length > 0)
    {
        // Update the length of the buzzer
        buzzUntil = osKernelGetTickCount() + length;
    }
}