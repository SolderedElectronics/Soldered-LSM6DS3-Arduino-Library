/**
 *******************************************************************************************
 *
 * @file      DoubleTap.ino
 * @brief     This example will show you how to use the wake up detection feature.
 *            Connect the IMU to the board via the Qwiic connector and the interrupt pin to the digital pin 5.
 *
 * @link      solde.red/333069
 *
 * @author    Josip Šimun Kuči @ Soldered
 *******************************************************************************************/

// Includes.
#include <LSM6DS3-SOLDERED.h>

// Components.
Soldered_LSM6DS3 lsm6ds3;

// Interrupt pin.
#define INT_PIN 5

//Interrupts.
volatile int mems_event = 0;

void INT2Event_cb();

void setup() {
  // Initialize serial for output.
  Serial.begin(115200);
  
  // Initialize I2C bus.
  Wire.begin();

  //Interrupts.
  attachInterrupt(INT_PIN, INT2Event_cb, RISING);

  // Initialize Components.
  lsm6ds3.begin();
  lsm6ds3.enableAccelerator();

  // Enable Wake Up Detection.
  lsm6ds3.enableWakeUpDetection();
}

void loop() {
  if (mems_event) {
    mems_event = 0;
    LSM6DS3_Event_Status_t status;
    lsm6ds3.getEventStatus(&status);
    if (status.WakeUpStatus)
    {
      // Output data.
      Serial.println("Wake up Detected!");
    }
  }
}

void INT2Event_cb()
{
  mems_event = 1;
}
