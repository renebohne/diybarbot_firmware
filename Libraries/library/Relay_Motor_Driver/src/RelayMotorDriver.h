// Relay Motor driver Library
// Allows to use Relays instead of L9110 Motors with DIYBar / MyBar
// By - René Gern. Pubplic domain. Enjoy.

#ifndef _RelayMotorDriver_h_
#define _RelayMotorDriver_h_

#include <inttypes.h>

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8

class Relay_Motor {
public:
       Relay_Motor();
	   bool initialize(uint8_t pin);
	   bool run(uint8_t);
	   uint8_t getState(void);
	   uint8_t getDirection(void);

private:
	    uint8_t motor_pin, runstate, currentspeed;
};

#endif
