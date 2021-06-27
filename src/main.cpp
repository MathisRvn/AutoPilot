#include <Arduino.h>

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
Led boardLed(BOARD_LED_PIN, SLOW_BLINK);

PID aileron_PID(2, 0.5, 90, 90);
Controller aileronController(&(airplane.aileronServo), &aileronReceiver, INPUT_COPY, &aileron_PID);

PID elevator_PID(2, 0.5, 90, 90);
Controller elevatorController(&(airplane.elevatorServo), &elevatorReceiver, INPUT_COPY, &elevator_PID);

Controller throttleController(&(airplane.throttleServo), &throttleReceiver, INPUT_COPY);

Controller rudderController(&(airplane.rudderServo), &rudderReceiver, INPUT_COPY);

void setup() {

  	#ifdef ENABLE_DEBUG
		Serial.begin(9600);
  	#endif

  	initAttitude(&attitude);
  	initAirplane(&airplane);
}

void loop() {

  	updateMeanAngle(&attitude);
	
  	boardLed.tickLed();

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

}