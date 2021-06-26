#include <Arduino.h>

#include "../config.h"

#include "./Airplane.h"

void initAirplane (Airplane *airplane) {

    pinMode(AILERON_SERVO_PIN, OUTPUT);
    airplane->aileronServo.attach(AILERON_SERVO_PIN);

    pinMode(ELEVATOR_SERVO_PIN, OUTPUT);
    airplane->elevatorServo.attach(ELEVATOR_SERVO_PIN);

    pinMode(THROTTLE_SERVO_PIN, OUTPUT);
    airplane->throttleServo.attach(THROTTLE_SERVO_PIN);

    pinMode(RUDDER_SERVO_PIN, OUTPUT);
    airplane->rudderServo.attach(RUDDER_SERVO_PIN);

}