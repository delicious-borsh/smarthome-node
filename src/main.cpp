#include <Arduino.h>

#include "core/smarthome_node.h"

#define STATION_ID 0

void setup() {
    Serial.begin(19200);

    initialize();
}

void loop() { process_cycle(STATION_ID); }