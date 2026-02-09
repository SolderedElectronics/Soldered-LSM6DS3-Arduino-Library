/**
 **************************************************
 *
 * @file        LSM6DS3-SOLDERED.h
 * @brief       Functions for working with LSM6DS3.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __LSM6DS3__
#define __LSM6DS3__

#include "Arduino.h"
#include "Wire.h"
#include "libs/stm32duino-LSM6DS3/src/LSM6DS3Sensor.h"

class Soldered_LSM6DS3 : public LSM6DS3Sensor
{
  public:
    Soldered_LSM6DS3(uint8_t address = LSM6DS3_ACC_GYRO_I2C_ADDRESS_HIGH, TwoWire *i2c = &Wire)
        : LSM6DS3Sensor(i2c, address)
    {
    }
};

#endif
