#include <Servo.h>

#include "./Receiver.h"
#include "./PID.h"
#include "./Attitude.h"

#ifndef CONTROLLER_H
    #define CONTROLLER_H

    typedef enum ControlMode {
        INPUT_COPY,
        PID_CONTROLLER
    } ControlMode;

    class Controller {

        public:
            Servo *servo;
            ReceiverPwmChannel *receiverPwmChannel;
            ControlMode mode;
            PID *pid;

            Controller(Servo *initial_servo, 
                        ReceiverPwmChannel *initial_receiverPwmChannel, 
                        ControlMode initial_mode,
                        PID *initial_pid);

            void tick (double axis_angle);
            void tick (void);

    };

    double microseconds_to_deg (unsigned long microseconds);

#endif