#include "PowerManager.h"
#include <esp_sleep.h>
#include "Config.h"
#include "SIM900Manager.h"

void prepareForDeepSleep() {
    Serial.println("Spegnimento del SIM900...");
    sim900.println("AT+CPOWD=1");
    delay(1000);
    Serial.println("SIM900 spento correttamente.");

    Serial.println("Entrando in deep sleep per un'ora...");
    delay(1000);  // Breve attesa per garantire che i messaggi seriali siano trasmessi completamente
    
    // Disabilitazione della periferica UART1 (SIM900)
    sim900.end();

    // Impostazione del timer per il deep sleep (1 ora = 3600 secondi)
    uint64_t sleepTime = DEEP_SLEEP_DURATION * (uint64_t) uS_TO_S_FACTOR;
    esp_sleep_enable_timer_wakeup(sleepTime);

    // Entrata in deep sleep
    esp_deep_sleep_start();
}
