#include "SensorManager.h"
#include "Config.h"
#include <Wire.h>
#include <DHT.h>
#include <AS5600.h>
#include <MQ135.h>
#include <Adafruit_BMP280.h>
#include <Preferences.h>
#include <pgmspace.h>

DHT dht(DHTPIN, DHTTYPE);
AS5600 as5600;
MQ135 mq135_sensor(A2);
Adafruit_BMP280 bmp;
Preferences preferences;

float previousPressure = 0.0;
float pressureTwoHoursAgo = 0.0;

// Variabili globali per il sensore Hall
volatile byte pulseCount = 0;
unsigned long lastPulseTime = 0;
unsigned long lastTime = 0;

// Direzioni del vento in memoria PROGMEM
const char wind_directions[][4] PROGMEM = {
    "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
    "S", "SSO", "SO", "OSO", "O", "ONO", "NO", "NNO"
};

// Funzione di Interrupt per contare gli impulsi
void countPulse() {
    unsigned long now = millis();
    if (now - lastPulseTime > MIN_PULSE_INTERVAL) {  // Filtraggio per evitare conteggi errati
        pulseCount++;
        lastPulseTime = now;
    }
}

// Inizializzazione dei sensori
void initializeSensors() {
    Wire.begin(6, 5);
    dht.begin();

    if (!bmp.begin(0x76)) Serial.println(F("⚠️ Errore: BMP280 non trovato!"));
    if (!as5600.begin(0x36)) Serial.println(F("⚠️ Errore: AS5600 non trovato!"));
    
    pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING);

    preferences.begin("weather", false);
}

// Funzione per determinare la direzione del vento
const char* getWindDirection(float angle) {
    static char buffer[4] = "N/A";  // Buffer per la direzione del vento

    int index = (int)((angle + 11.25) / 22.5) % 16;
    strcpy_P(buffer, wind_directions[index]);  // Copia dalla memoria PROGMEM al buffer

    return buffer;
}

// Funzione per la lettura dei sensori
WeatherData readSensors() {
    WeatherData data;
    data.hasErrors = false;

    data.angle = as5600.readAngle() * 360.0 / 4096.0;
    data.windDirection = getWindDirection(data.angle);
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    data.pressure = bmp.readPressure() / 100.0F;
    data.PPM = mq135_sensor.getCorrectedPPM(data.temperature, data.humidity);
    data.forecast = getWeatherPrediction(data.pressure);
    unsigned long currentTime = millis();
    float timeSec = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    float rotationsPerSec = 0.0;
    if (pulseCount > 0) {
        rotationsPerSec = pulseCount / timeSec;  // Calcolo della frequenza di rotazione (giri al secondo)
    } else {
        Serial.println(F("❌ Nessun impulso dal sensore Hall. Velocità del vento = 0 km/h."));
    }
    
    // Calcolo della velocità del vento
    float circumference = 2 * PI * RADIUS_M;    // Circonferenza del sensore (in metri)
    data.windSpeed = rotationsPerSec * circumference * 3.6;  // Conversione da m/s a km/h
    pulseCount = 0;  // Resetta il conteggio degli impulsi per la prossima lettura

    if (isnan(data.temperature) || isnan(data.humidity) || data.pressure == 0.0) {
        data.hasErrors = true;
    }
    return data;
}

// Funzione per ripristinare i dati della pressione salvata
void restoreSavedPressure() {
    previousPressure = preferences.getFloat("pressure", 0.0);
    pressureTwoHoursAgo = preferences.getFloat("pressure2h", 0.0);
}

// Funzione per salvare i dati della pressione attuale
void savePressure(float pressure) {
    preferences.putFloat("pressure", pressure);

    if (millis() >= 2 * 3600 * 1000UL) {
        preferences.putFloat("pressure2h", pressure);
    }
}

// Funzione per calcolare la previsione meteo
String getWeatherPrediction(float currentPressure) {
    if (previousPressure == 0.0) {
        return "Pressione non disponibile per confronto.";
    }

    float diff = currentPressure - previousPressure;
    String prediction = "⛅ Pressione stabile: Nessun cambiamento significativo";

    if (diff > 1.0) prediction = "🌞 Alta pressione: Tempo sereno";
    if (diff < -1.0) prediction = "🌧 Bassa pressione: Possibili piogge o temporali";

    if (pressureTwoHoursAgo != 0.0) {
        float diffTwoHours = currentPressure - pressureTwoHoursAgo;

        if (diffTwoHours >= 2.0) {
            prediction = "🌞 Graduale miglioramento: La pressione è aumentata di 2 hPa in 2 ore.";
        }
        if (diffTwoHours <= -2.0) {
            prediction = "🌧 Peggioramento graduale: La pressione è diminuita di 2 hPa in 2 ore.";
        }
    }
    return prediction;
}
