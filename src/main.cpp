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

	leftAileronMixer.tick(airplane.receiver->ch[0], airplane.receiver->ch[1]);
	rightAileronMixer.tick(airplane.receiver->ch[0], airplane.receiver->ch[1]);

	airplane.board.infoLed.tickLed();

	/*

	static PID aileron_PID(2, 0.5, 90, 90);
	static Controller aileronController(&(airplane.aileronServo), &aileronReceiver, INPUT_COPY, &aileron_PID);

	static PID elevator_PID(2, 0.5, 90, 90);
	static Controller elevatorController(&(airplane.elevatorServo), &elevatorReceiver, INPUT_COPY, &elevator_PID);

	static Controller throttleController(&(airplane.throttleServo), &throttleReceiver, INPUT_COPY);

	static Controller rudderController(&(airplane.rudderServo), &rudderReceiver, INPUT_COPY);

	static ReceiverSwitch switch1(&switch1Receiver);
	static ReceiverSwitch switch2(&switch2Receiver);

  	airplane.board.imuSensor.tick();

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
*/
	/*
	aileronController.tick(board.imuSensor.x);
	elevatorController.tick(board.imuSensor.y);
	throttleController.tick();
	rudderController.tick();
	*/

	wdt_reset();

}