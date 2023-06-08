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
// Timeout for the semaphore before it will throw an error
#define SEMAPHORE_TIMEOUT 100

// Status of the tasters so that they can be read without accessing the hardware
static bool TASTER_1_STATUS = false;
static bool TASTER_2_STATUS = false;
static bool TASTER_3_STATUS = false;

// Callback functions for the tasters
static void (*TASTER_1_CALLBACK)(bool) = NULL;
static void (*TASTER_2_CALLBACK)(bool) = NULL;
static void (*TASTER_3_CALLBACK)(bool) = NULL;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

// Updates the given taster with the current state
// This function will trigger the callback function
void Update_Taster(enum Taster taster)
{
    // Update the taster
    switch (taster)
    {
    case TASTER_1:
        TASTER_1_STATUS = !HAL_GPIO_ReadPin(GPIOA, TASTER_1_Pin);
        break;
    case TASTER_2:
        TASTER_2_STATUS = !HAL_GPIO_ReadPin(GPIOA, TASTER_2_Pin);
        break;
    case TASTER_3:
        TASTER_3_STATUS = !HAL_GPIO_ReadPin(TASTER_3_GPIO_Port, TASTER_3_Pin);
        break;
    default:
        // This should never happen, because the enum Taster is used as parameter
        break;
    }
}

// Calls the callback function for the given taster
void Trigger_Callback(enum Taster taster)
{
    // Call the callback function to trigger the event
    switch (taster)
    {
    case TASTER_1:
        TASTER_1_CALLBACK(TASTER_1_STATUS);
        break;
    case TASTER_2:
        TASTER_2_CALLBACK(TASTER_2_STATUS);
        break;
    case TASTER_3:
        TASTER_3_CALLBACK(TASTER_3_STATUS);
        break;
    default:
        // This should never happen, because the enum Taster is used as parameter
        break;
    }
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// Sets the callback function for the given taster
void Set_Taster_Callback(enum Taster taster, void (*callback)(bool))
{
    switch (taster)
    {
    case TASTER_1:
        TASTER_1_CALLBACK = callback;
        break;
    case TASTER_2:
        TASTER_2_CALLBACK = callback;
        break;
    case TASTER_3:
        TASTER_3_CALLBACK = callback;
        break;
    default:
        // This should never happen, because the enum Taster is used as parameter
        break;
    }
}

// Reads the current state of the given taster and returns it
bool Taster_Get(enum Taster taster)
{
    // Update the taster
    Update_Taster(taster);

    // Return the status of the taster
    switch (taster)
    {
    case TASTER_1:
        return TASTER_1_STATUS;
    case TASTER_2:
        return TASTER_2_STATUS;
    case TASTER_3:
        return TASTER_3_STATUS;
    default:
        return false;
    }
}

// Informs the Taster_Treiber that the given taster has been pressed
void Taster_Pressed(enum Taster taster)
{
    // Update the taster status
    Update_Taster(taster);

    // Call the callback function to trigger the event
    Trigger_Callback(taster);
}