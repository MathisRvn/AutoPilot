#include <Arduino.h>

#include "../config.h"
#include "./Mixer.h"

Mixer::Mixer(Servo *initial_servo) { servo = initial_servo; }

void Mixer::tick(int axis1, int axis2) {

    axis1 = microseconds_to_deg(axis1);
    axis2 = microseconds_to_deg(axis2);

    // TODO : Improve this calculation method
    // Serial.println((axis1 + axis2) / 2);

    output = axis1 + axis2 - 90;

    if (output > 90 + SERVO_MAX_CLEARANCE) {
        output = 90 + SERVO_MAX_CLEARANCE;
    }else if (output < SERVO_MAX_CLEARANCE) {
        output = SERVO_MAX_CLEARANCE;
    }

    servo->write(output); // Mean of the two inputs

}

int microseconds_to_deg (int microseconds) {
    // Reverse engineer Servo.write function
    return map(microseconds, SERVO_MIN_MICROSECONDS, SERVO_MAX_MICROSECONDS, 0, 180);
}