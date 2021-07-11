#include <Arduino.h>
#include "EEPROM.h"

#include "../config.h"
#include "../memoryConfig.h"
#include "./Board/Board.h"
#include "../error.h"

#include "./Airplane.h"

Airplane::Airplane () {

    pinMode(AILERON_SERVO_PIN, OUTPUT);
    aileronServo.attach(AILERON_SERVO_PIN);

    pinMode(ELEVATOR_SERVO_PIN, OUTPUT);
    elevatorServo.attach(ELEVATOR_SERVO_PIN);

    pinMode(THROTTLE_SERVO_PIN, OUTPUT);
    throttleServo.attach(THROTTLE_SERVO_PIN);

    pinMode(RUDDER_SERVO_PIN, OUTPUT);
    rudderServo.attach(RUDDER_SERVO_PIN);


    // Binding the airplane attitude with the board attitude
    byte pitch_axis_reference = EEPROM.read(PITCH_AXIS_REFERENCE_LOCATION);
    byte roll_axis_reference = EEPROM.read(PITCH_AXIS_REFERENCE_LOCATION);

    if (pitch_axis_reference == X_AXIS) {
        pitchPt = &(board.imuSensor.x);
    }else if (pitch_axis_reference == Y_AXIS) {
        pitchPt = &(board.imuSensor.y);
    }else if (pitch_axis_reference == Z_AXIS) {
        pitchPt = &(board.imuSensor.z);
    }else{
        configurationError();
    }

    if (roll_axis_reference == X_AXIS) {
        rollPt = &(board.imuSensor.x);
    }else if (roll_axis_reference == Y_AXIS) {
        rollPt = &(board.imuSensor.y);
    }else if (roll_axis_reference == Z_AXIS) {
        rollPt = &(board.imuSensor.z);
    }else{
        configurationError();
    }

    byte reverse_pitch_axis = EEPROM.read(REVERSE_PITCH_AXIS_LOCATION);
    byte reverse_roll_axis = EEPROM.read(REVERSE_ROLL_AXIS_LOCATION);

    if (reverse_pitch_axis == NOT_REVERSED) {
        pitchCoef = 1;
    }else if (reverse_pitch_axis == REVERSE) { 
        pitchCoef = -1;
    }else {
        configurationError();
    }

    if (reverse_roll_axis == NOT_REVERSED) {
        rollCoef = 1;
    }else if (reverse_roll_axis == REVERSE) { 
        rollCoef = -1;
    }else {
        configurationError();
    }

}

void Airplane::getPitch() {
    pitch = (*pitchPt) * pitchCoef;
}

void Airplane::getRoll() {
    roll = (*rollPt) * rollCoef;
}

void Airplane::tick () {
    board.imuSensor.tick();
}