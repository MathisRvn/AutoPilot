#include <avr/wdt.h>

/********************* RECEIVER *********************/
#define AILERON_INPUT 14
#define ELEVATOR_INPUT 15
#define THROTTLE_INPUT 16
#define RUDDER_INPUT 17
#define SWITCH1_INPUT 8
#define SWITCH2_INPUT 7

/********************* MPU *********************/
#define MPU_ADDR 0x68

#define CALIBRATION_TICK_NUMBER 1000
#define CALIBRATION_BEGINNING_CODE "calibration_start"
#define CALIBRATION_SUCCESS_CODE "calibration_success"

/********************* COMMANDS *********************/
#define SERVO1_PIN 5
#define SERVO2_PIN 6
#define SERVO3_PIN 9
#define SERVO4_PIN 10

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
#define BOARD_LED_PIN 11

// mode config
#define SLOW_BLINK_FREQUENCY 1000 // = half-period
#define FAST_BLINK_FREQUENCY 200

/********************* WATCHDOG *********************/
#define WDTO_TIME WDTO_60MS

/********************* DEBUG *********************/
// #define ENABLE_DEBUG