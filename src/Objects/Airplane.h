#include <Servo.h>

#include "./Board/Board.h"
#include "./Receiver.h"

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    class Airplane {

        public:
        
            Servo leftAileronServo;
            Servo rightAileronServo;

            Board board;

            Receiver *receiver;

            double *pitchPt, *rollPt;
            double pitch, roll;

            uint8_t pitchCoef;
            uint8_t rollCoef;

            Airplane(Receiver *initial_receiver);

            void tick ();

            void getPitch();
            void getRoll();

    };

#endif