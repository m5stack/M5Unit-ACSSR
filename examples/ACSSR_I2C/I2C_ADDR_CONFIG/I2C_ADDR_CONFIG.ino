/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file I2C_ADDR_CONFIG.ino
 * @brief I2C Addr Config Example
 * @version 0.1
 * @date 2024-09-06
 */

#include "M5_ACSSR.h"

#define NEW_I2C_ADDR 0x51

uint8_t i2c_addr = ACSSR_DEFAULT_ADDR;

M5_ACSSR SSR;

void scan_addr() {
    // scan addr
    Serial.printf("Scan I2C Addr: \r\n");
    for (uint8_t addr = 1; addr < 127; addr++) {
        Serial.printf(".");
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.printf("\r\n");
            Serial.printf("Device I2C Addr is: 0x%02X\r\n", addr);
            i2c_addr = addr;
            break;
        }
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin(26, 32);
    while (!SSR.begin(&Wire, 26, 32, i2c_addr)) {
        Serial.println("ACSSR I2C INIT ERROR");
        scan_addr();
    }

    if (SSR.setDeviceAddr(NEW_I2C_ADDR)) {
        Serial.printf("Change I2C Addr to: 0x%02X\r\n", NEW_I2C_ADDR);
        i2c_addr = NEW_I2C_ADDR;
        SSR.begin(&Wire, 26, 32, i2c_addr);
    } else {
        Serial.println("Change I2C Addr: FAIL");
    };
}

void loop() {
    scan_addr();
    delay(1000);
}
