#include "transceiver.h"

#include <SoftwareSerial.h>

#define RX 10
#define TX 11

String AP = "Asus";
String PASS = "VASILISA";
String HOST = "192.168.1.29";
String PORT = "8000";

SoftwareSerial esp8266(RX, TX);

void initialize() {
    esp8266.begin(9600);

    boolean FAIL_8266 = false;
    do {
        esp8266.print("AT");
        esp8266.print("\r\n");
        delay(3000);

        if (esp8266.find((char*)"OK")) {
            Serial.println("Module is ready");
            configureAsStation();
            connectToWIFI();

            Serial.println("Setup finish");

            FAIL_8266 = false;
        } else {
            Serial.println("Failed to get response. Trying again");
            delay(500);
            FAIL_8266 = true;
        }
    } while (FAIL_8266);
}

void connectToHost(String host, String port) {
    sendCommand("AT+CIPMUX=0", 1000);
    delay(3000);

    sendCommand("AT+CIPSTART=,\"TCP\",\"" + HOST + "\"," + PORT, 2000);
    delay(3000);
}

void disconnect() {}

void configureAsStation() {
    boolean FAIL_8266 = false;
    do {
        Serial.println("Configuring as a station");
        esp8266.print("AT+CWMODE=1");
        esp8266.print("\r\n");
        delay(1000);
        if (esp8266.find((char*)"OK")) {
            Serial.println("Configured");
            FAIL_8266 = false;
        } else {
            Serial.println("Error, trying again");
            delay(500);
            FAIL_8266 = true;
        }
    } while (FAIL_8266);
}

void connectToWIFI() {
    boolean FAIL_8266 = false;

    do {
        Serial.println("Connecting to " + AP);
        esp8266.print("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"");
        esp8266.print("\r\n");
        delay(3000);

        if (esp8266.find((char*)"WIFI GOT IP")) {
            Serial.println("Connected");
            FAIL_8266 = false;
        } else {
            Serial.println("Error, trying again");
            delay(500);
            FAIL_8266 = true;
        }
    } while (FAIL_8266);
}

void send(String data) {
    String getData = "GET /state/all?id=114";
    sendCommand("AT+CIPMUX=0", 3000);
    delay(3000);
    sendCommand("AT+CIPSTART=\"TCP\",\"" + HOST + "\"," + PORT, 3000);

    sendStringRequest(getData);

    delay(1500);

    sendCommand("AT+CIPCLOSE", 1000);
}

String sendStringRequest(String data) {
    String cipSend = "AT+CIPSEND=";
    // cipSend += 0;
    // cipSend += ",";
    cipSend += data.length() + 4;
    sendCommand(cipSend, 1000);
    sendCommand(prepareData(data), 2000);
}

String prepareData(String data) {
    return data + "\r\n" + getHeaders(data.length());
}

String getHeaders(int contentLength) {
    String httpHeader;
    httpHeader += "Accept: ";
    httpHeader += "text/plain";
    httpHeader += "\r\n";
    httpHeader += "Content-Length: ";
    httpHeader += contentLength;
    httpHeader += "\r\n";
    httpHeader += "Connection: close";
    httpHeader += "\r\n";

    return httpHeader;
}

void sendCommand(String command, const int timeout) {
  Serial.println("Executing command: " + command);

  String response = "";

  esp8266.print(command);
  esp8266.print("\r\n");

  long int startTime = millis();

  while (  millis()-startTime < timeout) {
    while (esp8266.available()) {
      response += esp8266.readString() + "\n";
    }
  }

  Serial.println("Response : " + response);
}