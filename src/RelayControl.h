#ifndef RelayControl_h
#define RelayControl_h

#include <Arduino.h>
#include "pindef.h"

class IOBridgeLib;
class RelayControl
{
	friend IOBridgeLib;
 private:
    RelayControl();
    RelayControl(int relay1, int relay2);

    void setup();

    void relayLeftOn();
    void relayLeftOff();
    void relayLeftToggle();
	bool relayLeftGetStatus();

    void relayRightOn();
    void relayRightOff();
    void relayRightToggle();
	bool relayRightGetStatus();

  private:
    int relay_left_pin;
    int relay_right_pin;
    bool relay_left_power;
    bool relay_right_power;
};


#endif
