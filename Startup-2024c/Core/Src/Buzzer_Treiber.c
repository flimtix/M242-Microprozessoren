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
static int buzzLength = 0;

// State of the buzzer
static bool isBuzzerOn = false;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

// Toggle the buzzer state
void SetBuzzer(bool buzzerState)
{
    // Update the buzzer state
    isBuzzerOn = buzzerState;

    // Semaphore controlling the access to the buzzer
    osSemaphoreAcquire(buzzerSemaphoreHandleId, SEMAPHORE_TIMEOUT);

    // Make the buzzer beep (false = the buzzer is on)
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, !buzzerState);

    // Release the semaphore
    osSemaphoreRelease(buzzerSemaphoreHandleId);
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Initializes the buzzer and updates the buzzer task
// This task will control the state of buzzer in the background
void BuzzerTask(void *argument)
{
    while (true)
    {
        // Only beep the buzzer if the buzzer is off and there is a delay
        if (!isBuzzerOn && buzzLength > 0)
        {
            SetBuzzer(true);
        }

        // Wait before for for the buzzer to end
        osDelay(DEFAULT_BUZZER_DELAY);

        // Decrease the length that the buzzer already ran
        // If the buzzer was called again while the buzzer was running the length of the new call will be decreased
        if (buzzLength > 0)
        {
            buzzLength -= DEFAULT_BUZZER_DELAY;
        }

        // Only turn off the buzzer if the buzzer is on and there is no call
        if (isBuzzerOn && buzzLength <= 0)
        {
            SetBuzzer(false);
        }
    }
}

// Beep the buzzer for a given length in ms
void Buzzer_Beep(int length)
{
    // Negative length is not supported by the buzzer
    if (length <= 0)
    {
        return;
    }

    // Update the length of the buzzer if the given length is bigger
    if (length > buzzLength)
    {
        buzzLength = length;
    }
}