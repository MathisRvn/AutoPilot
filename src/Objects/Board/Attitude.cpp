#include<Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>

#include "../../config.h"
#include "../../memoryConfig.h"
#include "./EEPROM_.h"

#include "./Attitude.h"

ImuSensor::ImuSensor() {

    Wire.beginTransmission(MPU_ADDR); 
    Wire.write(0x6B); 
    Wire.write(0); 
    Wire.endTransmission(true);

    x = 90;
    y = 90;
    z = 90;

    loadGyroOffsets();

    last_time_capture = micros();
}

void ImuSensor::tick () {

    const int minVal=265; const int maxVal=402;

    // Talking to the MPU6050
	Wire.beginTransmission(MPU_ADDR); 
  	Wire.write(0x3B); 
  	Wire.endTransmission(false);
  	Wire.requestFrom(MPU_ADDR,14,true); 
  
  	AcX=Wire.read()<<8|Wire.read(); 
  	AcY=Wire.read()<<8|Wire.read(); 
  	AcZ=Wire.read()<<8|Wire.read(); 

    Tmp=Wire.read()<<8|Wire.read();

    GyX=(Wire.read()<<8|Wire.read())/131.0 - gyroXOffset; 
    GyY=(Wire.read()<<8|Wire.read())/131.0 - gyroYOffset; 
    GyZ=(Wire.read()<<8|Wire.read())/131.0 - gyroZOffset;
  
  	int xAng = map(AcX,minVal,maxVal,-90,90); 
  	int yAng = map(AcY,minVal,maxVal,-90,90); 
  	int zAng = map(AcZ,minVal,maxVal,-90,90);

  	// Calculating Angles
  	double accX = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  	double accY = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
    double accZ = RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    accX += 90; // To center the value around 90°
    if (accX >= 360) { accX -= 360; }

    accY += 90;
    if (accY >= 360) { accY -= 360; }

    accZ += 90;
    if (accZ >= 360) { accZ -= 360; }

    double delta_time = (double)(micros() - last_time_capture) / 1000000;
    last_time_capture = micros();

    // Implementing a complementary filter
    x = 0.98 * ( x + GyY * delta_time ) + 0.02 * accX;
    y = 0.98 * ( y + GyX * delta_time ) + 0.02 * accY;
    z = 0.98 * ( z + GyX * delta_time ) + 0.02 * accZ;

}

void ImuSensor::loadGyroOffsets () {
    gyroXOffset = readEepromDouble(GYRO_X_OFFSET_LOCATION);
    gyroYOffset = readEepromDouble(GYRO_Y_OFFSET_LOCATION);
    gyroZOffset = readEepromDouble(GYRO_Z_OFFSET_LOCATION);
}

void ImuSensor::calibrateGyroOffsets () {

    // Resetting present values
    writeEepromDouble(GYRO_X_OFFSET_LOCATION,0.00);
    writeEepromDouble(GYRO_Y_OFFSET_LOCATION,0.00);
    writeEepromDouble(GYRO_Z_OFFSET_LOCATION,0.00);
    loadGyroOffsets();

    double alpha_gyx = 0;
    double alpha_gyy = 0;
    double alpha_gyz = 0;

    for (short i = 0; i < CALIBRATION_TICK_NUMBER; i++) {
        tick();
        alpha_gyx += GyX;
        alpha_gyy += GyY;
        alpha_gyz += GyZ;
        wdt_reset(); // to prevent him to start
        delay(1);
    }

    alpha_gyx /= CALIBRATION_TICK_NUMBER;
    alpha_gyy /= CALIBRATION_TICK_NUMBER;
    alpha_gyz /= CALIBRATION_TICK_NUMBER;

    writeEepromDouble(GYRO_X_OFFSET_LOCATION,alpha_gyx);
    writeEepromDouble(GYRO_Y_OFFSET_LOCATION,alpha_gyy);
    writeEepromDouble(GYRO_Z_OFFSET_LOCATION,alpha_gyz);

    loadGyroOffsets();

}

#ifdef ENABLE_DEBUG
    void ImuSensor::printAttitude() {
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.print(z);
        Serial.println();
    }
#endif
