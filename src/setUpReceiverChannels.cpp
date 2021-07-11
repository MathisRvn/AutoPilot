#include "config.h"

#include "./Objects/Board/Receiver.h"

#include "setUpReceiverChannels.h"

ReceiverPwmChannel aileronReceiver(AILERON_INPUT, aileronInterrupt);
void aileronInterrupt() {
	aileronReceiver.interruptCallback();
}

ReceiverPwmChannel elevatorReceiver(ELEVATOR_INPUT, elevatorInterrupt);
void elevatorInterrupt() {
	elevatorReceiver.interruptCallback();
}

ReceiverPwmChannel throttleReceiver(THROTTLE_INPUT, throttleInterrupt);
void throttleInterrupt() {
	throttleReceiver.interruptCallback();
}

ReceiverPwmChannel rudderReceiver(RUDDER_INPUT, rudderInterrupt);
void rudderInterrupt() {
    rudderReceiver.interruptCallback();
}

ReceiverPwmChannel switch1Receiver(SWITCH1_INPUT, switch1Interrupt);
void switch1Interrupt() {
	switch1Receiver.interruptCallback();
}

ReceiverPwmChannel switch2Receiver(SWITCH2_INPUT, switch2Interrupt);
void switch2Interrupt() {
	switch2Receiver.interruptCallback();
}