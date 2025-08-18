#include "config.h"
#include "actuators.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern SystemState g_system_state;

void init_buttons() {}

int process_buttons()
{
    char input;
    printf("Nhấn 'a' để chuyển chế độ | 'm' để bật/tắt bơm thủ công | Enter để tiếp tục: \n");
    input = getchar();

    if (input == '\n')
    {
        return 0; // Tiếp tục vòng lặp
    }

    // clear buffer nếu nhập ký tự khác Enter
    getchar();

    if (input == 'a')
    {
        g_system_state.mode = (g_system_state.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        if (g_system_state.mode == MODE_MANUAL)
        {
            turn_pump_off();
            g_system_state.is_manual_watering = false;
        }
        return 0;
    }
    else if (input == 'm' && g_system_state.mode == MODE_MANUAL)
    {
        if (g_system_state.is_manual_watering)
        {
            g_system_state.is_manual_watering = false;
            turn_pump_off();
        }
        else
        {
            g_system_state.is_manual_watering = true;
            turn_pump_on();
        }
        return 0;
    }
    else if (input == 'm' && g_system_state.mode == MODE_AUTO)
    {
        printf("Đang ở chế độ AUTO, không thể tưới thủ công.\n");
        return 0;
    }
}