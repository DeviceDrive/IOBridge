#ifndef MotionDetector_h
#define MotionDetector_h

#include <Arduino.h>
#include <inttypes.h>
#include "pindef.h"

#define MOVEMENT_LEVEL_LOW 350
#define MOVEMENT_LEVEL_HIGH 600

typedef void MotionDetectedCallback();

class MotionDetector
{
  public:
    MotionDetector();
    MotionDetector(int pin);
    void enableMotionDetector();
    void disableMotionDetector();
    void onMotionDetected(MotionDetectedCallback * motion_detected_cb);
    void onNoMotion(MotionDetectedCallback * no_motion_detected_cb);
    void motionHandler();
	void setMovementLevels(float low, float high);
	float getCurrentMovement();

  private:
	  int num_readings = 10;
	  int readIndex = 0;
	  float total = 0;
	  float average = 0;
	  float readings[10];


	  float movement_level_low = 400;
	  float movement_level_high = 510;
	  bool is_movement = false;
    bool should_read_motion;
    float move_level;
    int read_motion_pin;
    bool movement_detected;
    float movement_timer;
    float current_time;
    MotionDetectedCallback *motion_detected_cb = NULL;
    MotionDetectedCallback *no_motion_detected_cb = NULL;
	void setup_pins_and_smoothing();
};

#endif
