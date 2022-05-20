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
    Serial.print("FW Version: 0x");
    Serial.println(SSR.getVersion(), HEX);
    M5.dis.fillpix(0x0000ff);
}

void loop() {
    SSR.on();
    Serial.print("ACSSR STATUS: ");
    Serial.println(SSR.status());
    SSR.setLEDColor(0xff0000);
    Serial.print("LED COLOR: 0x");
    Serial.println(SSR.getLEDColor(), HEX);
    delay(900);
    SSR.off();
    Serial.print("ACSSR STATUS: ");
    Serial.println(SSR.status());
    SSR.setLEDColor(0x00ff00);
    Serial.print("LED COLOR: 0x");
    Serial.println(SSR.getLEDColor(), HEX);
    delay(900);
}
