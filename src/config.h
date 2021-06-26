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
#define AILERON_SERVO_PIN 10
#define ELEVATOR_SERVO_PIN 11

/********************* LED *********************/
#define BOARD_LED_PIN 7
#define SLOW_BLINK_FREQUENCY 1000 // = half-period
#define FAST_BLINK_FREQUENCY 200

/********************* DEBUG MODE *********************/
// #define ENABLE_DEBUG

    /******* ANGLE *******/
    // #define PRINT_INSTANT_ANGLE
    // #define PRINT_MEAN_ANGLE