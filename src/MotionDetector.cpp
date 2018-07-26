#include "MotionDetector.h"
#include "pindef.h"

#define MOVEMENT_TIMER 5000

MotionDetector::MotionDetector() {
  this->read_motion_pin = MOVEMENT_DETECTOR_READ_PIN;
  setup_pins_and_smoothing();
}

MotionDetector::MotionDetector(int pin) {
  this->read_motion_pin = pin;
  setup_pins_and_smoothing();
}

void MotionDetector::setup_pins_and_smoothing()
{
	should_read_motion = false;
	pinMode(MOTION_DETECTOR_ENABLE_PIN, OUTPUT);
	digitalWrite(MOTION_DETECTOR_ENABLE_PIN, LOW);
	setMovementLevels(MOVEMENT_LEVEL_LOW, MOVEMENT_LEVEL_HIGH);

}

void MotionDetector::enableMotionDetector() {
  should_read_motion = true;
}

void MotionDetector::disableMotionDetector() {
  should_read_motion = false;
}

void MotionDetector::onMotionDetected(MotionDetectedCallback * motion_detected_cb) {
  this->motion_detected_cb = motion_detected_cb;
}

void MotionDetector::onNoMotion(MotionDetectedCallback * no_motion_detected_cb) {
  this->no_motion_detected_cb = no_motion_detected_cb;
}

void MotionDetector::motionHandler() {
	this->move_level = analogRead(this->read_motion_pin);
	//Smooting
	total = total - readings[readIndex];
	readings[readIndex] = move_level;
	total = total + readings[readIndex];
	readIndex = readIndex + 1;
	if (readIndex >= num_readings) {
		readIndex = 0;
	}
	// ///
	average = total / num_readings;
  if (should_read_motion) {
    this->current_time = millis();
    if (average < this->movement_level_low || average > this->movement_level_high && motion_detected_cb != NULL) {
		if (!this->is_movement) {
			this->motion_detected_cb();
			this->is_movement = true;
		}
		else
			this->is_movement = true;
    } else {
      if (current_time - movement_timer >= MOVEMENT_TIMER) {
		  if (this->is_movement && no_motion_detected_cb != NULL) {
			  no_motion_detected_cb();
		  }
		  this->is_movement = false;
        movement_timer = current_time;
      }
    }
  }
}

void MotionDetector::setMovementLevels(float low, float high)
{
	this->movement_level_low = low;
	this->movement_level_high = high;
}

float MotionDetector::getCurrentMovement() {
	return this->average;
}
