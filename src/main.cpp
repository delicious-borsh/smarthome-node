#include <Arduino.h>

#include <SoftwareSerial.h>
#include "arduino_wifi_transceiver.h"


void setup() {
  Serial.begin(19200);

  initialize();
}

void loop() {
  connectToHost("", "");

  send("GET /state/all?id=114");
}
