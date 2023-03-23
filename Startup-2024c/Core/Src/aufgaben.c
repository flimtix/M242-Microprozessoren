
void TimeSlice()
{
    int counter_ms = 0;
    int counter_sek = 0;
    int counter_min = 0;
    int counter_hour = 0;
    for (;;)
    {
        counter_ms++;
        if (!(counter_ms % 100))
        {
            counter_sek++;

            if (!(counter_sek % 60))
            {
                counter_min++;

                if (!(counter_min % 60))
                {
                    counter_hour++;
                }
            }
        }
        osDelay(10);
    }
}

void ToggleLed()
{
    for (;;)
    {
        // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(1000);
    }
}
