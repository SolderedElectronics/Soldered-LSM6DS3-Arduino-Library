/**
 *******************************************************************************************
 *
 * @file      MinimalistExample.ino
 * @brief     Most basic example of use. Example using the LSM6DS3 with basic settings.  
 *            This sketch collects Gyro and Accelerometer data every second, then presents 
 *            it on the Serial Monitor.
 *
 *            Hardware connections:
 *            Connect SDA to A4
 *            Connect SCL to A5
 *            Connect GND and 3.3v power to the IMU
 *            Or simply use easyC cable
 *
 *            Resources:
 *            Uses Wire.h for i2c operation
 *
 *            Development environment specifics:
 *            Arduino IDE 1.8.13
 *
 *            Distributed as-is; no warranty is given.
 *
 * @link      solde.red/333069
 *
 * @authors   Owen Lyke @ SparkFun Electronics, 13 March 2019
 *            Modified by Soldered, 3 April 2023
 *******************************************************************************************/

// Include libraries
#include "LSM6DS3-SOLDERED.h"
#include "Wire.h"

// Create object from LSM library
Soldered_LSM6DS3 myIMU;

void setup()
{
    // Init serial communication
    Serial.begin(115200);
    delay(1000); // Relax...
    Serial.print("The sketch started - ");

    // Call .begin() to configure the IMU
    myIMU.begin();
}

void loop()
{
    // Get all parameters
    Serial.print("\nAccelerometer:\n");
    Serial.print(" X = ");
    Serial.println(myIMU.readFloatAccelX(), 4);
    Serial.print(" Y = ");
    Serial.println(myIMU.readFloatAccelY(), 4);
    Serial.print(" Z = ");
    Serial.println(myIMU.readFloatAccelZ(), 4);

    // Get rotational velocity
    Serial.print("\nGyroscope:\n");
    Serial.print(" X = ");
    Serial.println(myIMU.readFloatGyroX(), 4);
    Serial.print(" Y = ");
    Serial.println(myIMU.readFloatGyroY(), 4);
    Serial.print(" Z = ");
    Serial.println(myIMU.readFloatGyroZ(), 4);

    // Read the temperature
    Serial.print("\nThermometer:\n");
    Serial.print(" Degrees C = ");
    Serial.println(myIMU.readTempC(), 4);
    Serial.print(" Degrees F = ");
    Serial.println(myIMU.readTempF(), 4);

    // Relax...
    delay(1000);
}
