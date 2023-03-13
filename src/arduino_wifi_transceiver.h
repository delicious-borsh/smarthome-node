#ifndef arduino_wifi_transceiver_h
#define arduino_wifi_transceiver_h
#include <Arduino.h>


void initialize();
String send(String data);
void connectToHost(String host, String port);
void disconnect();


void configureAsStation();
void connectToWIFI();
String sendStringRequest(String data);
String prepareData(String data);
String getHeaders(int contentLength);
String sendCommand(String command, const int timeout);

#endif
