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

    // Đọc cảm biến mỗi lần gọi hàm
    SensorData data = read_sensor_data();

    // Kiểm tra dữ liệu không hợp lệ
    if (data.soil_moisture_percent > 100 || data.soil_moisture_percent < 0)
    {
        set_led_state(LED_ERROR);
        turn_pump_off();
        g_system_state.is_manual_watering = false;
        printf("Lỗi cảm biến: Độ ẩm hoặc nhiệt độ không hợp lệ.\n");
        return;
    }

    // Chế độ thủ công
    if (g_system_state.is_manual_watering)
    {
        if (g_system_state.pump == PUMP_OFF)
        {
            turn_pump_on();
            set_led_state(LED_WATERING);
            pump_start = now;
            g_system_state.last_watering_time = now;
        }
        else if (now - pump_start >= WATERING_DURATION_MS / 1000)
        {
            turn_pump_off();
            set_led_state(LED_NORMAL);
            g_system_state.is_manual_watering = false;
        }
        return;
    }

    // Chế độ tự động
    if (now - last_check >= SENSOR_CHECK_INTERVAL_MS / 1000)
    {
        last_check = now;
        printf("Độ ẩm đất: %d%% | Nhiệt độ: %.1f°C\n",
               data.soil_moisture_percent, data.temperature_celsius);

        if (data.soil_moisture_percent < HUMIDITY_MIN_THRESHOLD &&
            now - g_system_state.last_watering_time >= SENSOR_CHECK_INTERVAL_MS / 1000)
        {
            turn_pump_on();
            set_led_state(LED_WATERING);
            pump_start = now;
            g_system_state.last_watering_time = now;
        }
        else if (data.soil_moisture_percent > HUMIDITY_MAX_THRESHOLD)
        {
            turn_pump_off();
            set_led_state(LED_NORMAL);
        }
        else if (data.soil_moisture_percent < HUMIDITY_MIN_THRESHOLD)
        {
            set_led_state(LED_LOW_MOISTURE_ALERT); // Độ ẩm thấp nhưng chưa tưới do giới hạn thời gian
        }
        else
        {
            if (g_system_state.pump == PUMP_OFF)
            {
                set_led_state(LED_NORMAL);
            }
        }
    }

    // Kiểm soát thời gian tưới
    if (g_system_state.pump == PUMP_ON && now - pump_start >= WATERING_DURATION_MS / 1000)
    {
        turn_pump_off();
        set_led_state(LED_NORMAL);
    }
}