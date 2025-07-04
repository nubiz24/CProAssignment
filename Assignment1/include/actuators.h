#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "config.h"

void init_actuators();
void turn_pump_on();
void turn_pump_off();
void set_led_state(LedState state);
void update_led_status();
void report_status();

#endif
