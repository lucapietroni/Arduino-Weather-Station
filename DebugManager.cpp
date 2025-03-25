#include "DebugManager.h"
#include <Arduino.h>

void printWeatherData(const WeatherData& data) {
    Serial.println(F("\n🌡 Dati Meteo Raccolti:"));
    Serial.print(F("Angolo: ")); Serial.print(data.angle); Serial.println(F("°"));
    Serial.print(F("Direzione del vento: ")); Serial.println(data.windDirection);
    Serial.print(F("Velocità del vento: ")); Serial.print(data.windSpeed); Serial.println(F(" km/h"));
    Serial.print(F("Temperatura: ")); Serial.print(data.temperature); Serial.println(F("°C"));
    Serial.print(F("Umidità: ")); Serial.print(data.humidity); Serial.println(F("%"));
    Serial.print(F("PPM: ")); Serial.print(data.PPM); Serial.println(F(" PPM"));
    Serial.print(F("Pressione: ")); Serial.print(data.pressure); Serial.println(F(" hPa"));
    Serial.print(F("Previsione: ")); Serial.println(data.forecast);
}

void logMessage(const String& message) {
    Serial.print(F("[LOG] "));
    Serial.println(message);
}
