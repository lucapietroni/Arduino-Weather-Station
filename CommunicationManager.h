#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include "WeatherStation.h"

// Inizializza il modulo SIM900
void initializeSIM900();

// Invia un messaggio meteo a Telegram
void sendTelegramMessageAsync(WeatherData data);

// Verifica se il messaggio è stato inviato con successo
void sendMessage(const String& message);

#endif
