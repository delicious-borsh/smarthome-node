#ifndef message_h
#define message_h
#include <Arduino.h>

#include "../sensor/sensor.h"

byte createMessage(byte stationId, Measurements measurements[], byte measurementsSize);
void getMessage(byte buffer[]);

void resetMessage();

#endif
