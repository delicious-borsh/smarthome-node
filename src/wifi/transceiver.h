#ifndef transceiver_h
#define transceiver_h
#include <Arduino.h>

void initialize();
void send(String data);
void connectToHost(String host, String port);
void disconnect();

void configureAsStation();
void connectToWIFI();
String sendStringRequest(String data);
String prepareData(String data);
String getHeaders(int contentLength);
void sendCommand(String command, const int timeout);

#endif
