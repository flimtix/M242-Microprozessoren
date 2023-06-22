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

#define TIMER_INCREMENT_DELAY 150

// The current running state
static enum State currentState = STATE_STOPWATCH;

// Check if the state was changed recently
static bool stateChanged = false;

//  -------------------------------------------
//  4.     I N T E R N A L    F U N C T I O N S
//  -------------------------------------------

#pragma region Stopwatch State Handling

// List all possible events so they can be called out of order
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
    ShowIntermediateTime();

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

void Timer_EingerichteteZeitAnzeigen();
void Timer_ZeitErhoehen();
void Timer_ZeitVerringern();
void Timer_AktuelleZeitAnzeigen();
void Timer_Pausieren();
void Timer_TimerAbgelaufen();

void Timer_EingerichteteZeitAnzeigen()
{
    if (IsTimerRunning())
    {
        ResetTimer();
    }

    Set_Taster_Callback(TASTER_1, &Timer_ZeitErhoehen);
    Set_Taster_Callback(TASTER_2, &Timer_ZeitVerringern);
    Set_Taster_Callback(TASTER_3, &Timer_AktuelleZeitAnzeigen);
}

void Timer_ZeitErhoehen()
{
    // Die Zeit solange erhöhen, bis der Taster losgelassen wird
    while (Taster_Get(TASTER_1))
    {
        IncrementTime();

        // Die Zeit wird mit einem delay erhöht, damit die Zeit nicht zu schnell erhöht wird
        osDelay(TIMER_INCREMENT_DELAY);
    }

    // Zurück zum vorherigen Status
    Timer_EingerichteteZeitAnzeigen();
}

void Timer_ZeitVerringern()
{
    // Die Zeit solange verringern, bis der Taster losgelassen wird
    while (Taster_Get(TASTER_2))
    {
        DecrementTime();

        // Die Zeit wird mit einem delay verringert, damit die Zeit nicht zu schnell verringert wird
        osDelay(TIMER_INCREMENT_DELAY);
    }

    // Zurück zum vorherigen Status
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

    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, &Timer_AktuelleZeitAnzeigen);
    Set_Taster_Callback(TASTER_3, &Timer_EingerichteteZeitAnzeigen);
}

void Timer_TimerAbgelaufen()
{
    // Status kann während der Ausführung nicht geändert werden
    Set_Taster_Callback(TASTER_1, NULL);
    Set_Taster_Callback(TASTER_2, NULL);
    Set_Taster_Callback(TASTER_3, NULL);

    // Buzzer für 3 Sekunden aktivieren
    Buzzer_Beep(3000);

    // Zurück zum einrichten der Zeit
    Timer_EingerichteteZeitAnzeigen();
}

#pragma endregion

// Change the state to the other state
// This will stop the current state and start the other state
// Supported states are in the enum State
// This function should be called when TASTER_3 is pressed long
void ChangeState()
{
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
        else if (IsTimerRunning())
        {
            Timer_AktuelleZeitAnzeigen();
        }
        else
        {
            Stoppuhr_EndzeitAnzeigen();
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
        else
        {
            Stoppuhr_LeereZeitAnzeigen();
        }

        currentState = STATE_STOPWATCH;
    }

    // The state was changed
    stateChanged = true;
}

// Initialize the state event
void InitStateEvent()
{
    // Reset both processes
    ResetStopwatch();
    ResetTimer();

    // At the beginning, the state is the stopwatch state
    currentState = STATE_STOPWATCH;

    // Set the callback for the timer is up
    SetTimerUpCallback(&Timer_TimerAbgelaufen);

    // Set the callback to change the state
    Set_Taster_Long_Callback(TASTER_3, &ChangeState);

    // Initialize the state to the stopwatch state
    Stoppuhr_LeereZeitAnzeigen();
}

// Show the current state on the LEDs
// This function should be called every 50ms
void ShowLedState()
{
    // Check if the LED should blink (2 Hz)
    static int cycleCounter = 0;
    static bool shouldBlink = false;

    // 2 Hz are 2'000 miliseconds
    // 2'000 miliseconds / 50 (delay of the Task) = 40
    cycleCounter++;
    if (cycleCounter == 40)
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
    if (stateChanged)
    {
        static int cycleCounter = 0;
        cycleCounter++;
        // 1'000 miliseconds / 50 (delay of the Task) = 20
        if (cycleCounter == 20)
        {
            // Reset the state change
            cycleCounter = 0;
            stateChanged = false;
        }
    }

    // Show the time of the current state
    if (currentState == STATE_STOPWATCH)
    {
        if (stateChanged)
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
        if (stateChanged)
        {
            Display_Flash_Time(GetTimerTime(), FAST);
        }
        else if (IsTimeUp())
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
