#include "hex.h"

String HexString2ASCIIString(String hexstring) {
    String temp = "", sub = "", result;
    char buf[3];
    for (unsigned int i = 0; i < hexstring.length(); i += 2) {
        sub = hexstring.substring(i, i + 2);
        sub.toCharArray(buf, 3);
        char b = (char)strtol(buf, 0, 16);
        if (b == '\0') break;
        temp += b;
    }
    return temp;
}

String toHex(byte array[], int size) {
    String hexstring = "";

    for (int i = 0; i < size; i++) {
        if (array[i] < 0x10) {
            hexstring += '0';
        }

        hexstring += String(array[i], HEX);
    }

    Serial.println("Temp hex is " + hexstring);

    // return HexString2ASCIIString(hexstring);
    return hexstring;
}