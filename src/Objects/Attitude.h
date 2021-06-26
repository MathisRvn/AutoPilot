#include <Arduino.h>

#include "../config.h"

#ifndef ATTITUDE_H
    #define ATTITUDE_H

    typedef struct Angle {
        double pitch, roll; // (Yaw = Z axis); Pitch = Y axis; Roll = X axis
    } Angle;

    #define NEW_ANGLE(name, pitch, roll) Angle name = {pitch, roll}

    #ifdef ENABLE_DEBUG
        void printAngle(Angle *angle);
    #endif

    typedef struct AngleHistory {
        Angle history[ANGLE_HISTORY_TO_MEAN];
        short current_index;
    } AngleHistory;

    void initAngleHistory(AngleHistory *angleHistory, Angle initial_angle);
    void addNewAngle(AngleHistory *angleHistory, Angle newAngle);
    Angle getMeanAngle(AngleHistory *angleHistory);

    typedef struct Attitude {

        int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
        double rpitch, rroll;
        Angle instant_angle;
        Angle angle;
        AngleHistory history;

    } Attitude;

    void initAttitude (Attitude *attitude);
    void updateInstantAttitude (Attitude *attitude);
    void updateMeanAngle (Attitude *attitude);

#endif