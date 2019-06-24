#include <SoftwareSerial.h>
#include "pinning.h"

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

char bluetooth_read() {
    char value;
    if (bluetooth.available()) {
        value = bluetooth.read();
    }

    return value;
}