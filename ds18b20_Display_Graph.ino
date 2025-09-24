#include <Wire.h>
#include "HT_SSD1306Wire.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#ifdef WIRELESS_STICK_V3
static SSD1306Wire display(0x3c, 500000, 17, 18, GEOMETRY_64_32, RST_OLED);
#else
static SSD1306Wire display(0x3c, 500000, 17, 18, GEOMETRY_128_64, RST_OLED);
#endif

// DS18B20
const int oneWireBus = 33;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

const int MAX_POINTS = 100;   // ~100 punti visibili
float tempHistory[MAX_POINTS];
int dataIndex = 0;
bool filled = false;

unsigned long elapsedSeconds = 0;  // tempo totale

// funzione per map con float
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(115200);
  sensors.begin();
  display.init();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // aggiorna buffer
  tempHistory[dataIndex] = temperatureC;
  dataIndex = (dataIndex + 1) % MAX_POINTS;
  if (dataIndex == 0) filled = true;
  elapsedSeconds++;

  // calcolo range Y
  int count = filled ? MAX_POINTS : dataIndex;
  float tMin = tempHistory[0], tMax = tempHistory[0];
  for (int i = 0; i < count; i++) {
    tMin = min(tMin, tempHistory[i]);
    tMax = max(tMax, tempHistory[i]);
  }
  if (tMin == tMax) { tMin -= 1; tMax += 1; }

  display.clear();

  // --- Temperatura attuale (in basso a sinistra) ---
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 54, String(temperatureC, 1) + "°C");

  // --- Coordinate grafiche adattate ---
  int graphX0 = 30;     // margine sinistro
  int graphY0 = 45;     // baseline del grafico
  int graphH  = 40;     // altezza grafico
  int graphW  = 90;     // larghezza grafico

  // Assi
  display.drawLine(graphX0, graphY0 - graphH, graphX0, graphY0);  // asse Y
  display.drawLine(graphX0, graphY0, graphX0 + graphW, graphY0);  // asse X

  // --- Tacche ---
  // Solo massimo su Y
  int yTop = graphY0 - graphH;
  display.drawLine(graphX0 - 3, yTop, graphX0, yTop);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(graphX0 - 4, yTop - 4, String(tMax, 1));

  // Solo tempo in basso a destra
  String timeStr = String(elapsedSeconds);
  int xRight = 128; // bordo destro del display
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(xRight, 54, timeStr + "s");

  // --- Grafico ---
  for (int i = 1; i < count; i++) {
    int x1 = (int)mapFloat(i - 1, 0, count - 1, graphX0, graphX0 + graphW - 1);
    int x2 = (int)mapFloat(i,     0, count - 1, graphX0, graphX0 + graphW - 1);
    int y1 = graphY0 - (int)mapFloat(tempHistory[(dataIndex + i - 1) % count], tMin, tMax, 0, graphH);
    int y2 = graphY0 - (int)mapFloat(tempHistory[(dataIndex + i) % count],     tMin, tMax, 0, graphH);
    display.drawLine(x1, y1, x2, y2);
  }

  display.display();
  delay(10000);
}
