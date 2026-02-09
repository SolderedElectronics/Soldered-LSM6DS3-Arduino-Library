/**
 *******************************************************************************************
 *
 * @file      DoubleTap.ino
 * @brief     This example will show you how to use the double tap detection feature.
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

void INT1Event_cb();

void setup() {

  // Initialize serial for output.
  Serial.begin(115200);
  
  // Initialize I2C bus.
  Wire.begin();

  //Interrupts.
  attachInterrupt(INT_PIN, INT1Event_cb, RISING);

  // Initialize Components.
  lsm6ds3.begin();
  lsm6ds3.enableAccelerator();

  // Enable Double Tap Detection.
  lsm6ds3.enableDoubleTapDetection();
}

void loop() {
  if (mems_event) {
    mems_event = 0;
    LSM6DS3_Event_Status_t status;
    lsm6ds3.getEventStatus(&status);
    if (status.DoubleTapStatus)
    {
      // Output data.
      Serial.println("Double Tap Detected!");
    }
  }
}

void INT1Event_cb()
{
  mems_event = 1;
}
