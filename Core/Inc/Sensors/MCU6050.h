/******************************
 * File name   : MCU6050.h
 * Purpose     : Mithrill project.
 *               MCU6050 sensor
 * Author      : Tarasov Denis
 *               Filippov Denis
 * Create date : 02.03.2020
 * Last change : 26.05.2020
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
     *   uit8_t addr -- device address
     */
    explicit MCU6050(I2C_HandleTypeDef *handle, uint8_t addr);

    /* Read data from accelerometer
     *
     * Arguments:
     *   math::quater &v -- quaternion to store data
     *
     * Returns:
     *   None.
     */
    void readAccel(math::quater<float> &v) override;

    /* Read data from gyroscope
     *
     * Arguments:
     *   math::vec &v -- quaternion to store data
     *
     * Returns:
     *   None.
     */
    void readGyro(math::quater<float> &v) override;

    /* Calibrate device
     *
     * Arguments:
     *   int32_t iterations -- number of iterations to calibrate
     *
     * Returns:
     *   None.
     */
    void calibrate(int32_t iterations) override;

    /* Evaluate angles of deflection.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   Filtered angles
     */
    math::quater<float> getAnglesOfDefl() override;

    /* Evaluate absolute angles.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   Filtered angles
     */
    math::quater<float> getAbsAngles() override;

    static constexpr const uint8_t MPU6050_ADDR_1 = 0xD0,  // Device register on 5v
                      MPU6050_ADDR_2 = 0xD2;  // Device register on 3.3v
  private:
    I2C_HandleTypeDef *i2c_handle;
    uint8_t addres;
    /* MCU6050 registers */
    static constexpr const uint8_t GYRO_CONFIG_REG = 0x1b,  // Gyroscope register for config
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

    math::quater<float> calibratedGyro, // Calibrated gyroscope quaternion
                      angles,           // Filtered angles
                      calibratedAngles; // Calibrated angles
    /* Read raw data from gyroscope
     *
     * Arguments:
     *   math::quater &v -- array to store data
     *
     * Returns:
     *   None.
     */
    void readGyroRaw(math::quater<float> &v);
  }; // End of 'MCU6050' class
} // end of 'mthl' namespace

#endif // __MCU6050_H_
