#include "RelayControl.h"

RelayControl::RelayControl() {
  RelayControl(DEFAULT_RELAY1_REL200_PIN, DEFAULT_RELAY2_REL201_PIN);
}

RelayControl::RelayControl(int relay1, int relay2) {
  this->relay_left_pin = relay1;
  this->relay_right_pin = relay2;
}

void RelayControl::setup() {
  this->relay_left_power = false;
  this->relay_right_power = false;
  pinMode(this->relay_left_pin, OUTPUT);
  pinMode(this->relay_right_pin, OUTPUT);
  digitalWrite(this->relay_left_pin, this->relay_left_power);
  digitalWrite(this->relay_right_pin, this->relay_right_power);
}

void RelayControl::relayLeftOn() {
  this->relay_left_power = true;
  digitalWrite(this->relay_left_pin, HIGH);
}

void RelayControl::relayLeftOff() {
  this->relay_left_power = false;
  digitalWrite(this->relay_left_pin, LOW);
}

void RelayControl::relayLeftToggle() {
  this->relay_left_power = !this->relay_left_power;
  digitalWrite(this->relay_left_pin, this->relay_left_power);
  Serial.println("Toggle");
}

bool RelayControl::relayLeftGetStatus() {
	return this->relay_left_power;
}

void RelayControl::relayRightOn() {
  this->relay_right_power = true;
  digitalWrite(this->relay_right_pin, HIGH);
}

void RelayControl::relayRightOff() {
  this->relay_right_power = false;
  digitalWrite(this->relay_right_pin, LOW);
}

void RelayControl::relayRightToggle() {
  this->relay_right_power = !this->relay_right_power;
  digitalWrite(this->relay_right_pin, this->relay_right_power);
}

bool RelayControl::relayRightGetStatus() {
	return this->relay_right_power;
}
