#ifndef EEPROM_H_
    #define EEPROM_H_

    typedef uint8_t byte;

    double readEepromDouble(unsigned int addr);
    void writeEepromDouble(unsigned int addr, double x);

#endif