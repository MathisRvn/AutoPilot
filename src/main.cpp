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


typedef enum ModeType { 
        COPY, STABILIZER, OFF
} ModeType;

ModeType ControlMode = OFF;

void setup() {

	#ifdef ENABLE_DEBUG
		Serial.begin(9600);
		Serial.println("DEBUG ENABLED");
	#endif

	Wire.begin();

	wdt_enable(WDTO_TIME);
	
}

void loop() {

	static Airplane airplane(&receiver);
	static Mixer leftAileronMixer(&(airplane.leftAileronServo));
	static Mixer rightAileronMixer(&(airplane.rightAileronServo));

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

	// TODO : déplacer cette section dans une fonction receiver.tick; typedef ModeType aussi à déplacer
	// Detecting the mode
	if (receiver.ch[4] < 700) { ControlMode = OFF; }
	else if (receiver.ch[4] > 1800) { ControlMode = STABILIZER; }
	else { ControlMode = COPY; } // if between 700 and 1800; = top and middle position of SWC

	wdt_reset();

}