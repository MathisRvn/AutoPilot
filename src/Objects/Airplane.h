#include <Servo.h>

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    typedef struct Airplane {

        Servo aileronServo;
        Servo elevatorServo;
        Servo throttleServo;
        Servo rudderServo;


    } Airplane;

    void initAirplane (Airplane *airplane);

#endif