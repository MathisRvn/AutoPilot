#include <Arduino.h>
#include <avr/wdt.h>

#include "./config.h"

#include "./Objects/Attitude.h"
#include "./Objects/Airplane.h"
#include "./Objects/Led.h"
#include "./Objects/Receiver.h"
#include "./Objects/PID.h"
#include "./Objects/Controller.h"

#include "./setUpReceiverChannels.h"

Attitude attitude;
Airplane airplane;
Led boardLed(BOARD_LED_PIN, LED_FAST_BLINK);

PID aileron_PID(2, 0.5, 90, 90);
Controller aileronController(&(airplane.aileronServo), &aileronReceiver, INPUT_COPY, &aileron_PID);

PID elevator_PID(2, 0.5, 90, 90);
Controller elevatorController(&(airplane.elevatorServo), &elevatorReceiver, INPUT_COPY, &elevator_PID);

Controller throttleController(&(airplane.throttleServo), &throttleReceiver, INPUT_COPY);

Controller rudderController(&(airplane.rudderServo), &rudderReceiver, INPUT_COPY);

ReceiverSwitch switch1(&switch1Receiver);
ReceiverSwitch switch2(&switch2Receiver);

void setup() {

  	#ifdef ENABLE_DEBUG
		Serial.begin(9600);
  	#endif

  	initAttitude(&attitude);
  	initAirplane(&airplane);

	wdt_enable(WDTO_TIME);
}

void loop() {

  	boardLed.tickLed();

  	updateMeanAngle(&attitude);

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

	aileronController.tick(attitude.angle.roll);
	elevatorController.tick(attitude.angle.pitch);
	throttleController.tick();
	rudderController.tick();

  	#ifdef ENABLE_DEBUG

		#ifdef PRINT_INSTANT_ANGLE
	  		printAngle(&(attitude.instant_angle));
		#endif

		#ifdef PRINT_MEAN_ANGLE
	  		printAngle(&(attitude.angle));
		#endif

		Serial.println();

  	#endif

	wdt_reset();

}