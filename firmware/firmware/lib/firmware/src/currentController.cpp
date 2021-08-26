#include <Arduino.h>

#include "currentMeasurement.h"

static float samplingTime = 0.0f;
// static float rampGain = 0.0f;
static float iGain = 0.0f;
static float iPart = 0.0f;
static float setCurrent = 0.0f;

void currentController_init(float sampling_time){
	samplingTime = sampling_time;
}

void currentController_setCurrent(float value){
	setCurrent = value;
}

void currentController_tick(void){
	currentMeasurement_tick();
	float current = currentMeasurement_getCurrent();
	float err = setCurrent - current;
	iPart += iGain * err * samplingTime;

	iPart = min(iPart, 255);
	iPart = max(iPart, 0);

	const uint8_t PwmPin = 11;
	analogWrite(PwmPin, iPart);
}

// void setCurrentController_rampGain(float value){
// 	rampGain = value;
// }

void currentController_setIGain(float value){
	iGain = value;
}

float currentController_getValue(void){
	return iPart;
}
