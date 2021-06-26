#include <Arduino.h>

#include "../config.h"

#include "./Airplane.h"

void initAirplane (Airplane *airplane) {
    airplane->aileronServo.attach(AILERON_SERVO_PIN);
    airplane->elevatorServo.attach(ELEVATOR_SERVO_PIN);
}