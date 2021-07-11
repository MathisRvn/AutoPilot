#include <Servo.h>

#include "./Board/Board.h"

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    class Airplane {

        public:
        
            Servo aileronServo;
            Servo elevatorServo;
            Servo throttleServo;
            Servo rudderServo;

            Board board;

            double *pitchPt, *rollPt;
            double pitch, roll;

            uint8_t pitchCoef;
            uint8_t rollCoef;

            Airplane();

            void tick ();

            void getPitch();
            void getRoll();

    };

#endif