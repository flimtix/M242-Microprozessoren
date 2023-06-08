/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Treiber

PURPOSE:    Dieser Modul dient als Vorlage für neue Treiber.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "Display_Treiber.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

// Timeout for the semaphore before it will throw an error
#define SEMAPHORE_TIMEOUT 100

// Where to display the dots
#define UPDATE_ALL_SEGMENTS SEG_Driver_DP_1 | SEG_Driver_DP_2 | SEG_Driver_DP_3 | SEG_Driver_DP_4

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

// Converts the time to the format of the display
int Convert_Time_To_Display(int time)
{
    // Negative time is not supported by the display
    if (time <= 0)
    {
        return 0;
    }

    // TODO: Add a check if the time is too big for the display
    // The display can only show 4 digits

    // TODO: Convert the time to the format of the display
    return time;
}

// Writes the time to the SEG_Driver
void Write_Time_To_Display(int time, int flashSpeed)
{
    // Convert the time to the format of the display
    int displayTime = Convert_Time_To_Display(time);

    // Semaphore to prevent the display from being updated by multiple tasks at the same time
    // Wait for the semaphore to be released
    osSemaphoreAcquire(displaySemaphoreHandleId, SEMAPHORE_TIMEOUT);

    // Write the time to the display
    SEG_Driver_Write(displayTime, UPDATE_ALL_SEGMENTS, flashSpeed);

    // Release the semaphore so other tasks can update the display
    osSemaphoreRelease(displaySemaphoreHandleId);
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Initializes the display and updates the display with the given value
void Update_Display_Task()
{
    while (true)
    {
        // Update the display every 5ms
        SEG_Driver_Task_5ms();
        osDelay(5);
    }
}

// Updates the time of the display
void Display_Time(int time)
{
    // Write the time to the display without flashing
    Write_Time_To_Display(time, SEG_Driver_FLASH_OFF);
}

// Updates the time of the display with a flashing effect
void Display_Flash_Time(int time, enum DisplayFlashSpeed flashSpeed)
{
    // Convert the flash speed to the format of the SEG_Driver
    int flash;
    switch (flashSpeed)
    {
    case SLOW:
        flash = SEG_Driver_FLASH_SLOW;
        break;
    case FAST:
        flash = SEG_Driver_FLASH_FAST;
        break;
    default:
        flash = SEG_Driver_FLASH_OFF;
        break;
    }

    // Write the time to the display
    Write_Time_To_Display(time, flash);
}
