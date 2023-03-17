#ifndef sensor_h
#define sensor_h
#include <Arduino.h>

enum SensorType {
    TEMP,
    SOIL,
    HUM,
    GAS,
};

struct Sensor {
    int pin;
    SensorType type;
};

struct Measurements {
    SensorType type;
    int value;
};

byte getCurrentSize();
void addSensor(int pin, SensorType type);
void removeSensor(int pin);
void measure(Measurements buffer[]);

#endif
