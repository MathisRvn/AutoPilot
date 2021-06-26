#include <Arduino.h>

#include "./config.h"

#include "./Objects/Attitude.h"
#include "./Objects/Airplane.h"
#include "./Objects/Led.h"
#include "./Objects/Receiver.h"
#include "./setUpReceiverChannels.h"

Attitude attitude;
Airplane airplane;
Led boardLed(BOARD_LED_PIN, SLOW_BLINK);

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

  	#ifdef ENABLE_DEBUG

		#ifdef PRINT_INSTANT_ANGLE
	  		printAngle(&(attitude.instant_angle));
		#endif

		#ifdef PRINT_MEAN_ANGLE
	  		printAngle(&(attitude.angle));
		#endif

		Serial.println();

  	#endif

  	delay(100);

}