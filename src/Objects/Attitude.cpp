#include<Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#include "./Attitude.h"

ImuSensor::ImuSensor() {}

void ImuSensor::init () {

    mpu.initialize();
    if(!mpu.testConnection()) {

        initialization_success = false;
        Serial.println("Err:Fail to connect with the MPU6050");

    }else{

        devStatus = mpu.dmpInitialize();

        // supply your own gyro offsets here, scaled for min sensitivity
        mpu.setXGyroOffset(220);
        mpu.setYGyroOffset(76);
        mpu.setZGyroOffset(-85);
        mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

        if (devStatus == 0) {

            mpu.CalibrateAccel(6);
            mpu.CalibrateGyro(6);
            mpu.PrintActiveOffsets();
            // TODO : bouger la phase de calibration dans une autre fonction et enregistrer les valeurs dans la mémoires ?? (automatique directement sur le mpu ?)

            mpu.setDMPEnabled(true);
            mpuIntStatus = mpu.getIntStatus();
            dmpReady = true;
            packetSize = mpu.dmpGetFIFOPacketSize();
            initialization_success = true;

        } else {

            initialization_success = false;

            Serial.print(F("Err:DMP Initialization failed (code "));
            Serial.print(devStatus);
            Serial.println(F(")"));

        }
    }

    

}

void ImuSensor::tick () {

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer) && initialization_success == true) {

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    }

}

void ImuSensor::printAttitude() {
    Serial.print("Att:");
    Serial.print(ypr[0] * 180 / PI);
    Serial.print(',');
    Serial.print(ypr[1] * 180 / PI);
    Serial.print(',');
    Serial.print(ypr[2] * 180 / PI);
    Serial.println();
}
