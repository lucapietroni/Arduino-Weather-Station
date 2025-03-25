# 🌦 Stazione Meteo con Arduino Nano ESP32 e SIM900
Questo progetto raccoglie dati meteorologici e li invia su Telegram usando un modulo SIM900. Utilizza un display E-Ink per mostrare i dati localmente.

## 🔧 Hardware Utilizzato
- **Arduino Nano ESP32**
- **Modulo SIM900**
- **Sensore DHT22 (Temperatura e Umidità)**
- **Sensore BMP280 (Pressione)**
- **Sensore MQ135 (Qualità dell'aria)**
- **Sensore AS5600 (Direzione del vento)**
- **Display E-Ink GxEPD**

---

## 📝 Funzionalità Principali
- Misurazione della velocità e direzione del vento.
- Rilevamento di temperatura, umidità, pressione e qualità dell'aria.
- Invio automatico dei dati a Telegram tramite GPRS.
- Salvataggio della pressione per calcolare la previsione meteo.
- Visualizzazione dei dati su Display E-Ink.
- Modalità **Deep Sleep** per risparmiare energia.

---

## 📖 Struttura del Codice
- **`WeatherStation.h`**: Dichiarazioni principali.
- **`SensorManager.*`**: Gestione dei sensori.
- **`DisplayManager.*`**: Gestione del Display E-Ink.
- **`SIM900Manager.*`**: Comunicazione con il modulo SIM900.
- **`PowerManager.*`**: Gestione del Deep Sleep.
- **`TestManager.*`**: Esecuzione dei test.
- **`DebugManager.*`**: Funzioni di log e debug.

---

## 🚀 Avvio del Progetto
1. Carica il progetto su Arduino Nano ESP32.
2. Collega il modulo SIM900 e altri sensori.
3. Apri il `Serial Monitor` per verificare i test e i log.

---

## 🔍 Test e Debug
- I test vengono eseguiti automaticamente all'avvio.
- Controlla il `Serial Monitor` per i risultati dei test e i messaggi di debug.

---

## 📌 Migliorie Future
- Gestione degli errori avanzata.
- Integrazione con più servizi di notifica.
- Frikki hai rottercazzo.

---

## 🔌 Collegamenti Hardware (Pinout)

| Componente       | Descrizione                            | Pin Arduino (ESP32) | Pin Sensore/Modulo        |
|------------------|---------------------------------------|---------------------|---------------------------|
| **SIM900**       | Modulo GSM/GPRS per invio messaggi     | RX1 (GPIO4)         | TX del SIM900             |
|                  |                                        | TX1 (GPIO1)         | RX del SIM900             |
|                  | Controllo PWRKEY                      | GPIO12              | PWRKEY del SIM900         |
|                  | Alimentazione                         | 5V / GND            | VCC / GND del SIM900      |
|                  | Baud Rate                              | 9600 Baud           |                           |
|------------------|---------------------------------------|---------------------|---------------------------|
| **AS5600**       | Sensore di direzione del vento         | GPIO6 (SDA)         | SDA                       |
|                  |                                        | GPIO5 (SCL)         | SCL                       |
|                  | Alimentazione                         | 3.3V / GND          | VCC / GND                 |
|                  | Indirizzo I2C                         | 0x36                |                           |
|------------------|---------------------------------------|---------------------|---------------------------|
| **BMP280**       | Sensore di pressione atmosferica       | GPIO6 (SDA)         | SDA                       |
|                  |                                        | GPIO5 (SCL)         | SCL                       |
|                  | Alimentazione                         | 3.3V / GND          | VCC / GND                 |
|                  | Indirizzo I2C                         | 0x76                |                           |
|------------------|---------------------------------------|---------------------|---------------------------|
| **DHT22**        | Sensore di temperatura e umidità       | GPIO2               | Data Pin                  |
|                  | Alimentazione                         | 3.3V / GND          | VCC / GND                 |
|------------------|---------------------------------------|---------------------|---------------------------|
| **MQ135**        | Sensore di qualità dell'aria           | A2 (Analogico)      | AOUT                      |
|                  | Alimentazione                         | 5V / GND            | VCC / GND                 |
|------------------|---------------------------------------|---------------------|---------------------------|
| **Hall Sensor**  | Sensore per misurare la velocità vento | GPIO3 (INT)         | Data Pin (Pulldown)       |
|                  | Alimentazione                         | 3.3V / GND          | VCC / GND                 |
|------------------|---------------------------------------|---------------------|---------------------------|
| **Display E-Ink**| Display E-Paper (GxEPD Library)        | GPIO10 (CS)         | CS                        |
|                  |                                        | GPIO9 (DC)          | DC                        |
|                  |                                        | GPIO8 (RST)         | RST                       |
|                  |                                        | GPIO7 (BUSY)        | BUSY                      |
|                  | Alimentazione                         | 3.3V / GND          | VCC / GND                 |
|                  | SPI Pins (Standard)                   | SCK, MOSI, MISO     | SCK, MOSI, MISO           |

---

## 📋 Configurazione Software (Estratto delle definizioni)

File: `Config.h`
```cpp
#define HALL_SENSOR_PIN 3            // Pin del sensore Hall (velocità vento)
#define DHTPIN 2                     // Pin del sensore DHT22
#define DHTTYPE DHT22                // Tipo di sensore DHT
#define SIM900_PWRKEY 12             // Pin per accendere/spegnere il SIM900
#define RADIUS_MM 166                // Raggio del sensore di velocità del vento
#define RADIUS_M (RADIUS_MM / 1000.0)
#define MIN_PULSE_INTERVAL 50        // Intervallo minimo tra impulsi del sensore Hall
#define RESPONSE_TIMEOUT 5000        // Timeout per le risposte del SIM900
#define uS_TO_S_FACTOR 1000000       // Conversione da secondi a microsecondi
#define DEEP_SLEEP_DURATION 3480     // Durata del Deep Sleep in secondi (quasi 1 ora)

