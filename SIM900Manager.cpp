#include "SIM900Manager.h"
#include <HardwareSerial.h>
#include "Config.h"

HardwareSerial sim900(1); 

void powerOnSIM900() {
    Serial.println("Tentativo di accensione del SIM900...");
    pinMode(SIM900_PWRKEY, OUTPUT);

    // Accendi il modulo tenendo basso PWRKEY per 1 secondo
    digitalWrite(SIM900_PWRKEY, LOW);
    delay(1000);
    digitalWrite(SIM900_PWRKEY, HIGH);

    delay(5000);  // Attendi che il modulo si accenda

    // Verifica che il modulo risponda al comando AT con "OK"
    sim900.println("AT");
    if (checkSIM900Response(String("OK"), RESPONSE_TIMEOUT)) {
        Serial.println("SIM900 acceso correttamente!");
    } else {
        Serial.println("Errore: Il SIM900 non risponde al comando AT iniziale.");
    }
}

// Funzione per controllare la risposta del SIM900
bool checkSIM900Response(const String& expectedResponse, unsigned long timeout) {
    String response = "";
    unsigned long startTime = millis();

    Serial.println("In attesa della risposta dal SIM900...");
    
    while (millis() - startTime < timeout) {
        while (sim900.available()) {
            char c = sim900.read();

            // Filtra i caratteri strani (valori non ASCII)
            if (c >= 32 && c <= 126) {
                response += c;  // Aggiunge solo caratteri leggibili
            }
        }
    }
    
    if (response.length() > 0) {
        Serial.print("Risposta filtrata ricevuta dal SIM900: ");
        Serial.println(response);  // Mostra la risposta ricevuta (senza caratteri strani)
    } else {
        Serial.println("Nessuna risposta ricevuta.");
    }

    // Controlla se la risposta contiene ciò che ci aspettiamo
    if (response.indexOf(expectedResponse) != -1) {
        return true;
    }

    return false;
}

void setupGPRS() {
    Serial.println(F("📡 Configurazione GPRS..."));

    delay(10000); // Attendi che si registri sulla rete
    
    sim900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    if (checkSIM900Response("OK", RESPONSE_TIMEOUT)) {
        Serial.println("Contype configurato correttamente.");
    } else {
        Serial.println("Errore nella configurazione del Contype.");
        return;
    }

    sim900.println("AT+SAPBR=3,1,\"APN\",\"iot.1nce.net\"");
    if (checkSIM900Response("OK", RESPONSE_TIMEOUT)) {
        Serial.println("APN configurato correttamente.");
    } else {
        Serial.println("Errore nella configurazione dell'APN.");
        return;
    }

    sim900.println("AT+SAPBR=1,1");
    if (checkSIM900Response("OK", RESPONSE_TIMEOUT)) {
        Serial.println("Connessione GPRS attivata correttamente.");
    } else {
        Serial.println("Errore durante l'attivazione della connessione GPRS.");
    }
}

bool isGPRSConnected() {
    Serial.println(F("📡 Verifica dello stato GPRS..."));
    sim900.println("AT+SAPBR=2,1");
    delay(1000);

    String response = "";
    while (sim900.available()) {
        response += (char)sim900.read();
    }

    Serial.println("📋 Risposta GPRS: " + response);

    return !(response.indexOf("0.0.0.0") != -1 || response.indexOf("ERROR") != -1);
}
