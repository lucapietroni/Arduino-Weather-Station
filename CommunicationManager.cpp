#include "CommunicationManager.h"
#include "SIM900Manager.h"

void initializeSIM900() {
    sim900.begin(9600, SERIAL_8N1, 4, 1);
    delay(1000);
    powerOnSIM900();
    setupGPRS();
}

void sendTelegramMessageAsync(WeatherData data) {
    if (!isGPRSConnected()) {
        Serial.println(F("❌ Connessione GPRS non disponibile. Riprovo..."));
        setupGPRS();

        if (!isGPRSConnected()) {
            Serial.println(F("❌ Impossibile stabilire la connessione GPRS. Messaggio non inviato."));
            return;  // Esci se non riesce a connettersi
        }
    }
    
    Serial.println(F("✅ Connessione GPRS disponibile. Preparazione invio messaggio..."));
    
    String message = "📡 *Aggiornamento Meteo* 📡\n";
    message += "🌬 *Vento:* " + String((int)data.windSpeed) + " km/h (" + data.windDirection + " " + String((int)data.angle) + "°)\n";
    message += "🌡 *Temperatura:* " + String((int)data.temperature) + "°C\n";
    message += "💦 *Umidità:* " + String((int)data.humidity) + "%\n";
    message += "🗜 *Pressione:* " + String((int)data.pressure) + " hPa\n";
    message += "🌤 *Previsione:* " + data.forecast + "\n";
    message += "♻️ *Qualità dell'aria:* " + String((int)data.PPM) + " PPM\n";
    
    sendMessage(message);
}

void sendMessage(const String& message) {
    Serial.println(F("📤 Invio del messaggio Telegram..."));

    sim900.println("AT+HTTPINIT");
    delay(1000);
    
    sim900.println("AT+HTTPPARA=\"CID\",1");
    delay(500);

    sim900.println("AT+HTTPPARA=\"URL\",\"http://185.82.115.128:3003/sendMessage\"");
    delay(500);

    sim900.println("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"");
    delay(500);

    String postData = "message=" + message + "&parse_mode=Markdown";
    sim900.print("AT+HTTPDATA=");
    sim900.print(postData.length());
    sim900.println(",10000");
    delay(500);

    // Invia il messaggio
    sim900.print(postData);
    delay(1000);

    // Richiesta HTTP
    sim900.println("AT+HTTPACTION=1");
    delay(15000);  // Attende 15 secondi per ricevere la risposta

    Serial.println(F("📋 Lettura della risposta HTTP..."));
    sim900.println("AT+HTTPREAD");
    delay(2000);

    // Legge la risposta del server
    String response = "";
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {  // Legge fino a 5 secondi
        while (sim900.available()) {
            response += (char)sim900.read();
        }
    }

    if (response.length() > 0) {
        Serial.println("📋 Risposta dal server: " + response);
    } else {
        Serial.println(F("❌ Nessuna risposta ricevuta dal server."));
    }

    sim900.println("AT+HTTPTERM");
    delay(1000);
}
