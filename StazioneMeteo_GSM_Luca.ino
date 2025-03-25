#include "WeatherStation.h"
#include "SensorManager.h"
#include "DisplayManager.h"
#include "CommunicationManager.h"
#include "PowerManager.h"
#include "DebugManager.h"
#include "TestManager.h"
#include "Config.h"

void setup() {
    Serial.begin(115200);
    delay(5000);
    Serial.println(F("\n\n\n🚀 Avvio Arduino Nano ESP32..."));

    initializeSensors();
    initializeDisplay();
    initializeSIM900();
    restoreSavedPressure();
    runAllTests();  

    Serial.println(F("✅ Setup completato!"));
}

void loop() {
    WeatherData data = readSensors();
    if (data.hasErrors) {
        Serial.println(F("❌ Errore nella lettura dei sensori. Messaggio non inviato."));
    } else {
        printWeatherData(data);  // Mostra i dati raccolti

        updateDisplay(data);
        savePressure(data.pressure);

        Serial.println(F("📲 Invio messaggio a Telegram..."));
        sendTelegramMessageAsync(data);  // Invia i dati al bot Telegram

        Serial.println(F("📤 Messaggio inviato!"));
    }

    prepareForDeepSleep();
}
