#ifndef OptoCoupler_h
#define OptoCoupler_h

#include <Arduino.h>
#include <inttypes.h>

typedef void OptoCouplerCallback(int value);

class OptoCoupler {
private:
	OptoCouplerCallback *onStateChangedCb = NULL;
	int read_opto_pin;
	int current_state;
	int last_state;

public:
	OptoCoupler();
	OptoCoupler(int opto_pin);
	void handle();

	void onStateChangedCallback(OptoCouplerCallback *cb);
	
	int getCurrentState();
};

#endif