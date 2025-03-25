#ifndef SIM900MANAGER_H
#define SIM900MANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>

extern HardwareSerial sim900;  // Dichiara sim900 come variabile globale accessibile ad altri file

void powerOnSIM900();
void setupGPRS();
bool isGPRSConnected();
bool checkSIM900Response(const String& expectedResponse, unsigned long timeout);

#endif
