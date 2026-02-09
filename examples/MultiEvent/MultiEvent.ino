/**
 *******************************************************************************************
 *
 * @file      Pedometer.ino
 * @brief     This example will show you how to use the pedometer feature.
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
#define INT1_PIN 5
#define INT2_PIN 4

//Interrupts.
volatile int mems_event = 0;

uint16_t step_count = 0;
char report[256];

void INT1Event_cb();
void INT2Event_cb();
void sendOrientation();

void setup() {
  // Led.
  Serial.begin(115200);
  
  // Initialize I2C bus.
  Wire.begin();

  //Interrupts.
  attachInterrupt(INT1_PIN, INT1Event_cb, RISING);
  attachInterrupt(INT2_PIN, INT2Event_cb, RISING);

  // Initialize Components.
  lsm6ds3.begin();
  lsm6ds3.enableAccelerator();

  // Enable all HW events.
  lsm6ds3.enablePedometer();
  lsm6ds3.enableTiltDetection();
  lsm6ds3.enableFreeFallDetection();
  lsm6ds3.enableSingleTapDetection();
  lsm6ds3.enableDoubleTapDetection();
  lsm6ds3.enable6dOrientation();
  lsm6ds3.enableWakeUpDetection();
}

void loop() {
  if (mems_event)
  {
    mems_event = 0;
    LSM6DS3_Event_Status_t status;
    lsm6ds3.getEventStatus(&status);

    if (status.StepStatus)
    {
      // New step detected, so print the step counter
      lsm6ds3.getStepCounter(&step_count);
      snprintf(report, sizeof(report), "Step counter: %d", step_count);
      Serial.println(report);
    }

    if (status.FreeFallStatus)
    {
      // Output data.
      Serial.println("Free Fall Detected!");
    }

    if (status.TapStatus)
    {
      // Output data.
      Serial.println("Single Tap Detected!");
    }

    if (status.DoubleTapStatus)
    {
      // Output data.
      Serial.println("Double Tap Detected!");
    }

    if (status.TiltStatus)
    {
      // Output data.
      Serial.println("Tilt Detected!");
    }

    if (status.D6DOrientationStatus)
    {
      // Send 6D Orientation
	  sendOrientation();
    }

    if (status.WakeUpStatus)
    {
      // Output data.
      Serial.println("Wake up Detected!");
    }
  }
}

void INT1Event_cb()
{
  mems_event = 1;
}

void INT2Event_cb()
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
