#include <avr/wdt.h>

/********************* PROGRAM INFO *********************/
#define VERSION 1.0-dev
#define AUTHOR Mathis REVENU

/********************* RECEIVER *********************/
#define AILERON_INPUT 9
#define ELEVATOR_INPUT 9
#define THROTTLE_INPUT 9
#define RUDDER_INPUT 9
#define SWITCH1_INPUT 9
#define SWITCH2_INPUT 9

/********************* ANGLE *********************/
// Number of value taken in count to remove noise from vivration
#define ANGLE_HISTORY_TO_MEAN 10

/********************* MPU *********************/
#define MPU_ADDR 0x68

/********************* COMMANDS *********************/
#define SERVO1_PIN 10
#define SERVO2_PIN 11
#define SERVO3_PIN 12
#define SERVO4_PIN 13

#define SERVO_MAX_CLEARANCE 45 // output servo via controller is 90-SERVO_MAX_CLEARANCE < out < 90+SERVO_MAX_CLEARANCE

// servo config
#define SERVO_MIN_MICROSECONDS 544
#define SERVO_MAX_MICROSECONDS 2400

// binding each airplane part with board pin
#define AILERON_SERVO_PIN SERVO1_PIN
#define ELEVATOR_SERVO_PIN SERVO2_PIN
#define THROTTLE_SERVO_PIN SERVO3_PIN
#define RUDDER_SERVO_PIN SERVO4_PIN

/********************* LED *********************/
#define BOARD_LED_PIN 7

// mode config
#define SLOW_BLINK_FREQUENCY 1000 // = half-period
#define FAST_BLINK_FREQUENCY 200

/********************* WATCHDOG *********************/
#define WDTO_TIME WDTO_60MS

/********************* DEBUG MODE *********************/
// #define ENABLE_DEBUG

    /******* ANGLE *******/
    // #define PRINT_INSTANT_ANGLE
    // #define PRINT_MEAN_ANGLE