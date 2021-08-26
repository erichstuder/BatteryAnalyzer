#include <Arduino.h>

#include "itHandler.h"
#include "cellCurrent.h"

static inline unsigned long getMicros(void);

static ItSignal_t itSignals[] = {
	{
		"current",
		ItValueType_Float,
		(void (*)(void)) getCellCurrent,
		NULL
	},
};

static const unsigned char ItSignalCount = sizeof(itSignals) / sizeof(itSignals[0]);

static unsigned long currentMicros;
static unsigned long lastAppTickMicros;
static unsigned long lastItTickMicros;
static const unsigned long AppSamplingTimeMicros = 0.01e6;
static const unsigned long ItSamplingTimeMicros = 1e6;

static const uint8_t PwmPin = 10;

void setup(void){
	itHandlerInit(getMicros, itSignals, ItSignalCount);
	currentMicros = micros();
	lastAppTickMicros = currentMicros;
	lastItTickMicros = currentMicros;
	pinMode(PwmPin, OUTPUT);
}

void loop(void){
	currentMicros = micros();
	if(currentMicros - lastAppTickMicros >= AppSamplingTimeMicros){
		lastAppTickMicros = currentMicros;
		cellCurrentTick();
		analogWrite(PwmPin, 204);
	}
	if(currentMicros - lastItTickMicros >= ItSamplingTimeMicros ){
		lastItTickMicros = currentMicros;
		itHandlerTick();
	}
}

static unsigned long getMicros(void){
	return currentMicros;
}
