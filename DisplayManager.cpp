#include "DisplayManager.h"
#include <GxEPD.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>
#include <Fonts/FreeMono9pt7b.h>

// Definiamo i pin per lo schermo
GxIO_Class io(SPI, 10, 9, 8);   // CREO SERIALE PER E-INK -- CS DC RST
GxEPD_Class display(io, 8, 7);  // CREO DISPLAY PER E-INK -- Seriale RST BUSY 

void initializeDisplay() {
    display.init(115200);
    display.setRotation(2);
}

void updateDisplay(WeatherData data) {
    display.eraseDisplay();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMono9pt7b);
    display.setTextColor(GxEPD_BLACK);

    display.setCursor(0, 20);
    display.print(F("Ang: ")); display.print(data.angle, 1);
    display.print(F("° Dir: ")); display.print(data.windDirection);

    display.setCursor(0, 40);
    display.print(F("Temp: ")); display.print(data.temperature, 1); 
    display.print(F("°C Umid: ")); display.print(data.humidity, 1); display.print(F("%"));

    display.setCursor(0, 60);
    display.print(F("PPM: ")); display.print(data.PPM, 0);

    display.setCursor(0, 80);
    display.print(F("Press: ")); display.print(data.pressure, 1); display.print(F(" hPa"));

    display.setCursor(0, 100);
    display.print(F("Prev: ")); display.print(data.forecast);

    display.update();
}
