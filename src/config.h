#include <avr/wdt.h>

/********************* RECEIVER *********************/
#define RECEIVER_PIN 14

/********************* MPU *********************/
#define MPU_ADDR 0x68

#define CALIBRATION_TICK_NUMBER 1000
#define CALIBRATION_BEGINNING_CODE "calibration_start"
#define CALIBRATION_SUCCESS_CODE "calibration_success"

/********************* COMMANDS *********************/
#define SERVO1_PIN 9
#define SERVO2_PIN 10

#define MOTOR1_PIN 13
#define MOTOR2_PIN 14

#define MOTOR_RADIO_CHANNEL 2 // Between 0 and ~5 

#define SERVO_MAX_CLEARANCE 45 // output servo via controller is 90-SERVO_MAX_CLEARANCE < out < 90+SERVO_MAX_CLEARANCE

// servo config
#define SERVO_MIN_MICROSECONDS 544
#define SERVO_MAX_MICROSECONDS 2400

// binding each airplane part with board pin
#define LEFT_AILERON_SERVO_PIN SERVO1_PIN
#define RIGHT_AILERON_SERVO_PIN SERVO2_PIN

/********************* LED *********************/
#define BOARD_LED_PIN 11

// mode config
#define SLOW_BLINK_FREQUENCY 1000 // = half-period
#define FAST_BLINK_FREQUENCY 200

/********************* WATCHDOG *********************/
#define WDTO_TIME WDTO_60MS

/********************* DEBUG *********************/
// #define ENABLE_DEBUG