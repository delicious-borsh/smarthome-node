#ifndef smarthome_node_h
#define smarthome_node_h
#include <Arduino.h>

#include "../message/hex.h"
#include "../message/message.h"
#include "../sensor/sensor.h"
#include "../wifi/transceiver.h"

void connectToWifi();
void process_cycle(byte nodeId);

#endif