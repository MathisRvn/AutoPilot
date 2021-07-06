#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>

#include "./config.h"

#include "./Objects/Attitude.h"
#include "./Objects/Airplane.h"
#include "./Objects/Led.h"
#include "./Objects/Receiver.h"
#include "./Objects/PID.h"
#include "./Objects/Controller.h"

#include "./setUpReceiverChannels.h"

ImuSensor imuSensor;
Airplane airplane;
Led boardLed(BOARD_LED_PIN, LED_SLOW_BLINK);

PID aileron_PID(2, 0.5, 90, 90);
Controller aileronController(&(airplane.aileronServo), &aileronReceiver, INPUT_COPY, &aileron_PID);

PID elevator_PID(2, 0.5, 90, 90);
Controller elevatorController(&(airplane.elevatorServo), &elevatorReceiver, INPUT_COPY, &elevator_PID);

Controller throttleController(&(airplane.throttleServo), &throttleReceiver, INPUT_COPY);

Controller rudderController(&(airplane.rudderServo), &rudderReceiver, INPUT_COPY);

ReceiverSwitch switch1(&switch1Receiver);
ReceiverSwitch switch2(&switch2Receiver);

void setup() {

	Serial.begin(9600);
	Wire.begin();

	imuSensor.init();

  	initAirplane(&airplane);

	wdt_enable(WDTO_TIME);
	
}

void loop() {

  	boardLed.tickLed();

  	imuSensor.tick();

	switch1.checkMode();
	switch2.checkMode();

	if (switch1.switchMode == SWITCH_DOWN){
		elevatorController.mode = PID_CONTROLLER;
	}else{
		elevatorController.mode = INPUT_COPY;
	}

	if (switch2.switchMode == SWITCH_DOWN){
		aileronController.mode = PID_CONTROLLER;
	}else{
		aileronController.mode = INPUT_COPY;
	}

	aileronController.tick(imuSensor.roll);
	elevatorController.tick(imuSensor.pitch);
	throttleController.tick();
	rudderController.tick();

/*
	if (Serial.available() == 0) {
		String input = Serial.readString();
		Serial.println(input);
		
		if (input == SERIAL_CALIBRATION_COMMAND) {
			imuSensor.calibrateGyroOffsets();
		}else if (input == SERIAL_GET_ATTITUDE_COMMAND) {
			imuSensor.printAttitude();
		}else{
			Serial.println(SERIAL_INVALID_INPUT_RESPONSE);
		}

	}
*/
	wdt_reset();

}