#ifndef EEPROM_H_
    #define EEPROM_H_

    typedef uint8_t byte;

    class INTERNAL_EEPROM {

        public:

            INTERNAL_EEPROM();

            void writeByte(uint8_t addr, byte x);
            byte readByte(uint8_t addr);

            void write2Byte(uint8_t addr, uint16_t x);
            uint16_t read2Byte(uint8_t addr);

    };

    class I2C_EEPROM {

        public:

            I2C_EEPROM(byte I2C_addr);

            byte I2C_addr = 0x50;

            void writeByte(uint16_t addr, byte x);
            byte readByte(uint16_t addr);

            void write2Byte(uint8_t addr, uint16_t x);
            uint16_t read2Byte(uint8_t addr);

    };

#endif