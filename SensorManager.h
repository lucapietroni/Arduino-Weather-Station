#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "WeatherStation.h"

void initializeSensors();
WeatherData readSensors();
void restoreSavedPressure();
void savePressure(float pressure);
String getWeatherPrediction(float currentPressure);
const char* getWindDirection(float angle);

#endif
