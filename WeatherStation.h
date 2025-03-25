#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <Arduino.h>

// DHT Sensor Definitions
#define DHTPIN 2
#define DHTTYPE DHT22

// Struttura per raccogliere tutti i dati meteo
struct WeatherData {
    float angle;
    const char* windDirection;
    float windSpeed;
    float temperature;
    float humidity;
    float PPM;
    float pressure;
    String forecast;
    bool hasErrors;
};

#endif
