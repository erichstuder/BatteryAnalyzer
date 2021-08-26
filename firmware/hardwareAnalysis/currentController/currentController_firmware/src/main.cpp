#include <Arduino.h>

#include "itHandler.h"
#include "currentController.h"
#include "currentMeasurement.h"

static inline unsigned long getMicros(void);

static ItSignal_t itSignals[] = {
	{
		"current",
		ItValueType_Float,
		(void (*)(void)) currentMeasurement_getCurrent,
		(void (*)(void)) currentController_setCurrent
	},
	{
		"pwm",
		ItValueType_Float,
		(void (*)(void)) currentController_getValue,
		NULL
	},
	{
		"Ki",
		ItValueType_Float,
		(void (*)(void)) currentController_getIGain,
		(void (*)(void)) currentController_setIGain,
	},
};

static const unsigned char ItSignalCount = sizeof(itSignals) / sizeof(itSignals[0]);

static unsigned long currentMicros;
static unsigned long lastMicros;
static const unsigned long SamplingTimeMicros = 0.01e6;

static const uint8_t PwmPin = 10;

void setup(void){
	float samplingTime = ((float)SamplingTimeMicros) / 10e6;
	currentController_init(samplingTime);
	itHandlerInit(getMicros, itSignals, ItSignalCount);
	lastMicros = micros();
	pinMode(PwmPin, OUTPUT);
}

void loop(void){
	currentMicros = micros();
	if(currentMicros - lastMicros < SamplingTimeMicros){
		return;
	}
	lastMicros = currentMicros;
	currentController_tick();
	itHandlerTick();
}

static unsigned long getMicros(void){
	return currentMicros;
}
