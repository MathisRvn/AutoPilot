#include<Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#include "./Attitude.h"

ImuSensor::ImuSensor() {}

void ImuSensor::init () {

    mpu.initialize();
    // TODO : Enlever ce print ! (à part en debug mode)
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

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

    } else {
		// TODO : gérer mieux l'erreur : empécher le programme de démarrer
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

}

void ImuSensor::tick () {

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    }

    // TODO : tester que ca renvoie des valeurs corrects

}

#ifdef ENABLE_DEBUG
    void ImuSensor::printAttitude() {
        // TODO: A redevelopper
    }
#endif
