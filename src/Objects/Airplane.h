#include <Servo.h>

#include "./Board/Board.h"
#include "./Receiver.h"
#include "./Attitude.h"

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    class Airplane {

        public:
        
            Servo leftAileronServo;
            Servo rightAileronServo;

            Board board;

            Receiver *receiver;

            Airplane(Receiver *initial_receiver);

            void tick ();

            void getPitch();
            void getRoll();

    };

#endif