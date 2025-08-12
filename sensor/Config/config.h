#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#define SENSOR_CHECK_INTERVAL_MS 5000
#define WATERING_DURATION_MS 10000
#define HUMIDITY_MIN_THRESHOLD 30
#define HUMIDITY_MAX_THRESHOLD 60

typedef enum
{
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum
{
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState;

typedef struct
{
    uint8_t soil_moisture_percent;
    float temperature_celsius;
} SensorData;

typedef struct
{
    SystemMode mode;
    PumpState pump;
    LedState led;
    uint32_t last_watering_time;
    bool is_manual_watering;
} SystemState;

extern SystemState g_system_state;

#endif
