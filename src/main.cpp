#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>

#include "./config.h"

#include "./Objects/Airplane.h"
#include "./Objects/Led.h"
#include "./Objects/PID.h"
#include "./Objects/Mixer.h"

#include "./Objects/Receiver.h"
void receiverInterrupt(); // Because we use an object, wa have to create this intermediate function
Receiver receiver(RECEIVER_PIN, receiverInterrupt);
void receiverInterrupt() {
	receiver.interruptCallback();
}

#include "./Objects/Attitude.h"
ImuSensor imuSensor;

typedef enum ModeType { 
        COPY, STABILIZER, OFF
} ModeType;

ModeType ControlMode = OFF;

void setup() {

	Serial.begin(9600);
	#ifdef ENABLE_DEBUG
		Serial.println("DEBUG ENABLED");
		Serial.println("Starting board");
	#endif

	Wire.begin();

	imuSensor.init();

	wdt_enable(WDTO_TIME);
	
}

void loop() {

	static Airplane airplane(&receiver);
	static Mixer leftAileronMixer(&(airplane.leftAileronServo));
	static Mixer rightAileronMixer(&(airplane.rightAileronServo));

	imuSensor.tick();

	#ifdef DEBUG_PRINT_RECEIVER_INPUT
		airplane.receiver->print();
	#endif

	static int pitch_command = 1500;
	static int roll_command = 1500;

	// TODO : ajouter un mode enregistrement des données et un mode control de vol

	// TODO : ajouter synchro moteur permanente

	if (ControlMode == OFF) {
		pitch_command = 1500;
		roll_command = 1500;
	} else if (ControlMode == STABILIZER) {
		// TODO : A changer -> ajouter control PID
		pitch_command = 1500;
		roll_command = 1500;
	} else {
		pitch_command = airplane.receiver->ch[1];
		roll_command = airplane.receiver->ch[0];
	}
	

	leftAileronMixer.tick(roll_command, pitch_command);
	rightAileronMixer.tick(roll_command, pitch_command);

	airplane.board.infoLed.tickLed();

	// Detecting the mode
	if (receiver.ch[4] < 700) { ControlMode = OFF; }
	else if (receiver.ch[4] > 1800) { ControlMode = STABILIZER; }
	else { ControlMode = COPY; } // if between 700 and 1800; = top and middle position of SWC


	// Reading and responding to command
	/*
	For the protocol, check desktop app doc
	*/

	
	static char msg[3];
	static short i = 0;

	if (Serial.available()) {

		delay(10); // Waiting to receive all the data
		
		for (i = 0; i < 3; i++){
		msg[i] = Serial.read();
		}

		// Clearing the buffer
		while (Serial.available()) { Serial.read(); }
		
		if (memcmp(msg, "pin", 3) == 0) {
			Serial.println("pong");
		}else if(memcmp(msg, "att", 3) == 0) {
			imuSensor.printAttitude();
		}else if (memcmp(msg, "cmd", 3) == 0) {
			airplane.receiver->print();
		}
		
	
	}

	wdt_reset();

}