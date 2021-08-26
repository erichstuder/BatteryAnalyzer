#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

void currentController_init(float samplingTime);
void currentController_setCurrent(float value);
void currentController_tick(void);
void currentController_setIGain(float value);
float currentController_getValue(void);

#endif