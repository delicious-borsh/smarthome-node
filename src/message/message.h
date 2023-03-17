#ifndef message_h
#define message_h
#include <Arduino.h>

#include "../sensor/sensor.h"

void createMessage(byte stationId, Measurements measurements[], byte measurementsSize);
int getMessageLength();
void getMessage(byte buffer[]);

void resetMessage();

#endif
