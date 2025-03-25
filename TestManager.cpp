#include "TestManager.h"
#include "SensorManager.h"
#include "CommunicationManager.h"
#include "DisplayManager.h"
#include "PowerManager.h"
#include "DebugManager.h"
#include "SIM900Manager.h"

void runAllTests() {
    Serial.println(F("\n🔍 Inizio Esecuzione Test...\n"));

    testSensorReading();
    testSIM900Connection();
    testDisplayUpdate();

    Serial.println(F("\n✅ Tutti i test completati.\n"));
}

// Test per la lettura dei sensori
void testSensorReading() {
    Serial.println(F("📡 Test Sensori..."));
    WeatherData data = readSensors();

    if (!data.hasErrors) {
        printWeatherData(data);  // Mostra i dati raccolti per il debug
        Serial.println(F("✅ Lettura sensori riuscita."));
    } else {
        Serial.println(F("❌ Errore nella lettura dei sensori."));
    }
}

// Test per il modulo SIM900
void testSIM900Connection() {
    Serial.println(F("📶 Test Connessione SIM900..."));
    
    if (isGPRSConnected()) {
        Serial.println(F("✅ GPRS connesso correttamente."));
    } else {
        Serial.println(F("❌ Errore nella connessione GPRS. Tentativo di riattivazione..."));
        setupGPRS();
        
        if (isGPRSConnected()) {
            Serial.println(F("✅ Riconnessione GPRS riuscita."));
        } else {
            Serial.println(F("❌ Connessione GPRS fallita."));
        }
    }
}

// Test per il Display E-Ink
void testDisplayUpdate() {
    Serial.println(F("🖥 Test Aggiornamento Display..."));

    WeatherData testData;
    testData.angle = 45.0;
    testData.windDirection = "NE";
    testData.windSpeed = 10.0;
    testData.temperature = 22.5;
    testData.humidity = 65.0;
    testData.PPM = 450.0;
    testData.pressure = 1013.0;
    testData.forecast = "🌞 Soleggiato";
    testData.hasErrors = false;

    updateDisplay(testData);
    Serial.println(F("✅ Display aggiornato correttamente."));
}

