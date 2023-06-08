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

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Beep the buzzer for a given length in ms
void Buzzer_Beep(int length)
{
    // Negative length is not supported by the buzzer
    if (length <= 0)
    {
        return;
    }

    // Keep track of the number of calls to make sure the buzzer works with multiple calls
    static int callCount = 0;

    // Increase the call count
    callCount++;

    // Only beep the buzzer if it is the first call
    if (callCount == 1)
    {
        // Semaphore controlling the access to the buzzer
        osSemaphoreAcquire(buzzerSemaphoreHandleId, SEMAPHORE_TIMEOUT);

        // Make the buzzer beep
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);

        // Release the semaphore
        osSemaphoreRelease(buzzerSemaphoreHandleId);
    }

    // Wait for the given length
    osDelay(length);

    // Decrease the call count
    callCount--;

    // Only turn off the buzzer if it is the last call
    if (callCount <= 1)
    {
        // Semaphore controlling the access to the buzzer
        osSemaphoreAcquire(buzzerSemaphoreHandleId, SEMAPHORE_TIMEOUT);

        // Turn off the buzzer
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

        // Release the semaphore
        osSemaphoreRelease(buzzerSemaphoreHandleId);
    }
}