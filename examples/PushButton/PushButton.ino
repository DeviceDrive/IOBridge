// the setup function runs once when you press reset or power the board
#include "iobridgelib.h"

IOBridgeLib bridge;

void setup() {
	Serial.begin(115200);
	bridge.init();
	bridge.set_button_sw200_press_callback(button_callback);
	Serial.println("Done Setup");
}

// the loop function runs over and over again until power down or reset
void loop() {
	bridge.handle();
	delay(1);
}

void button_callback() {
	Serial.println("Button was pushed");
}
