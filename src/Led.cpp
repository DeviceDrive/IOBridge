#include "Led.h"
#include <Arduino.h>

Led::Led() {

}

Led::Led(int pin_red, int pin_green, int pin_blue){
    _pin_red = pin_red;
    _pin_green = pin_green;
    _pin_blue = pin_blue;
}

void Led::setup(){
    pinMode(_pin_red, OUTPUT);
    pinMode(_pin_green, OUTPUT);
    pinMode(_pin_blue, OUTPUT);
}

void Led::handle(){
    unsigned long current_millis = millis();
    if(shouldBlink && current_millis - lastBlink >= blinkInterval){
        if(blinkVal){
            setColor(current_red, current_green, current_blue, true);
        }else{
            setColor(0,0,0, false);
        }
        lastBlink = current_millis;
        blinkVal = !blinkVal;
    }
    if(isCorssFading && current_millis - lastFade >= crossFadeWait){
        crossFade();
    }
}

void Led::setColor(int red, int green, int blue){
    analogWrite(_pin_red, red);
    analogWrite(_pin_green, green);
    analogWrite(_pin_blue, blue);
}

void Led::setColor(int red, int green, int blue, bool remember){
    if(remember){
      current_red = red;
      current_green = green;
      current_blue = blue;
    }
    setColor(red,green,blue);
}

void Led::setColor(Color color){
    setColor(color.red, color.green, color.blue, true);
}
void Led::setColor(Color color, bool remember){
    setColor(color.red, color.green, color.blue, remember);
}

void Led::fadeTo(Color color){
    current_step = 0;
    stepR = calculateStep(current_red, color.red);
    stepG = calculateStep(current_green, color.green);
    stepB = calculateStep(current_blue, color.blue);
    isCorssFading = true;
}
bool Led::isFading(){
    return isCorssFading;
}
void Led::stopFade(){
    isCorssFading = false;
}
void Led::startBlink(unsigned long intervall){
    shouldBlink = true;
    blinkInterval = intervall;
    blinkVal = false;
}
void Led::stopBlink(){
    shouldBlink = false;
}
bool Led::isBlinking(){
    return shouldBlink;
}

Color Led::getColor(){
    Color c;
    c.red = current_red;
    c.green = current_green;
    c.blue = current_blue;
}

int Led::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero,
    step = 1020/step;              //   divide by 1020
  }
  return step;
}

int Led::calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    }
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  }
  else if (val < 0) {
    val = 0;
  }
  return val;
}

void Led::crossFade() {
  if(current_step >= 1020){
      isCorssFading = false;
  }
  else{
    lastFade = millis();
    current_red = calculateVal(stepR, current_red, current_step);
    current_green = calculateVal(stepG, current_green, current_step);
    current_blue = calculateVal(stepB, current_blue, current_step);
    current_step++;

    setColor(current_red,current_green,current_blue);
  }
}

Color Colors::RED(){      return Color{255,0,0};}
Color Colors::ORANGE(){   return Color{255,128,0};}
Color Colors::YELLOW(){   return Color{255,255,0};}
Color Colors::GREEN(){    return Color{0,255,0};}
Color Colors::BLUE(){     return Color{0,0,255};}
Color Colors::CYAN(){     return Color{0,255,255};}
Color Colors::MAGENTA(){  return Color{255,0,255};}
