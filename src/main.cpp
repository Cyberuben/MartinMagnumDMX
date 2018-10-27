#include <Arduino.h>
#include <Conceptinetics.h>
#define DEBUG 0
#define DMX_SLAVE_CHANNELS 1

DMX_Slave dmx_slave(DMX_SLAVE_CHANNELS);

int INPUT_PINS[8] = { 4, 5, 6, 7, 8, 9, 10, 12 };

void setup() {
    // Enable DMX mode
    dmx_slave.enable();
    dmx_slave.setStartAddress(1);

    // Set input modes
    for (int i = 0; i < 8; i++) {
        pinMode(INPUT_PINS[i], INPUT_PULLUP);
    }

    pinMode(11, OUTPUT);
}

int previousAddress = 1;

void loop() {
    int address = 0;

    for (int i = 7; i >= 0; i--) {
        address = address << 1;
        address = address | (digitalRead(INPUT_PINS[i]) ^ 1);
    }

    if (address != previousAddress && address != 0) {
        previousAddress = address;
        dmx_slave.setStartAddress(address);
    }

    int value = dmx_slave.getChannelValue(1);

    analogWrite(11, value);
}