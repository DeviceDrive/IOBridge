// 
// 
// 

#include "iobridgelib.h"

void IOBridgeLib::init()
{
	led_controller = Led(DEFAULT_RED_PIN, DEFAULT_GREEN_PIN, DEFAULT_BLUE_PIN);
	led_controller.setup();
	led_controller.setColor(0, 0, 0, true);

	button_handler_sw200_controller = ButtonHandler(SW200_PIN);
	button_handler_sw201_controller = ButtonHandler(SW201_PIN);
	button_handler_sw200_controller.setup(INPUT);
	button_handler_sw201_controller.setup(INPUT);

	motion_detector_controller = MotionDetector(MOVEMENT_DETECTOR_READ_PIN);

	ntc_controller = NTCConverter(DEFAULT_TEMPERATURE_PIN);
	ntc_controller.setup();

	relay_controller = RelayControl(DEFAULT_RELAY1_REL200_PIN, DEFAULT_RELAY2_REL201_PIN);
	relay_controller.setup();

	opto_one_controller = OptoCoupler(DEFAULT_OPTO_1_PIN);
	opto_two_controller = OptoCoupler(DEFAULT_OPTO_2_PIN);

	remote_adc_controller = RemoteADC(DEFAULT_REMOTE_ADC_PIN);
	Initialized = true;
}

void IOBridgeLib::handle()
{
	led_controller.handle();
	button_handler_sw200_controller.handle();
	button_handler_sw201_controller.handle();
	motion_detector_controller.motionHandler();
	ntc_controller.temperatureHandler();
	opto_one_controller.handle();
	opto_two_controller.handle();
}

SpiUart& IOBridgeLib::get_uart()
{
	CheckInit();		
	if(Uart == nullptr)
		Uart = new SpiUart(7);
		
	return *Uart;
}
#pragma region Button callbacks
void IOBridgeLib::set_button_sw200_press_callback(ButtonPressedCallback cb)
{
	button_handler_sw200_controller.onPress(cb);
}

void IOBridgeLib::set_button_sw201_press_callback(ButtonPressedCallback cb)
{
	button_handler_sw201_controller.onPress(cb);
}

void IOBridgeLib::set_button_sw200_longpress_callback(ButtonPressedCallback cb)
{
	button_handler_sw200_controller.onLongPress(cb);
}

void IOBridgeLib::set_button_sw201_longpress_callback(ButtonPressedCallback cb)
{
	button_handler_sw201_controller.onLongPress(cb);
}
#pragma endregion

#pragma region Motion Detector Callbacks
void IOBridgeLib::set_motion_detector_on_motion_callback(MotionDetectedCallback * cb)
{
	motion_detector_controller.onMotionDetected(cb);
}

void IOBridgeLib::set_motion_detector_on_no_motion_callback(MotionDetectedCallback * cb)
{
	motion_detector_controller.onNoMotion(cb);
}

#pragma endregion

#pragma region Temperature callback
void IOBridgeLib::set_temperature_temperature_changed_callback(TemperatureChangedCallback * cb)
{
	ntc_controller.onTemperatureChanged(cb);
}
#pragma endregion

#pragma region OptoCoupler callback
void IOBridgeLib::set_opto_one_state_changed_callback(OptoCouplerCallback * cb)
{
	opto_one_controller.onStateChangedCallback(cb);
}
void IOBridgeLib::set_opto_two_state_changed_callback(OptoCouplerCallback * cb)
{
	opto_two_controller.onStateChangedCallback(cb);
}
#pragma endregion


#pragma region LED controller methods

void IOBridgeLib::led_setColor(int red, int green, int blue)
{
	led_controller.setColor(red, green, blue);
}
void IOBridgeLib::led_setColor(int red, int green, int blue, bool remember)
{
	led_controller.setColor(red, green, blue, remember);
}
void IOBridgeLib::led_setColor(Color color)
{
	led_controller.setColor(color);
}
void IOBridgeLib::led_setColor(Color color, bool remember)
{
	led_controller.setColor(color, remember);
}
void IOBridgeLib::led_fadeTo(Color color)
{
	led_controller.fadeTo(color);
}
bool IOBridgeLib::led_isFading()
{
	return led_controller.isFading();
}
void IOBridgeLib::led_stopFade()
{
	led_controller.stopFade();
}
void IOBridgeLib::led_startBlink(unsigned long interval)
{
	led_controller.startBlink(interval);
}
void IOBridgeLib::led_stopBlink()
{
	led_controller.stopBlink();
}
bool IOBridgeLib::led_isBlinking()
{
	return led_controller.isBlinking();
}
Color IOBridgeLib::led_getColor()
{
	return led_controller.getColor();
}
#pragma endregion

#pragma region Relays

void IOBridgeLib::relay_set_relay1_on()
{
	relay_controller.relayLeftOn();
}
void IOBridgeLib::relay_set_relay1_off()
{
	relay_controller.relayLeftOff();
}
void IOBridgeLib::relay_set_relay2_on()
{
	relay_controller.relayRightOn();
}
void IOBridgeLib::relay_set_relay2_off()
{
	relay_controller.relayRightOff();
}
void IOBridgeLib::relay_set_relay1_toggle()
{
	relay_controller.relayLeftToggle();
}
void IOBridgeLib::relay_set_relay2_toggle()
{
	relay_controller.relayRightToggle();
}
bool IOBridgeLib::relay_get_relay1()
{
	return relay_controller.relayLeftGetStatus();
}
bool IOBridgeLib::relay_get_relay2()
{
	return relay_controller.relayRightGetStatus();
}
#pragma endregion

#pragma region Motion detector
void IOBridgeLib::motion_set_movement_levels(float low, float high)
{
	motion_detector_controller.setMovementLevels(low, high);
}
void IOBridgeLib::motion_enable_movement_sensor()
{
	motion_detector_controller.enableMotionDetector();
}
void IOBridgeLib::motion_disable_movement_sensor()
{
	motion_detector_controller.disableMotionDetector();
}
float IOBridgeLib::motion_get_current_movement()
{
	return motion_detector_controller.getCurrentMovement();
}

#pragma endregion

#pragma region Temperature
void IOBridgeLib::temp_toggle_temperature_read()
{
	ntc_controller.toggleTemperatureRead();
}
double IOBridgeLib::temp_read_celsius()
{
	return ntc_controller.ReadCelsius();
}
double IOBridgeLib::temp_read_kelvin()
{
	return ntc_controller.ReadKelvin();
}
#pragma endregion

#pragma region OptoCouplers
int IOBridgeLib::opto_one_get_current_state()
{
	return opto_one_controller.getCurrentState();
}
int IOBridgeLib::opto_two_get_current_state()
{
	return opto_two_controller.getCurrentState();
}
#pragma endregion

#pragma region Remote ADC
float IOBridgeLib::adc_get_current_value()
{
	return remote_adc_controller.getCurrentValue();
}
 IOBridgeLib::~IOBridgeLib()
{
	if(Uart)
	{
		delete Uart;
		Uart = nullptr;
	}
}
#pragma endregion



IOBridgeLib Iobridgelib;

