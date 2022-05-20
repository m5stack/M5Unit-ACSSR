#include "M5Atom.h"
#include "UNIT_ACSSR.h"

UNIT_ACSSR SSR;

void setup() {
    M5.begin(true, false, true);
    M5.dis.fillpix(0xff0000);
    while (!SSR.begin(&Wire, 26, 32, DEVICE_DEFAULT_ADDR)) {
        Serial.println("ACSSR I2C INIT ERROR");
        delay(1000);
    }
    M5.dis.fillpix(0x0000ff);
}

void loop() {
    if (M5.Btn.wasPressed()) {
        if (SSR.setDeviceAddr(0x66)) {
            Serial.println("I2C ADDR CONFIG: 0x66");
            delay(300);
        } else {
            Serial.println("I2C ADDR CONFIG: FAIL");
            SSR.setLEDColor(0x8700ff);
        };
    };
    M5.update();
    SSR.on();
    SSR.setLEDColor(0xff0000);
    delay(900);
    SSR.off();
    SSR.setLEDColor(0x00ff00);
    delay(900);
}
