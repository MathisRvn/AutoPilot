#include<Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>

#include "../config.h"
#include "./EEPROM_.h"

#include "./Attitude.h"

void ImuSensor::init() {

    Wire.beginTransmission(MPU_ADDR); 
    Wire.write(0x6B); 
    Wire.write(0); 
    Wire.endTransmission(true);

    pitch = 90;
    roll = 90;

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
  	double accRoll = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  	double accPitch = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

    accRoll += 90; // To center the value around 90°
    if (accRoll >= 360) { accRoll -= 360; }

    accPitch += 90;
    if (accPitch >= 360) { accPitch -= 360; }

    double delta_time = (double)(micros() - last_time_capture) / 1000000;
    last_time_capture = micros();

    // Implementing a complementary filter
    pitch = 0.98 * ( pitch + GyY * delta_time ) + 0.02 * accPitch;
    roll = 0.98 * ( roll + GyX * delta_time ) + 0.02 * accRoll;

}

void ImuSensor::loadGyroOffsets () {
    gyroXOffset = readEepromDouble(GYRO_X_OFFSET_LOCATION);
    gyroYOffset = readEepromDouble(GYRO_Y_OFFSET_LOCATION);
    gyroZOffset = readEepromDouble(GYRO_Z_OFFSET_LOCATION);
}

void ImuSensor::calibrateGyroOffsets () {

    Serial.println(CALIBRATION_BEGINNING_CODE);

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

    Serial.println(CALIBRATION_SUCCESS_CODE);

}

void ImuSensor::printAttitude() {
    Serial.print(pitch);
    Serial.print(",");
    Serial.print(roll);
    Serial.println();
}
