#include "sensor.h"

#define ARRAY_MAX_SIZE 16

Sensor sensorArray[ARRAY_MAX_SIZE];
byte currentSize = 0;

byte getCurrentSize() {
    return currentSize;
}

void addSensor(int pin, SensorType type) {
    for (unsigned int i; i < currentSize; i++) {
        if (sensorArray[i].pin == pin) {
            sensorArray[i] = Sensor{pin, type};
            return;
        };
    }

    if (currentSize >= ARRAY_MAX_SIZE) {
        return;
    } else {
        sensorArray[currentSize] = Sensor{pin, type};
    }
}

void removeSensor(int pin) {}

int read(int pin) {
    return analogRead(pin);
}

void measure(Measurements buffer[]) {
    for (unsigned int i; i < currentSize; i++) {
        int result = read(sensorArray[i].pin);
        buffer[i] = Measurements{sensorArray[i].type, result};
    }
}
