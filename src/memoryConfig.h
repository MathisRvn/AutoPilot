/*

I just keep this as example

#define GYRO_X_OFFSET_LOCATION 0x10
#define GYRO_Y_OFFSET_LOCATION 0x14 // Because a double is 4 bytes long (atmega328)
#define GYRO_Z_OFFSET_LOCATION 0x18

#define X_AXIS 0x01
#define Y_AXIS 0x02
#define Z_AXIS 0x03
#define PITCH_AXIS_REFERENCE_LOCATION 0x22
#define ROLL_AXIS_REFERENCE_LOCATION 0x23

#define NOT_REVERSED 1
#define REVERSE 2
#define REVERSE_PITCH_AXIS_LOCATION 0x24
#define REVERSE_ROLL_AXIS_LOCATION 0x25

*/

// TODO inplement memory


#define I2C_EEPROM_ADDR 0x50

#define MEMORY_CURSOR_ADDR 0x00
#define EXT_MEMORY_SIZE 256