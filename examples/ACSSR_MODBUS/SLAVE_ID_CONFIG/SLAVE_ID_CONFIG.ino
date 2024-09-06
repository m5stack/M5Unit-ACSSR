
/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file SLAVE_ID_CONFIG.ino
 * @brief MODBUS ID Config Example
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

#define NEW_SLAVE_ID 0x0050

RS485Class RS485(Serial2, 32, 26, -1, -1);

uint8_t slave_id = 0;

bool scan_addr() {
    // scan addr
    Serial.printf("Scan Slave ID: \r\n");
    for (uint8_t id = 1; id < 247; id++) {
        Serial.printf(".");
        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS, ACSSR_VERSION_HOLDING_ADDR, 1)) {
            Serial.print("\r\nfirmware version: ");
            while (ModbusRTUClient.available()) {
                Serial.printf("%02X", ModbusRTUClient.read());
            }
            Serial.printf("\r\n");
            Serial.printf("Slave ID is: 0x%02X\r\n", id);
            slave_id = id;
            return true;
            break;
        }
    }
    Serial.println("Not Found Slave ID");
    return false;
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    ModbusRTUClient.begin(115200, SERIAL_8N1);

    ModbusRTUClient.setTimeout(50);
    while (!scan_addr())
        ;
    Serial.println("Click Btn to Change Slave ID");
    if (ModbusRTUClient.holdingRegisterWrite(slave_id, ACSSR_ID_HOLDING_ADDR, NEW_SLAVE_ID)) {
        Serial.printf("Change Slave ID to: 0x%02X\r\n", NEW_SLAVE_ID);
        slave_id = NEW_SLAVE_ID;
    } else {
        Serial.println("Change Slave ID: FAIL");
    };
}

void loop() {
    scan_addr();
    delay(1000);
}
