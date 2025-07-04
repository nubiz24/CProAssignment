#include "watering_logic.h"
#include "sensors.h"
#include "actuators.h"
#include "config.h"
#include <time.h>
#include <stdio.h>

extern SystemState g_system_state;

void automatic_watering_logic()
{
    static time_t last_check = 0;
    static time_t pump_start = 0;

    time_t now = time(NULL);

    if (g_system_state.is_manual_watering)
    {
        turn_pump_on();
        set_led_state(LED_WATERING);
        sleep(WATERING_DURATION_MS / 1000);
        turn_pump_off();
        g_system_state.is_manual_watering = false;
        return;
    }

    if (now - last_check >= SENSOR_CHECK_INTERVAL_MS / 1000)
    {
        last_check = now;
        SensorData data = read_sensor_data();
        printf("Độ ẩm đất: %d%% | Nhiệt độ: %.1f°C\n", data.soil_moisture_percent, data.temperature_celsius);

        if (data.soil_moisture_percent < HUMIDITY_MIN_THRESHOLD)
        {
            turn_pump_on();
            set_led_state(LED_WATERING);
            pump_start = now;
        }
    }

    if (g_system_state.pump == PUMP_ON)
    {
        if (now - pump_start >= WATERING_DURATION_MS / 1000)
        {
            turn_pump_off();
            set_led_state(LED_NORMAL);
        }
    }
}
