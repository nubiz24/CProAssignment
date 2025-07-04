#include "actuators.h"
#include <stdio.h>

extern SystemState g_system_state;

void init_actuators() {}

void turn_pump_on()
{
    if (g_system_state.pump == PUMP_OFF)
    {
        g_system_state.pump = PUMP_ON;
        printf("Bơm nước: BẬT\n");
    }
}

void turn_pump_off()
{
    if (g_system_state.pump == PUMP_ON)
    {
        g_system_state.pump = PUMP_OFF;
        printf("Bơm nước: TẮT\n");
    }
}

void set_led_state(LedState state)
{
    g_system_state.led = state;
}

void update_led_status()
{
    switch (g_system_state.led)
    {
    case LED_NORMAL:
        printf("LED: Xanh (Bình thường)\n");
        break;
    case LED_WATERING:
        printf("LED: Vàng (Đang tưới)\n");
        break;
    case LED_LOW_MOISTURE_ALERT:
        printf("LED: Đỏ (Độ ẩm thấp)\n");
        break;
    case LED_ERROR:
        printf("LED: Đỏ nhấp nháy (Lỗi)\n");
        break;
    }
}

void report_status()
{
    printf("[STATUS] Chế độ: %s | Bơm: %s\n",
           g_system_state.mode == MODE_AUTO ? "Tự động" : "Thủ công",
           g_system_state.pump == PUMP_ON ? "BẬT" : "TẮT");
}
