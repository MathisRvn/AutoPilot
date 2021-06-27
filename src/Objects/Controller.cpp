#include <Arduino.h>
#include <Servo.h>

#include "config.h"
#include "./PID.h"
#include "Attitude.h"

#include "./Controller.h"

Controller::Controller (Servo *initial_servo, 
                        ReceiverPwmChannel *initial_receiverPwmChannel, 
                        ControlMode initial_mode,
                        PID *initial_pid)
{
    servo = initial_servo;
    receiverPwmChannel = initial_receiverPwmChannel;
    mode = initial_mode;
    pid = initial_pid;
}

void Controller::tick (double axis_angle) {

    if (mode == PID_CONTROLLER) {
        double desiredAngle = microseconds_to_deg(receiverPwmChannel->value);
        double out = this->pid->output(desiredAngle, axis_angle);
        servo->write(out);
    }else{ // == INPUT_COPY
        servo->writeMicroseconds(receiverPwmChannel->value);
    }

}

void Controller::tick () {
    servo->writeMicroseconds(receiverPwmChannel->value);
}

double microseconds_to_deg (unsigned long microseconds) {
    // Reverse engineer Servo.write function
    return map(microseconds, SERVO_MIN_MICROSECONDS, SERVO_MAX_MICROSECONDS, 0, 180);
}