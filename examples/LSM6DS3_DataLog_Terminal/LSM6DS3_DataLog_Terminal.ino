/**
 *******************************************************************************************
 *
 * @file      LSM6DS3_DataLog_Terminal.ino
 * @brief     This example will show you how to log the data from the IMU to the serial monitor.
 *            Connect the IMU to the board via the Qwiic connector.
 *
 * @link      solde.red/333069
 *
 * @author    Josip Šimun Kuči @ Soldered
 *******************************************************************************************/

// Includes.
#include <LSM6DS3-SOLDERED.h>

// Components.
Soldered_LSM6DS3 lsm6ds3;

void setup() {


  // Initialize serial for output.
  Serial.begin(115200);
  
  // Initialize I2C bus.
  Wire.begin();

  // Initialize components.
  lsm6ds3.begin();
  lsm6ds3.enableAccelerator();
  lsm6ds3.enableGyro();
}

void loop() {
  delay(250);

  // Read accelerometer and gyroscope.
  int32_t accelerometer[3];
  int32_t gyroscope[3];
  lsm6ds3.getAcceleratorAxes(accelerometer);
  lsm6ds3.getGyroAxes(gyroscope);

  // Output data.
  Serial.print("| Acc[mg]: ");
  Serial.print(accelerometer[0]);
  Serial.print(" ");
  Serial.print(accelerometer[1]);
  Serial.print(" ");
  Serial.print(accelerometer[2]);
  Serial.print(" | Gyr[mdps]: ");
  Serial.print(gyroscope[0]);
  Serial.print(" ");
  Serial.print(gyroscope[1]);
  Serial.print(" ");
  Serial.print(gyroscope[2]);
  Serial.println(" |");
}
