/******************************
 * File name   : MCU6050.h
 * Purpose     : Mithrill project.
 *               MCU6050 sensor
 * Author      : Tarasov Denis
 * Create date : 02.03.2020
 * Last change : 04.03.2020
 ******************************/

#ifndef __MCU6050_H_
#define __MCU6050_H_

#include "stm32f4xx_hal.h"

#include "IMU.h"

/* Mithril namespace */
namespace mthl
{
  /* MCU6050 class declaration
   * Class for MCU6050 device
   */
  class MCU6050 : public IMU
  {
  public:
    /* MCU6050 constructor function
     *
     * Arguments:
     *   I2C_HandleTypeDef *handle -- I2C handler
     */
    explicit MCU6050(I2C_HandleTypeDef *handle);

    /* Read data from accelerometer
     *
     * Arguments:
     *   math::vec &v -- vector to store data
     *
     * Returns:
     *   None.
     */
    void readAccel(math::vec<float> &v) override;

    /* Read data from gyroscope
     *
     * Arguments:
     *   math::vec &v -- vector to store data
     *
     * Returns:
     *   None.
     */
    void readGyro(math::vec<float> &v) override;

    /* Calibrate device
     *
     * Arguments:
     *   int32_t iterations -- number of iterations to calibrate
     *
     * Returns:
     *   None.
     */
    void calibrate(int32_t iterations) override;

  private:
    I2C_HandleTypeDef *i2c_handle;

    /* MCU6050 registers */
    static constexpr const uint8_t MPU6050_ADDR = 0xD0,  // Device register
                      GYRO_CONFIG_REG = 0x1b,  // Gyroscope register for config
                      ACCEL_CONFIG_REG = 0x1C, // Accelerometer register for config
                      GYRO_XOUT_H_REG = 0x43,  // Gyroscope register for getting data
                      ACCEL_XOUT_H_REG = 0x3B, // Accelerometer register for getting data
                      TEMP_OUT_H_REG = 0x41,   // Temperature register for getting data
                      PWR_MGMT_1_REG = 0x6B,   // Wake up register
                      WHO_AM_I_REG = 0x75,     // Identifier register
                      SMPLRT_DIV_REG = 0x19;   // Data rate setup register

    static constexpr const uint8_t SIGNATURE = 0x68; // Device signature

    /* Data scalers */
    static constexpr const float ACC_SCALE = 16384.0, // Accelerometer scale +-2g
                      GYRO_SCALE = 131.0;             // Gyroscope scale +-250 d/s

    math::vec<float> calibratedGyro; // Calibrated gyroscope vector

    /* Read raw data from gyroscope
     *
     * Arguments:
     *   math::vec &v -- array to store data
     *
     * Returns:
     *   None.
     */
    void readGyroRaw(math::vec<float> &v);
  }; // End of 'MCU6050' class
} // end of 'mthl' namespace

#endif // __MCU6050_H_
