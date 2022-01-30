#include <Arduino.h>

#include "../config.h"
#include "../memoryConfig.h"
#include "./Attitude.h"
#include "./Receiver.h"

#include "./Airplane.h"

Airplane::Airplane (Receiver *initial_receiver) : infoLed(BOARD_LED_PIN, LED_SLOW_BLINK)
{

    receiver = initial_receiver;

    pinMode(LEFT_AILERON_SERVO_PIN, OUTPUT);
    leftAileronServo.attach(LEFT_AILERON_SERVO_PIN);

    pinMode(RIGHT_AILERON_SERVO_PIN, OUTPUT);
    rightAileronServo.attach(RIGHT_AILERON_SERVO_PIN);

}