/**
 ******************************************************************************
 * @file    LSM6DS3Sensor.h
 * @author  AST
 * @version V1.0.0
 * @date    7 September 2017
 * @brief   Abstract Class of an LSM6DS3 Inertial Measurement Unit (IMU) 6 axes
 *          sensor.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __LSM6DS3Sensor_H__
#define __LSM6DS3Sensor_H__


/* Includes ------------------------------------------------------------------*/

#include "Wire.h"
#include "LSM6DS3_ACC_GYRO_Driver.h"

/* Defines -------------------------------------------------------------------*/

#define LSM6DS3_ACC_SENSITIVITY_FOR_FS_2G   0.061  /**< Sensitivity value for 2 g full scale [mg/LSB] */
#define LSM6DS3_ACC_SENSITIVITY_FOR_FS_4G   0.122  /**< Sensitivity value for 4 g full scale [mg/LSB] */
#define LSM6DS3_ACC_SENSITIVITY_FOR_FS_8G   0.244  /**< Sensitivity value for 8 g full scale [mg/LSB] */
#define LSM6DS3_ACC_SENSITIVITY_FOR_FS_16G  0.488  /**< Sensitivity value for 16 g full scale [mg/LSB] */

#define LSM6DS3_GYRO_SENSITIVITY_FOR_FS_125DPS   04.375  /**< Sensitivity value for 125 dps full scale [mdps/LSB] */
#define LSM6DS3_GYRO_SENSITIVITY_FOR_FS_245DPS   08.750  /**< Sensitivity value for 245 dps full scale [mdps/LSB] */
#define LSM6DS3_GYRO_SENSITIVITY_FOR_FS_500DPS   17.500  /**< Sensitivity value for 500 dps full scale [mdps/LSB] */
#define LSM6DS3_GYRO_SENSITIVITY_FOR_FS_1000DPS  35.000  /**< Sensitivity value for 1000 dps full scale [mdps/LSB] */
#define LSM6DS3_GYRO_SENSITIVITY_FOR_FS_2000DPS  70.000  /**< Sensitivity value for 2000 dps full scale [mdps/LSB] */

#define LSM6DS3_PEDOMETER_THRESHOLD_LOW       0x00  /**< Lowest  value of pedometer threshold */
#define LSM6DS3_PEDOMETER_THRESHOLD_MID_LOW   0x07
#define LSM6DS3_PEDOMETER_THRESHOLD_MID       0x0F
#define LSM6DS3_PEDOMETER_THRESHOLD_MID_HIGH  0x17
#define LSM6DS3_PEDOMETER_THRESHOLD_HIGH      0x1F  /**< Highest value of pedometer threshold */

#define LSM6DS3_WAKE_UP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define LSM6DS3_WAKE_UP_THRESHOLD_MID_LOW   0x0F
#define LSM6DS3_WAKE_UP_THRESHOLD_MID       0x1F
#define LSM6DS3_WAKE_UP_THRESHOLD_MID_HIGH  0x2F
#define LSM6DS3_WAKE_UP_THRESHOLD_HIGH      0x3F  /**< Highest value of wake up threshold */

#define LSM6DS3_TAP_THRESHOLD_LOW       0x01  /**< Lowest  value of wake up threshold */
#define LSM6DS3_TAP_THRESHOLD_MID_LOW   0x08
#define LSM6DS3_TAP_THRESHOLD_MID       0x10
#define LSM6DS3_TAP_THRESHOLD_MID_HIGH  0x18
#define LSM6DS3_TAP_THRESHOLD_HIGH      0x1F  /**< Highest value of wake up threshold */

#define LSM6DS3_TAP_SHOCK_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DS3_TAP_SHOCK_TIME_MID_LOW   0x01
#define LSM6DS3_TAP_SHOCK_TIME_MID_HIGH  0x02
#define LSM6DS3_TAP_SHOCK_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define LSM6DS3_TAP_QUIET_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DS3_TAP_QUIET_TIME_MID_LOW   0x01
#define LSM6DS3_TAP_QUIET_TIME_MID_HIGH  0x02
#define LSM6DS3_TAP_QUIET_TIME_HIGH      0x03  /**< Highest value of wake up threshold */

#define LSM6DS3_TAP_DURATION_TIME_LOW       0x00  /**< Lowest  value of wake up threshold */
#define LSM6DS3_TAP_DURATION_TIME_MID_LOW   0x04
#define LSM6DS3_TAP_DURATION_TIME_MID       0x08
#define LSM6DS3_TAP_DURATION_TIME_MID_HIGH  0x0C
#define LSM6DS3_TAP_DURATION_TIME_HIGH      0x0F  /**< Highest value of wake up threshold */

/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
  LSM6DS3_STATUS_OK = 0,
  LSM6DS3_STATUS_ERROR,
  LSM6DS3_STATUS_TIMEOUT,
  LSM6DS3_STATUS_NOT_IMPLEMENTED
} LSM6DS3StatusTypeDef;

typedef enum
{
  LSM6DS3_INT1_PIN,
  LSM6DS3_INT2_PIN
} LSM6DS3_Interrupt_Pin_t;

typedef struct
{
  unsigned int FreeFallStatus : 1;
  unsigned int TapStatus : 1;
  unsigned int DoubleTapStatus : 1;
  unsigned int WakeUpStatus : 1;
  unsigned int StepStatus : 1;
  unsigned int TiltStatus : 1;
  unsigned int D6DOrientationStatus : 1;
} LSM6DS3_Event_Status_t;

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an LSM6DS3 Inertial Measurement Unit (IMU) 6 axes
 * sensor.
 */
class LSM6DS3Sensor
{
  public:
    LSM6DS3Sensor                                     (TwoWire *i2c, uint8_t address=LSM6DS3_ACC_GYRO_I2C_ADDRESS_HIGH);
    LSM6DS3StatusTypeDef begin                        (void);
    LSM6DS3StatusTypeDef end                          (void);
    LSM6DS3StatusTypeDef enableAccelerator                     (void);
    LSM6DS3StatusTypeDef enableGyro                     (void);
    LSM6DS3StatusTypeDef disableAccelerator                    (void);
    LSM6DS3StatusTypeDef disableGyro                    (void);
    LSM6DS3StatusTypeDef readId                       (uint8_t *p_id);
    LSM6DS3StatusTypeDef getAcceleratorAxes                   (int32_t *pData);
    LSM6DS3StatusTypeDef getGyroAxes                   (int32_t *pData);
    LSM6DS3StatusTypeDef getAcceleratorSensitivity            (float *pfData);
    LSM6DS3StatusTypeDef getGyroSensitivity            (float *pfData);
    LSM6DS3StatusTypeDef getAcceleratorAxesRaw                (int16_t *pData);
    LSM6DS3StatusTypeDef getGyroAxesRaw                (int16_t *pData);
    LSM6DS3StatusTypeDef getAcceleratorOdr                    (float *odr);
    LSM6DS3StatusTypeDef getGyroOdr                    (float *odr);
    LSM6DS3StatusTypeDef setAcceleratorOdr                    (float odr);
    LSM6DS3StatusTypeDef setGyroOdr                    (float odr);
    LSM6DS3StatusTypeDef getAcceleratorFullScale                     (float *fullScale);
    LSM6DS3StatusTypeDef getGyroFullScale                     (float *fullScale);
    LSM6DS3StatusTypeDef setAcceleratorFullScale                     (float fullScale);
    LSM6DS3StatusTypeDef setGyroFullScale                     (float fullScale);
    LSM6DS3StatusTypeDef enableFreeFallDetection   (void);
    LSM6DS3StatusTypeDef enableFreeFallDetection   (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disableFreeFallDetection  (void);
    LSM6DS3StatusTypeDef setFreeFallThreshold      (uint8_t thr);
    LSM6DS3StatusTypeDef enablePedometer             (void);
    LSM6DS3StatusTypeDef disablePedometer            (void);
    LSM6DS3StatusTypeDef getStepCounter             (uint16_t *step_count);
    LSM6DS3StatusTypeDef resetStepCounter           (void);
    LSM6DS3StatusTypeDef setPedometerThreshold      (uint8_t thr);
    LSM6DS3StatusTypeDef enableTiltDetection        (void);
    LSM6DS3StatusTypeDef enableTiltDetection        (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disableTiltDetection       (void);
    LSM6DS3StatusTypeDef enableWakeUpDetection     (void);
    LSM6DS3StatusTypeDef enableWakeUpDetection     (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disableWakeUpDetection    (void);
    LSM6DS3StatusTypeDef setWakeUpThreshold        (uint8_t thr);
    LSM6DS3StatusTypeDef enableSingleTapDetection  (void);
    LSM6DS3StatusTypeDef enableSingleTapDetection  (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disableSingleTapDetection (void);
    LSM6DS3StatusTypeDef enableDoubleTapDetection  (void);
    LSM6DS3StatusTypeDef enableDoubleTapDetection  (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disableDoubleTapDetection (void);
    LSM6DS3StatusTypeDef setTapThreshold            (uint8_t thr);
    LSM6DS3StatusTypeDef setTapShockTime           (uint8_t time);
    LSM6DS3StatusTypeDef setTapQuietTime           (uint8_t time);
    LSM6DS3StatusTypeDef setTapDurationTime        (uint8_t time);
    LSM6DS3StatusTypeDef enable6dOrientation        (void);
    LSM6DS3StatusTypeDef enable6dOrientation        (LSM6DS3_Interrupt_Pin_t int_pin);
    LSM6DS3StatusTypeDef disable6dOrientation       (void);
    LSM6DS3StatusTypeDef get6dOrientationXl        (uint8_t *xl);
    LSM6DS3StatusTypeDef get6dOrientationXh        (uint8_t *xh);
    LSM6DS3StatusTypeDef get6dOrientationYl        (uint8_t *yl);
    LSM6DS3StatusTypeDef get6dOrientationYh        (uint8_t *yh);
    LSM6DS3StatusTypeDef get6dOrientationZl        (uint8_t *zl);
    LSM6DS3StatusTypeDef get6dOrientationZh        (uint8_t *zh);
	LSM6DS3StatusTypeDef getEventStatus             (LSM6DS3_Event_Status_t *status);
    LSM6DS3StatusTypeDef readRegister                      (uint8_t reg, uint8_t *data);
    LSM6DS3StatusTypeDef writeRegister                     (uint8_t reg, uint8_t data);
	
	/**
     * @brief Utility function to read data.
     * @param  pBuffer: pointer to data to be read.
     * @param  RegisterAddr: specifies internal address register to be read.
     * @param  NumByteToRead: number of bytes to be read.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t ioRead(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToRead)
    {
      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));
        dev_i2c->write(RegisterAddr);
        dev_i2c->endTransmission(false);

        dev_i2c->requestFrom(((uint8_t)(((address) >> 1) & 0x7F)), (byte) NumByteToRead);

        int i=0;
        while (dev_i2c->available())
        {
          pBuffer[i] = dev_i2c->read();
          i++;
        }

        return 0;
      }

      return 1;
    }
    
    /**
     * @brief Utility function to write data.
     * @param  pBuffer: pointer to data to be written.
     * @param  RegisterAddr: specifies internal address register to be written.
     * @param  NumByteToWrite: number of bytes to write.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t ioWrite(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToWrite)
    {
      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));

        dev_i2c->write(RegisterAddr);
        for (int i = 0 ; i < NumByteToWrite ; i++)
          dev_i2c->write(pBuffer[i]);

        dev_i2c->endTransmission(true);

        return 0;
      }

      return 1;
    }

  private:
    LSM6DS3StatusTypeDef setAcceleratorOdrWhenEnabled(float odr);
    LSM6DS3StatusTypeDef setGyroOdrWhenEnabled(float odr);
    LSM6DS3StatusTypeDef setAcceleratorOdrWhenDisabled(float odr);
    LSM6DS3StatusTypeDef setGyroOdrWhenDisabled(float odr);

    /* Helper classes. */
    TwoWire *dev_i2c;
    /* Configuration */
    uint8_t address;

    uint8_t X_isEnabled;
    float X_Last_ODR;
    uint8_t G_isEnabled;
    float G_Last_ODR;
};

#ifdef __cplusplus
extern "C" {
#endif
uint8_t lsm6ds3IoWrite( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
uint8_t lsm6ds3IoRead( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );
#ifdef __cplusplus
}
#endif

#endif