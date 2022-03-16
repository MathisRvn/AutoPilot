#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <Servo.h>

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

	pinMode(MOTOR1_PIN, OUTPUT);
	pinMode(MOTOR2_PIN, OUTPUT);

	wdt_enable(WDTO_TIME);
	
}

void loop() {

	static Airplane airplane(&receiver);
	static Mixer leftAileronMixer(&(airplane.leftAileronServo));
	static Mixer rightAileronMixer(&(airplane.rightAileronServo));

	static PID PitchPIDController(1, 0.2, 1500, 1500);
	static PID RollPIDController(1, 0.2, 1500, 1500);

	imuSensor.tick();

	// Apply motors output

	static Servo motor1, motor2;
	motor1.attach(MOTOR1_PIN);
	motor2.attach(MOTOR2_PIN);

	// Continuous binding with radio output; Fail safe need to be configure on radio 

	motor1.writeMicroseconds(airplane.receiver->ch[MOTOR_RADIO_CHANNEL]);
	motor2.writeMicroseconds(airplane.receiver->ch[MOTOR_RADIO_CHANNEL]);

	static int pitch_command = 1500;
	static int roll_command = 1500;

	// TODO : ajouter un mode enregistrement des données et un mode control de vol

	static double pitch_map, roll_map;

	if (ControlMode == OFF) {
		pitch_command = 1500;
		roll_command = 1500;
	} else if (ControlMode == STABILIZER && imuSensor.initialization_success == true) {


		// To map from -pi < pitch < pi to 1000 < pitch_map < 2000
		pitch_map = 1500.0 + (double)(500.0 * imuSensor.ypr[1] / PI);
		roll_map = 1500.0 + (double)(500.0 * imuSensor.ypr[2] / PI);

		/* TODO : Verifier si c'est des valeurs cohérentes
		Serial.print(pitch_map);
		Serial.print(',');
		Serial.print(roll_map);
		Serial.println();
		*/

		pitch_command = (int)PitchPIDController.output(airplane.receiver->ch[1], pitch_map);
		roll_command = (int)RollPIDController.output(airplane.receiver->ch[0], roll_map);

		// TODO : Verifier si c'est des valeurs cohérentes

	} else {
		pitch_command = airplane.receiver->ch[1];
		roll_command = airplane.receiver->ch[0];
	}
	

	leftAileronMixer.tick(roll_command, pitch_command);
	rightAileronMixer.tick(roll_command, pitch_command);

	airplane.infoLed.tickLed();

	// Detecting the mode
	if (receiver.ch[4] < 700) { ControlMode = OFF; }
	else if (receiver.ch[4] > 1800  && imuSensor.initialization_success == true) { 
		if (ControlMode != STABILIZER) { // Resetting PID controllers
			PitchPIDController.output(1500, 1500);
			RollPIDController.output(1500, 1500);
		}
		ControlMode = STABILIZER; 
	}
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
		
		if (memcmp(msg, "awk", 3) == 0) {

			Serial.println("awk");

		}else if(memcmp(msg, "att", 3) == 0) {

			imuSensor.printAttitude();

		}else if (memcmp(msg, "cmd", 3) == 0) {

			airplane.receiver->print();

		}else if (memcmp(msg, "out", 3) == 0) {

			Serial.print("Out:");
			Serial.print(leftAileronMixer.output);
			Serial.print(',');
			Serial.print(rightAileronMixer.output);
			Serial.println();

		}else if (memcmp(msg, "axi", 3) == 0){

			Serial.print("Axis:");
			Serial.print(pitch_command);
			Serial.print(',');
			Serial.print(roll_command);
			Serial.println();

		}else if (memcmp(msg, "cal", 3) == 0) {
			imuSensor.calibrate();
		}
		
	
	}

	wdt_reset();

}