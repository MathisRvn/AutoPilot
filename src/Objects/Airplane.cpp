#include <Arduino.h>

#include "../config.h"
#include "../memoryConfig.h"
#include "./Board/Board.h"
#include "./Attitude.h"
#include "./Receiver.h"

#include "./Airplane.h"

Airplane::Airplane (Receiver *initial_receiver) {

    receiver = initial_receiver;

    pinMode(LEFT_AILERON_SERVO_PIN, OUTPUT);
    leftAileronServo.attach(LEFT_AILERON_SERVO_PIN);

    pinMode(RIGHT_AILERON_SERVO_PIN, OUTPUT);
    rightAileronServo.attach(RIGHT_AILERON_SERVO_PIN);

}