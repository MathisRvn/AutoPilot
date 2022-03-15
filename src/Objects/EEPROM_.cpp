#include <EEPROM.h>

#include "./EEPROM_.h"

double readEepromDouble(unsigned int addr) {
    union {
        byte b[4];
        double f;
    } data;

    for(int i = 0; i < 4; i++) {
        data.b[i] = EEPROM.read(addr+i);
    }

    return data.f;
}


void writeEepromDouble(unsigned int addr, double x) {
    union {
        byte b[4];
        double f;
    } data;

    data.f = x;
    for(int i = 0; i < 4; i++) {
        EEPROM.write(addr+i, data.b[i]);
    }
}