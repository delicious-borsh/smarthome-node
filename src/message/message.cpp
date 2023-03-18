#include "message.h"

#define MESSAGE_MAX_SIZE 128

#define TAG_SENSOR_BLOCK_BEGIN 10
#define TAG_SENSOR_TEMP 101
#define TAG_SENSOR_SOIL 102
#define TAG_SENSOR_HUM 103
#define TAG_SENSOR_GAS 104

byte message[MESSAGE_MAX_SIZE];
byte messageLength = 0;

void getMessage(byte buffer[]) {
    for (unsigned int i; i < messageLength; i++) {
        buffer[i] = message[i];
    }
}

void resetMessage() {
    for (unsigned int i; i < MESSAGE_MAX_SIZE; i++) {
        message[i] = 0;
    }

    messageLength = 0;
}

byte addHeader(byte stationId, byte payloadSize) {
    message[0] = 0;
    message[1] = stationId;
    message[2] = payloadSize;

    return 3;
}

byte convert(int value) { return map(value, 0, 1023, 0, 255); }

byte getTypeByte(SensorType type) {
    switch (type) {
        case TEMP:
            return TAG_SENSOR_TEMP;
            break;
        case SOIL:
            return TAG_SENSOR_SOIL;
            break;
        case HUM:
            return TAG_SENSOR_HUM;
            break;
        case GAS:
            return TAG_SENSOR_GAS;
            break;
        default:
            return 0;
            break;
    }
}

byte addPayload(Measurements measurements[], byte measurementsSize) {
    byte sensor_block_size = measurementsSize * 3;

    message[3] = TAG_SENSOR_BLOCK_BEGIN;
    message[4] = sensor_block_size;

    byte sensorBlockStartPosition = 5;

    byte currentPosition = sensorBlockStartPosition;

    for (unsigned int i; i < measurementsSize; i++) {
        Serial.println("Processing sensor at " + String(i));
        message[currentPosition] = getTypeByte(measurements[i].type);
        message[currentPosition + 1] = 1;
        message[currentPosition + 2] = convert(measurements[i].value);

        currentPosition += 3;
    }

    return currentPosition;
}

byte createMessage(byte stationId, Measurements measurements[],
                   byte measurementsSize) {
    byte payloadSize = addPayload(measurements, measurementsSize);
    byte headerSize = addHeader(stationId, payloadSize);

    messageLength = headerSize + payloadSize;

    return messageLength;
}