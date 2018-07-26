#include "OptoCoupler.h"

OptoCoupler::OptoCoupler(int opto_pin)
{
	this->read_opto_pin = opto_pin;
	pinMode(opto_pin, INPUT);
	last_state = 0;
}

void OptoCoupler::handle()
{
	this->current_state = digitalRead(this->read_opto_pin);
	if (this->current_state != this->last_state) {
		if (onStateChangedCb != NULL) {
			onStateChangedCb(this->current_state);
		}
		this->last_state = current_state;
	}
}

void OptoCoupler::onStateChangedCallback(OptoCouplerCallback * cb)
{
	this->onStateChangedCb = cb;
}

int OptoCoupler::getCurrentState()
{
	this->current_state = digitalRead(this->read_opto_pin);
	return this->current_state;
}
