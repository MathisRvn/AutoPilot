#include "config.h"

#include "./Objects/Receiver.h"

#include "setUpReceiverChannels.h"

#ifdef CH1_INPUT
  	ReceiverPwmChannel ch1(CH1_INPUT, ch1Interrupt);
  	void ch1Interrupt() {
		ch1.interruptCallback();
  	}
#endif

#ifdef CH2_INPUT
  	ReceiverPwmChannel ch2(CH2_INPUT, ch2Interrupt);
  	void ch2Interrupt() {
		ch2.interruptCallback();
  	}
#endif

#ifdef CH3_INPUT
  	ReceiverPwmChannel ch3(CH3_INPUT, ch3Interrupt);
  	void ch3Interrupt() {
		ch3.interruptCallback();
  	}
#endif

#ifdef CH4_INPUT
  	ReceiverPwmChannel ch4(CH4_INPUT, ch4Interrupt);
  	void ch4Interrupt() {
		ch4.interruptCallback();
  	}
#endif

#ifdef CH5_INPUT
  	ReceiverPwmChannel ch5(CH5_INPUT, ch5Interrupt);
  	void ch5Interrupt() {
		ch5.interruptCallback();
  	}
#endif

#ifdef CH6_INPUT
  	ReceiverPwmChannel ch6(CH6_INPUT, ch6Interrupt);
  	void ch6Interrupt() {
		ch6.interruptCallback();
  	}
#endif