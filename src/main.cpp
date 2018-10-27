#include <Arduino.h>
#include <Conceptinetics.h>
#define DEBUG 0
#define DMX_SLAVE_CHANNELS 1

DMX_Slave dmx_slave(DMX_SLAVE_CHANNELS);

int INPUT_PINS[9] = { 4, 5, 6, 7, 8, 9, 10, 11, 12 };

void setup() {
    // Enable DMX mode
    dmx_slave.enable();
    dmx_slave.setStartAddress(0);

    // Set input modes
    for (int i = 0; i < 9; i++) {
        pinMode(INPUT_PINS[i], INPUT_PULLUP);
    }
}

int previousAddress = 0;

void loop() {
    int address = 0;

    for (unsigned char i = 8; i >= 0; i--) {
        address = address << 1;
        address = address | (digitalRead(INPUT_PINS[i]) ^ 1);
    }

    if (address != previousAddress) {
        previousAddress = address;
        dmx_slave.setStartAddress(address);
    }

    delay(1000);
}