/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functions module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 * Create date : 04.04.2020
 * Last change : 12.05.2020
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Functionality/Health/Posture/Posture.h"
#include "Filters/Filters.h"
#include "UART_IO.h"

// HAVE TO BE ADDED TO CONSTRUCTOR
extern UART_HandleTypeDef huart2;

/* Posture processing constructor */
mthl::PostureProc::PostureProc(const std::vector<std::unique_ptr<IMU>> &IMUSensors) : IMUSens(IMUSensors), deflAngles(0), calibrAngles(0)
{
  mthl::math::quater<float> gyro, accel;
  IMUSens[0]->readAccel(accel);

  calibrAngles = mthl::filters::complementary(calibrAngles, gyro, accel, 0, 1.0);

  for (int i = 0; i < 100; ++i)
  {
    IMUSens[0]->readGyro(gyro);
    IMUSens[0]->readAccel(accel);
    calibrAngles = mthl::filters::complementary(calibrAngles, gyro, accel, 0.001, 0.04);
    HAL_Delay(1);
  }

  deflAngles = calibrAngles;
} // End of 'mthl::PostureProc::PostureProc' constructor

/* Doing posture processing function */
void mthl::PostureProc::doFunction()
{
  // take angles
  // create function by dists from start and IMU-angles
  // get angle by distances of points on
  HAL_Delay(25);
} // End of 'mthl::PostureProc::doFunction' function




