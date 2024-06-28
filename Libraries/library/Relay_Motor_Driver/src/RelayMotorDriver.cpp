// Relay Motor driver Library
// Allows to use Relays instead of L9110 Motors with DIYBar / MyBar
// By - René Gern. Pubplic domain. Enjoy.

#include "RelayMotorDriver.h"
#include "Arduino.h"

Relay_Motor::Relay_Motor() {}

bool Relay_Motor::initialize(uint8_t pin) {
 	motor_pin = pin;
	pinMode(motor_pin, OUTPUT);
	return true;
}

bool Relay_Motor::run(uint8_t cmds) {
	if (((FORWARD | BACKWARD) & cmds) == (FORWARD | BACKWARD)) {
		return false;
	}
	if (((BRAKE | RELEASE) & cmds) == (BRAKE | RELEASE)) {
		return false;
	}
	if ((cmds & FORWARD) == FORWARD) {
        digitalWrite(motor_pin, HIGH);
		runstate = (runstate & (BRAKE | RELEASE)) | FORWARD;
	}
	if ((cmds & BACKWARD) == BACKWARD) {
        //NOT AVAILABLE
		runstate = (runstate & (BRAKE | RELEASE)) | BACKWARD;
	}
	if ((cmds & RELEASE) == RELEASE) {
  	   if ((runstate & FORWARD) == FORWARD) {
		    digitalWrite(motor_pin, HIGH);
  	   }

       if ((runstate & BACKWARD) == BACKWARD) {
		    //NOT AVAILABLE
        }

        runstate = (runstate & (FORWARD | BACKWARD)) | RELEASE;
	}

	if ((cmds & BRAKE) == BRAKE) {
         digitalWrite(motor_pin, LOW);
         runstate = (runstate & (FORWARD | BACKWARD)) | BRAKE;
	}

	return true;
}

uint8_t Relay_Motor::getState(void) {
	return runstate & (BRAKE | RELEASE);
}

uint8_t Relay_Motor::getDirection(void) {
	return runstate & (FORWARD | BACKWARD);
}
