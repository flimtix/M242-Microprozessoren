/*-----------------------------------------------------------------------
            D E F I N I T I O N    M O D U L E
-------------------------------------------------------------------------

PRODUCT:    Common Application (AP)

TITLE:      State Event

PURPOSE:    Dieses Modul stellt die Funktionen zur Verfuegung, um
            die Zustandsaenderungen der Maschine zu verwalten.

------------------------------------------------------------------------*/

//  -------------------------------------------------
//  1. I N C L U D E S
//  -------------------------------------------------

#include "StateEvent.h"

//  -----------------------------------------------
//  3.     I N T E R N A L    D E F I N I T I O N S
//  -----------------------------------------------

// Delay for changing the configuring time in milliseconds
#define TIMER_CHANGE_DELAY 250
#define TIMER_CHANGE_FAST_DELAY 50

// The current running state
static enum State currentState = STATE_STOPWATCH;

// Check if the state was changed recently
static bool hasStateChanged = false;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

#pragma region Stopwatch State Handling

// List all possible stopwatch events so they can be called out of order
void Stoppuhr_LeereZeitAnzeigen();
void Stoppuhr_AktuelleZeitAnzeigen();
void Stoppuhr_ZwischenzeitAnzeigen();
void Stoppuhr_EndzeitAnzeigen();

void Stoppuhr_LeereZeitAnzeigen()
{
    ResetStopwatch();

    Set_Taster_Callback(TASTER_1, &Stoppuhr_AktuelleZeitAnzeigen);
    Set_Taster_Callback(TASTER_2, NULL);
    Set_Taster_Callback(TASTER_3, NULL);
}

void Stoppuhr_AktuelleZeitAnzeigen()
{
    StartStopwatch();

    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, &Stoppuhr_EndzeitAnzeigen);
    Set_Taster_Callback(TASTER_3, &Stoppuhr_ZwischenzeitAnzeigen);
}

void Stoppuhr_ZwischenzeitAnzeigen()
{
    // Don't show the intermediate time if it is already shown
    if (!IsShowingIntermediateTime())
    {
        ShowIntermediateTime();
    }

    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, &Stoppuhr_EndzeitAnzeigen);
    Set_Taster_Callback(TASTER_3, &Stoppuhr_AktuelleZeitAnzeigen);
}

void Stoppuhr_EndzeitAnzeigen()
{
    StopStopwatch();

    Set_Taster_Callback(TASTER_1, &Stoppuhr_AktuelleZeitAnzeigen);
    Set_Taster_Callback(TASTER_2, NULL);
    Set_Taster_Callback(TASTER_3, &Stoppuhr_LeereZeitAnzeigen);
}

#pragma endregion

#pragma region Timer State Handling

// List all possible timer events so they can be called out of order
void Timer_EingerichteteZeitAnzeigen();
void Timer_ZeitErhoehen();
void Timer_ZeitVerringern();
void Timer_AktuelleZeitAnzeigen();
void Timer_Pausieren();
void Timer_TimerAbgelaufen();

void Timer_EingerichteteZeitAnzeigen()
{
    if (IsTimerRunning() || IsTimeUp())
    {
        ResetTimer();
    }

    Set_Taster_Callback(TASTER_1, &Timer_ZeitErhoehen);
    Set_Taster_Callback(TASTER_2, &Timer_ZeitVerringern);
    Set_Taster_Callback(TASTER_3, &Timer_AktuelleZeitAnzeigen);
}

void Timer_ZeitErhoehen()
{
    // The amount of time the button is pressed
    int incrementAmount = 0;

    // Incerement the time until the button is released
    while (Taster_Get(TASTER_1))
    {
        IncrementTime();

        // Increment the time faster after a certain amount of time
        incrementAmount++;

        // The time is incremented with a delay so the time is not incremented too fast
        if (incrementAmount > 10)
        {
            osDelay(TIMER_CHANGE_FAST_DELAY);
        }
        else
        {
            osDelay(TIMER_CHANGE_DELAY);
        }
    }

    // Return to the previous state
    Timer_EingerichteteZeitAnzeigen();
}

void Timer_ZeitVerringern()
{
    // The amount of time the button is pressed
    int decrementAmount = 0;

    // Decrement the time until the button is released
    while (Taster_Get(TASTER_2))
    {
        DecrementTime();

        // Decrement the time faster after a certain amount of time
        decrementAmount++;

        // The time is decremented with a delay so the time is not decremented too fast
        if (decrementAmount > 10)
        {
            osDelay(TIMER_CHANGE_FAST_DELAY);
        }
        else
        {
            osDelay(TIMER_CHANGE_DELAY);
        }
    }

    // Return to the previous state
    Timer_EingerichteteZeitAnzeigen();
}

void Timer_AktuelleZeitAnzeigen()
{
    StartTimer();

    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, &Timer_Pausieren);
    Set_Taster_Callback(TASTER_3, &Timer_EingerichteteZeitAnzeigen);
}

void Timer_Pausieren()
{
    PauseTimer();

    Set_Taster_Callback(TASTER_1, &Timer_AktuelleZeitAnzeigen);
    Set_Taster_Callback(TASTER_2, NULL);
    Set_Taster_Callback(TASTER_3, &Timer_EingerichteteZeitAnzeigen);
}

void Timer_TimerAbgelaufen()
{
    // Disable all taster callbacks so the user can't change the state while the buzzer is active
    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, NULL);
    Set_Taster_Callback(TASTER_3, NULL);

    // Activate the buzzer for 3 seconds
    Buzzer_Beep(3000);

    // Return to the taster and allow configuration again
    Timer_EingerichteteZeitAnzeigen();
    currentState = STATE_TIMER;
    hasStateChanged = true;
}

#pragma endregion

// Change the state to the other state
// This will restore the previous state
void ChangeState()
{
    // Change the state to the other state
    if (currentState == STATE_STOPWATCH)
    {
        // Find out which state was active before the stopwatch state
        if (IsConfiguringTimer())
        {
            Timer_EingerichteteZeitAnzeigen();
        }
        else if (IsTimeUp())
        {
            Timer_TimerAbgelaufen();
        }
        else if (IsTimerPaused())
        {
            Timer_Pausieren();
        }
        else
        {
            Timer_AktuelleZeitAnzeigen();
        }

        currentState = STATE_TIMER;
    }
    else
    {
        // Find out which state was active before the timer state
        if (IsShowingIntermediateTime())
        {
            Stoppuhr_ZwischenzeitAnzeigen();
        }
        else if (IsStopwatchRunning())
        {
            Stoppuhr_AktuelleZeitAnzeigen();
        }
        else if (GetStopwatchTime() > 0)
        {
            Stoppuhr_EndzeitAnzeigen();
        }
        else
        {
            Stoppuhr_LeereZeitAnzeigen();
        }

        currentState = STATE_STOPWATCH;
    }

    // The state was changed
    hasStateChanged = true;
}

// Initialize the state event
void InitStateEvent()
{
    // Reset both processes
    ResetStopwatch();
    ResetTimer();

    // Set the callback for the timer is up
    SetTimerUpCallback(&Timer_TimerAbgelaufen);

    // Set the callback to change the state
    Set_Taster_Long_Callback(TASTER_1, NULL);
    Set_Taster_Long_Callback(TASTER_2, NULL);
    Set_Taster_Long_Callback(TASTER_3, &ChangeState);

    // Initialize the state to the stopwatch state
    Stoppuhr_LeereZeitAnzeigen();

    // At the beginning, the state is the stopwatch state
    currentState = STATE_STOPWATCH;
}

// Show the current state on the LEDs
// This function should be called every 50ms
void ShowLedState()
{
    // Check if the LED should blink (2 Hz)
    static int cycleCounter = 0;
    static bool shouldBlink = false;

    // 2 Hz are 500 miliseconds
    // 500 miliseconds / 50 (delay of the Task) = 10 / 2 (blinking) = 5
    cycleCounter++;
    if (cycleCounter == 5)
    {
        // Toggle the blinker state
        cycleCounter = 0;
        shouldBlink = true;
    }

    // LED 1 leuchtet, wenn die Stoppuhr angezeigt wird.
    LED_Set(LED_1, currentState == STATE_STOPWATCH);

    // LED 2 leuchtet, wenn die Timerzeit angezeigt wird.
    LED_Set(LED_2, currentState == STATE_TIMER);

    // LED 3 leuchtet wenn die Stoppuhr gestartet wurde & blinkt (2Hz) wenn eine Zwischenzeit aktiv ist.
    if (IsStopwatchRunning())
    {
        if (!IsShowingIntermediateTime())
        {
            LED_Set(LED_3, true);
        }
        else if (shouldBlink)
        {
            LED_Toggle(LED_3);
        }
    }
    else
    {
        LED_Set(LED_3, false);
    }

    // LED 4 blinkt immer mit (2 Hz) «System running».
    if (shouldBlink)
    {
        LED_Toggle(LED_4);

        // Reset the blinker state
        shouldBlink = false;
    }
}

// Shows the current time of the current state on the display
void ShowCurrentTime()
{
    // Check if the display should blink
    if (hasStateChanged)
    {
        static int cycleCounter = 0;
        cycleCounter++;
        // 1'000 miliseconds / 50 (delay of the Task) = 20
        if (cycleCounter == 20)
        {
            // Reset the state change
            cycleCounter = 0;
            hasStateChanged = false;
        }
    }

    // Show the time of the current state
    if (currentState == STATE_STOPWATCH)
    {
        if (hasStateChanged)
        {
            Display_Flash_Time(GetStopwatchTime(), FAST);
        }
        else if (IsShowingIntermediateTime())
        {
            Display_Flash_Time(GetStopwatchTime(), SLOW);
        }
        else
        {
            Display_Time(GetStopwatchTime());
        }
    }
    else if (currentState == STATE_TIMER)
    {
        if (hasStateChanged)
        {
            Display_Flash_Time(GetTimerTime(), FAST);
        }
        else if (IsTimeUp())
        {
            Display_Flash_Time(GetTimerTime(), SLOW);
        }
        else if (IsTimerPaused())
        {
            Display_Flash_Time(GetTimerTime(), SLOW);
        }
        else
        {
            Display_Time(GetTimerTime());
        }
    }
}

//  ---------------------------------------
//  5.     G L O B A L    F U N C T I O N S
//  ---------------------------------------

// The background task to initialize the state event
void StateEventTask(void *argument)
{
    // Initialize the state event at the beginning
    InitStateEvent();

    while (true)
    {
        // Show the current state on the LEDs
        ShowLedState();

        // Show the current time of the current state on the display
        ShowCurrentTime();

        // Wait 50ms before updating the state again
        osDelay(50);
    }
}
