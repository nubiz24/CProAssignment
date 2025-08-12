#include "config.h"
#include "actuators.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern SystemState g_system_state;

void init_buttons() {}

void process_buttons()
{
    char input;
    printf("Nhấn 'a' để chuyển chế độ | 'm' để tưới thủ công: ");
    input = getchar();
    getchar(); // clear buffer

    if (input == 'a')
    {
        g_system_state.mode = (g_system_state.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        if (g_system_state.mode == MODE_MANUAL)
        {
            turn_pump_off();
        }
    }
    else if (input == 'm' && g_system_state.mode == MODE_MANUAL)
    {
        g_system_state.is_manual_watering = true;
    }
}
