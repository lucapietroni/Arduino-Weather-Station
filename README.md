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
