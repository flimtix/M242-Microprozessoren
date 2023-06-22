/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      Taster Treiber

PURPOSE:    Dieser Treiber liest die Taster des Mikrocontrollers aus.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "Taster_Treiber.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

// Status of the tasters so that they can be read without accessing the hardware
static bool TASTER_STATUS[AMOUNT_OF_TASTER] = {false, false, false};
static bool TASTER_HAS_CHANGE[AMOUNT_OF_TASTER] = {false, false, false};

// Callback functions for the tasters
static void (*TASTER_CALLBACK[AMOUNT_OF_TASTER])() = {NULL, NULL, NULL};

// Callback function for long press
static void (*TASTER_LONG_CALLBACK[AMOUNT_OF_TASTER])() = {NULL, NULL, NULL};

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

// Updates the given taster with the current state
void Update_Taster(enum Taster taster)
{
    // Read the status of the taster
    bool status = false;
    switch (taster)
    {
    case TASTER_1:
        status = HAL_GPIO_ReadPin(GPIOA, TASTER_1_Pin);
        break;
    case TASTER_2:
        status = HAL_GPIO_ReadPin(GPIOA, TASTER_2_Pin);
        break;
    case TASTER_3:
        status = HAL_GPIO_ReadPin(TASTER_3_GPIO_Port, TASTER_3_Pin);
        break;
    default:
        // This should never happen, because the enum Taster is used as parameter
        break;
    }

    // Save the status of the taster so that it can be read without accessing the hardware
    // Set that the taster changed the state
    TASTER_STATUS[taster] = !status;
    // Invert the status because the taster is active low
    TASTER_HAS_CHANGE[taster] = !status;
}

// Check if there is a callback for the taster
bool HasCallback(enum Taster taster)
{
    return TASTER_CALLBACK[taster] != NULL;
}

// Check if there is a long callback for the taster
bool HasLongCallback(enum Taster taster)
{
    return TASTER_LONG_CALLBACK[taster] != NULL;
}

// Check if the taster is pressed long
bool IsLongPress(enum Taster taster)
{
    // Only wait if there is a callback for a long press
    if (HasLongCallback(taster))
    {
        // Find out if the taster is pressed longer than 2 sek
        int counter = 0;

        // Wait for the taster to be released or 2 sek
        // The taster will be released by an interrupt
        while (Taster_Get(taster))
        {
            // Update the counter
            counter++;

            // Check if the taster is pressed long enough
            if (counter >= 40)
            {
                return true;
            }

            // Wait for a change
            // TODO: muss Hier nicht 2 Sek - 100 abgewartet werden?
            // 2'000  => 40 * 50ms
            osDelay(50);
        }
    }

    // The taster was not pressed long
    return false;
}

// Calls the callback function for the given taster
void Trigger_Callback(enum Taster taster)
{
    // Check if the taster is pressed long
    if (IsLongPress(taster))
    {
        // Call the buzzer
        Buzzer_Beep(500);

        // Call the callback function for long press
        TASTER_LONG_CALLBACK[taster]();
    }
    else if (HasCallback(taster))
    {
        // Call the buzzer
        Buzzer_Beep(300);

        // Call the callback function for short press
        TASTER_CALLBACK[taster]();
    }
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Initializes the taster treiber and triggers the callback function if a taster is pressed
void TasterTask(void *argument)
{
    // Cycle through all tasters forever and check if they have changed
    while (true)
    {
        // Cycle through all tasters
        for (int i = 0; i < AMOUNT_OF_TASTER; i++)
        {
            // Check if the taster has changed
            if (TASTER_HAS_CHANGE[i])
            {
                // Reset the change flag
                TASTER_HAS_CHANGE[i] = false;

                // Trigger the callback function
                Trigger_Callback(i);
            }
        }

        // Wait for 20ms
        osDelay(20);
    }
}

// Sets the callback function for the given taster
void Set_Taster_Callback(enum Taster taster, void (*callback)(void))
{
    // Save the callback function
    TASTER_CALLBACK[taster] = callback;
}

// Sets the callback function if the given taster is pressed long
void Set_Taster_Long_Callback(enum Taster taster, void (*callback)(void))
{
    // Save the callback function
    TASTER_LONG_CALLBACK[taster] = callback;
}

// Informs the Taster_Treiber that the given taster has been pressed
void Taster_Pressed(enum Taster taster)
{
    // Update the taster status
    // Only trigger the callback and the buzzer if is was a pressing interrupt
    Update_Taster(taster);
}

// Reads the current state of the given taster and returns it
bool Taster_Get(enum Taster taster)
{
    // Return the status of the taster
    return TASTER_STATUS[taster];
}
