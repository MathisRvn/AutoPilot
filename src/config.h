/********************* PROGRAM INFO *********************/
#define VERSION 1.0-dev
#define AUTHOR Mathis REVENU

/********************* RECEIVER *********************/
#define CH1_INPUT 9
#define CH2_INPUT 9
#define CH3_INPUT 9
#define CH4_INPUT 9
#define CH5_INPUT 9
#define CH6_INPUT 9

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

/********************* DEBUG MODE *********************/
// #define ENABLE_DEBUG

    /******* ANGLE *******/
    // #define PRINT_INSTANT_ANGLE
    // #define PRINT_MEAN_ANGLE