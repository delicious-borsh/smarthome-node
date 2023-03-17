#include <Arduino.h>
#include <SoftwareSerial.h>

#include "message/hex.h"
#include "message/message.h"
#include "sensor/sensor.h"
#include "wifi/transceiver.h"

#define STATION_ID 0

void setup() {
    Serial.begin(19200);

    initialize();
}

String createMessage() {
    addSensor(A0, TEMP);
    addSensor(A1, HUM);

    Measurements measurements[2];

    measure(measurements);

    createMessage(STATION_ID, measurements, 2);

    byte msg_len = getMessageLength();

    byte msg[msg_len];

    getMessage(msg);

    return toHex(msg, msg_len);
}

void loop() {
    connectToHost("", "");

    String msg = createMessage();

    String response = send("GET /state/all?id=114&payload=" + msg);

    Serial.println("response = " + response);
}