/******************************
 * File name   : MCU6050.cpp
 * Purpose     : Mithrill project.
 *               MCU6050 sensor
 * Author      : Tarasov Denis
 * Create date : 02.03.2020
 * Last change : 03.03.2020
 ******************************/

#include "Sensors/MCU6050.h"

/* 'MCU6050' class constructor */
mthl::MCU6050::MCU6050(I2C_HandleTypeDef *handle) : i2c_handle(handle)
{
  uint8_t check = 0;
  uint8_t Data = 0;

  // Try to get signature
  HAL_I2C_Mem_Read (i2c_handle, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);
  // TODO Error handling

  if (check == SIGNATURE)  // Check device signature
  {
    // Wake the sensor up
    Data = 0;
    HAL_I2C_Mem_Write(i2c_handle, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, 1000);

    // Set DATA RATE of 1KHz
    Data = 0x07;
    HAL_I2C_Mem_Write(i2c_handle, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

    // Set accelerometer configuration +- 2g
    Data = 0x00;
    HAL_I2C_Mem_Write(i2c_handle, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

    // Set gyroscope configuration +- 250 d/s
    Data = 0x00;
    HAL_I2C_Mem_Write(i2c_handle, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);

    // Calibrate gyroscope
    calibrate(3000);
  }
} // End of 'MCU6050' constructor

/* Read accelerometer data function */
void mthl::MCU6050::readAccel(math::vec<float> &v)
{
  uint8_t buffer[6];
  HAL_I2C_Mem_Read(i2c_handle, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, buffer, 6, 1000);
  // TODO Error handling

  v[0] = (int16_t)(buffer[0] << 8 | buffer[1]) / ACC_SCALE;
  v[1] = (int16_t)(buffer[2] << 8 | buffer[3]) / ACC_SCALE;
  v[2] = (int16_t)(buffer[4] << 8 | buffer[5]) / ACC_SCALE;
} // End of 'readAccel' function

/* Read raw gyroscope data function */
void mthl::MCU6050::readGyroRaw(math::vec<float> &v)
{
  uint8_t buffer[6];
  HAL_I2C_Mem_Read(i2c_handle, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, buffer, 6, 1000);
  // TODO Error handling

  v[0] = (int16_t)(buffer[0] << 8 | buffer[1]) / GYRO_SCALE;
  v[1] = (int16_t)(buffer[2] << 8 | buffer[3]) / GYRO_SCALE;
  v[2] = (int16_t)(buffer[4] << 8 | buffer[5]) / GYRO_SCALE;
} // End of 'readGyroRaw' function

/* Read gyroscope data function */
void mthl::MCU6050::readGyro(math::vec<float> &v)
{
  readGyroRaw(v);

  v -= calibratedGyro;
} // End of 'readGyro' function

/* Calibrate device */
void mthl::MCU6050::calibrate(int32_t iterations)
{
  math::vec<float> gData;

  for (int32_t i = 0; i < iterations; ++i)
  {
    readGyroRaw(gData);
    calibratedGyro += gData;
    //HAL_Delay(3);
  }

  calibratedGyro /= (float)iterations;
} // End of 'calibrate' function
