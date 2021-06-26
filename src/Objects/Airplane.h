#include <Servo.h>

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    typedef struct Airplane {

        Servo aileronServo;
        Servo elevatorServo;

    } Airplane;

    void initAirplane (Airplane *airplane);

#endif