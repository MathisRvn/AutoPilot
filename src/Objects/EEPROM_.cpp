#include <Wire.h>
#include <EEPROM.h>

#include "./EEPROM_.h"

// INTERNAL EEPROM

void INTERNAL_EEPROM::writeByte(uint8_t addr, byte x) {
    EEPROM.write(addr, x);
}

byte INTERNAL_EEPROM::readByte(uint8_t addr) {
    return EEPROM.read(addr);
}

void INTERNAL_EEPROM::write2Byte(uint8_t addr, uint16_t x) {
    EEPROM.write(addr, x & 0xFF);
    EEPROM.write(addr + 1, (x >> 8) & 0xFF);
}

uint16_t INTERNAL_EEPROM::read2Byte(uint8_t addr) {
    uint16_t x = EEPROM.read(addr);
    x |= EEPROM.read(addr + 1) << 8;
    return x;
}

// I2C EEPROM 

I2C_EEPROM::I2C_EEPROM(byte I2C_addr) {
    this->I2C_addr = I2C_addr;
    Wire.begin();
}

void I2C_EEPROM::writeByte(uint16_t addr, byte x) {

    // Look datasheet for protocol : https://datasheet.lcsc.com/lcsc/1809171607_onsemi-CAT24M01WI-GT3_C62273.pdf

    Wire.beginTransmission(I2C_addr);

    // Send memory address
    Wire.write(addr >> 8);
    Wire.write(addr & 0xFF);

    // Send data
    Wire.write(x);

    Wire.endTransmission();

}

byte I2C_EEPROM::readByte(uint16_t addr) {

    // Look datasheet for protocol : https://datasheet.lcsc.com/lcsc/1809171607_onsemi-CAT24M01WI-GT3_C62273.pdf

    Wire.beginTransmission(I2C_addr);

    // Send memory address
    Wire.write(addr >> 8);
    Wire.write(addr & 0xFF);

    Wire.endTransmission();

    Wire.requestFrom(I2C_addr, 1);

    return Wire.read();

}

void I2C_EEPROM::write4Bytes(uint16_t addr, uint32_t x) {
    
        // Look datasheet for protocol : https://datasheet.lcsc.com/lcsc/1809171607_onsemi-CAT24M01WI-GT3_C62273.pdf
    
        Wire.beginTransmission(I2C_addr);
    
        // Send memory address
        Wire.write(addr >> 8);
        Wire.write(addr & 0xFF);
    
        // Send data
        Wire.write(x & 0xFF);
        Wire.write((x >> 8) & 0xFF);
        Wire.write((x >> 16) & 0xFF);
        Wire.write((x >> 24) & 0xFF);
    
        Wire.endTransmission();
    
}

uint32_t I2C_EEPROM::read4Bytes(uint16_t addr) {

    // Look datasheet for protocol : https://datasheet.lcsc.com/lcsc/1809171607_onsemi-CAT24M01WI-GT3_C62273.pdf

    Wire.beginTransmission(I2C_addr);

    // Send memory address
    Wire.write(addr >> 8);
    Wire.write(addr & 0xFF);

    Wire.endTransmission();

    Wire.requestFrom(I2C_addr, 4);

    uint32_t x = Wire.read();
    x |= Wire.read() << 8;
    x |= Wire.read() << 16;
    x |= Wire.read() << 24;

    return x;

}