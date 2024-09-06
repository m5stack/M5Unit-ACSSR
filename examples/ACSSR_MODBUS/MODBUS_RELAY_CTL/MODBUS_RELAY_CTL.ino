/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file MODBUS_RELAY_CTL.ino
 * @brief MODBUS Relay Control Example
 * @version 0.1
 * @date 2024-09-06
 * 
 * 
 * @Dependent Library: 
 * ArduinoModbus: https://github.com/m5stack/ArduinoModbus
 * Arduino485: https://github.com/m5stack/ArduinoRS485
 */

#include "M5_ACSSR.h"
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

RS485Class RS485(Serial2, 32, 26, -1, -1);

uint8_t slave_id = 0;

void setup() {
    Serial.begin(115200);
    delay(2000);
    ModbusRTUClient.begin(115200, SERIAL_8N1);
    slave_id = ACSSR_DEFAULT_SLAVE_ID;
}

void loop() {
    // ACSSR CTL ON
    ModbusRTUClient.coilWrite(slave_id, ACSSR_RELAY_COIL_ADDR, 0xff);
    delay(600);
    // ACSSR LED CTL RED COLOR
    ModbusRTUClient.holdingRegisterWrite(slave_id, ACSSR_LED_HOLDING_ADDR, 0xF800);

    delay(600);
    // GET ACSSR STATUS
    if (ModbusRTUClient.requestFrom(slave_id, COILS, ACSSR_RELAY_COIL_ADDR, 1)) {
        Serial.print("ACSSR STATUS: ");
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    delay(600);
    // GET ACSSR LED COLOR
    if (ModbusRTUClient.requestFrom(slave_id, HOLDING_REGISTERS, ACSSR_LED_HOLDING_ADDR, 1)) {
        Serial.print("LED COLOR: 0x");
        uint16_t color = 0;
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        if (color == 0xF800) {
        }
        Serial.println();
    }

    delay(600);

    // ACSSR CTL OFF
    ModbusRTUClient.coilWrite(slave_id, ACSSR_RELAY_COIL_ADDR, 0x00);
    delay(600);
    // ACSSR LED CTL GREEN COLOR
    ModbusRTUClient.holdingRegisterWrite(slave_id, ACSSR_LED_HOLDING_ADDR, 0x07E0);

    delay(600);

    // GET ACSSR STATUS
    if (ModbusRTUClient.requestFrom(slave_id, COILS, ACSSR_RELAY_COIL_ADDR, 1)) {
        Serial.print("ACSSR STATUS: ");
        uint16_t color = 0;
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    delay(600);
    // GET ACSSR LED COLOR
    if (ModbusRTUClient.requestFrom(slave_id, HOLDING_REGISTERS, ACSSR_LED_HOLDING_ADDR, 1)) {
        Serial.print("LED COLOR: 0x");
        uint16_t color = 0;

        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    delay(600);
    // GET ACSSR FW VERSION
    if (ModbusRTUClient.requestFrom(slave_id, HOLDING_REGISTERS, ACSSR_VERSION_HOLDING_ADDR, 1)) {
        Serial.print("Firmware Version: 0x");
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    delay(600);
}
