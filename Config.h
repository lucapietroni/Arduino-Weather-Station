#ifndef CONFIG_H
#define CONFIG_H

// Sensori e Moduli
#define HALL_SENSOR_PIN 3       // Sensore Hall per il vento
#define DHTPIN 2                // Sensore DHT22 collegato al pin 2
#define DHTTYPE DHT22           // Tipo di DHT utilizzato (DHT22)
#define SIM900_PWRKEY 12        // GPIO per accendere/spegnere il modulo SIM900 (D12)
#define RESPONSE_TIMEOUT 5000    // Timeout per la risposta del SIM900 (ms)

// Deep Sleep
#define uS_TO_S_FACTOR 1000000          // Conversione da secondi a microsecondi
#define DEEP_SLEEP_DURATION 3480        // Durata del deep sleep in secondi (58 minuti)

// Sensore Hall
#define RADIUS_MM 166                   // Raggio dell'anemometro in mm
#define RADIUS_M (RADIUS_MM / 1000.0)   // Conversione del raggio in metri
#define MIN_PULSE_INTERVAL 50           // Intervallo minimo tra due impulsi in millisecondi

#endif
