#include <Arduino.h>

#include "../config.h"

#ifndef ATTITUDE_H
    #define ATTITUDE_H

   class ImuSensor {

        public:

            int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
            double gyroXOffset, gyroYOffset, gyroZOffset;
            unsigned long last_time_capture;
            double pitch, roll;

            void init();
            void tick();
            void loadGyroOffsets ();
            void calibrateGyroOffsets ();
            void printAttitude();

   };

#endif