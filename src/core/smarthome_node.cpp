#include "smarthome_node.h"

void connectToHost() { initialize(); }

void printMsg(byte msg[], byte msgLen) {
    Serial.println("Print msg before hex. Len=" + String(msgLen));

    for (byte i = 0; i < msgLen; i++) {
        Serial.println(String(msg[i]));
    }

    Serial.println("End print msg");
}

String createMessage(byte nodeId) {
    removeSensor(0);

    addSensor(A0, TEMP);
    addSensor(A1, HUM);
    // addSensor(A2, TEMP);

    Measurements measurements[2];

    measure(measurements);

    resetMessage();

    byte msg_len = createMessage(nodeId, measurements, 2);

    byte msg[msg_len];

    getMessage(msg);

    printMsg(msg, msg_len);

    String hex = toHex(msg, msg_len);

    Serial.println("Hex is " + hex);

    return hex;
}

void process_cycle(byte nodeId) {
    connectToHost("", "");

    String msg = createMessage(nodeId);

    String response = send("GET /state/all?id=114&payload=" + msg);

    Serial.println("response = " + response);
}