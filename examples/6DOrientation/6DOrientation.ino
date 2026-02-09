/**
 *******************************************************************************************
 *
 * @file      6DOrientation.ino
 * @brief     This example will show you how to use the 6D orientation detection feature.
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

char report[256];

void INT1Event_cb();
void sendOrientation();

void setup() {

  // Initialize serial for output.
  Serial.begin(9600);
  
  // Initialize I2C bus.
  Wire.begin();

  //Interrupts.
  attachInterrupt(INT_PIN, INT1Event_cb, RISING);

  // Initialize Components.
  lsm6ds3.begin();
  lsm6ds3.enableAccelerator();

  // Enable 6D Orientation.
  lsm6ds3.enable6dOrientation();
}

void loop() {
  if (mems_event)
  {
    mems_event = 0;
    LSM6DS3_Event_Status_t status;
    lsm6ds3.getEventStatus(&status);
    if (status.D6DOrientationStatus)
    {
      // Send 6D Orientation
	  sendOrientation();
      
    }
  }
}

void INT1Event_cb()
{
  mems_event = 1;
}

void sendOrientation()
{
  uint8_t xl = 0;
  uint8_t xh = 0;
  uint8_t yl = 0;
  uint8_t yh = 0;
  uint8_t zl = 0;
  uint8_t zh = 0;
  
  lsm6ds3.get6dOrientationXl(&xl);
  lsm6ds3.get6dOrientationXh(&xh);
  lsm6ds3.get6dOrientationYl(&yl);
  lsm6ds3.get6dOrientationYh(&yh);
  lsm6ds3.get6dOrientationZl(&zl);
  lsm6ds3.get6dOrientationZh(&zh);
  
  if ( xl == 0 && yl == 0 && zl == 0 && xh == 0 && yh == 1 && zh == 0 )
  {
    sprintf( report, "\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |  *             | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |________________| \r\n" );
  }
  
  else if ( xl == 1 && yl == 0 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
  {
    sprintf( report, "\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |             *  | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |________________| \r\n" );
  }
  
  else if ( xl == 0 && yl == 0 && zl == 0 && xh == 1 && yh == 0 && zh == 0 )
  {
    sprintf( report, "\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |  *             | " \
                      "\r\n |________________| \r\n" );
  }
  
  else if ( xl == 0 && yl == 1 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
  {
    sprintf( report, "\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |             *  | " \
                      "\r\n |________________| \r\n" );
  }
  
  else if ( xl == 0 && yl == 0 && zl == 0 && xh == 0 && yh == 0 && zh == 1 )
  {
    sprintf( report, "\r\n  __*_____________  " \
                      "\r\n |________________| \r\n" );
  }
  
  else if ( xl == 0 && yl == 0 && zl == 1 && xh == 0 && yh == 0 && zh == 0 )
  {
    sprintf( report, "\r\n  ________________  " \
                      "\r\n |________________| " \
                      "\r\n    *               \r\n" );
  }
  
  else
  {
    sprintf( report, "None of the 6D orientation axes is set in LSM6DSL - accelerometer.\r\n" );
  }
  
  Serial.print(report);
}
