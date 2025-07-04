#include "sensors.h"
#include <stdlib.h>
#include <time.h>

void init_sensors()
{
    srand(time(NULL));
}

SensorData read_sensor_data()
{
    SensorData data;
    data.soil_moisture_percent = rand() % 101;      // 0-100%
    data.temperature_celsius = 20.0f + rand() % 15; // 20-35°C
    return data;
}
