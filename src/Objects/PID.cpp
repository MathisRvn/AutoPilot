#include <Arduino.h>

#include "./PID.h"

PID::PID (double initial_kp, double initial_kd, double target, double current_position) {
    kp = initial_kp;
    kd = initial_kd;
    last_error = target - current_position;
    last_tick = micros();
}

double PID::output (double target, double current_position) {
    now = micros();
    error = target - current_position;
    derivative_error = (error - last_error) / (now - last_tick);
    last_error = error;
    last_tick = now;
    return 1500 + kp * error + kd *  derivative_error;
}