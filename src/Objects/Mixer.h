#include <Servo.h>

#ifndef MIXER_H
    #define MIXER_H

    class Mixer {

        public:

            Servo *servo;

            int output = 0;

            Mixer(Servo *initial_servo);
            void tick(int axis1, int axis2);

    };

    int microseconds_to_deg (int microseconds);

#endif