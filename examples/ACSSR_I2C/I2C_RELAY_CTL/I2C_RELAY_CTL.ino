

/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file I2C_RELAY_CTL.ino
 * @brief I2C Relay Control Example
 * @version 0.1
 * @date 2024-09-06
 */

#include "M5_ACSSR.h"

M5_ACSSR SSR;

void setup() {
    Serial.begin(115200);
    while (!SSR.begin(&Wire, 26, 32, ACSSR_DEFAULT_ADDR)) {
        Serial.println("ACSSR I2C INIT ERROR");
        delay(1000);
    }
    Serial.print("FW Version: 0x");
    Serial.println(SSR.getVersion(), HEX);
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
