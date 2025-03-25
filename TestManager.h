#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include "WeatherStation.h"

void runAllTests();

// Dichiarazioni delle funzioni di test
void testSensorReading();
void testSIM900Connection();
void testDisplayUpdate();

#endif
