#include "../include/config.h"
#include "../include/sensors.h"
#include "../include/actuators.h"
#include "../include/buttons.h"
#include "../include/watering_logic.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

SystemState g_system_state;

int main()
{
    init_sensors();
    init_actuators();
    init_buttons();

    g_system_state.mode = MODE_AUTO;
    g_system_state.pump = PUMP_OFF;
    g_system_state.led = LED_NORMAL;
    g_system_state.is_manual_watering = false;
    g_system_state.last_watering_time = 0;

    while (1)
    {
        process_buttons();

        if (g_system_state.mode == MODE_AUTO)
        {
            automatic_watering_logic();
        }

        update_led_status();
        report_status();

        usleep(500 * 1000); // 500ms delay
    }

    return 0;
}
