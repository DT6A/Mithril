/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functions module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 * Create date : 04.04.2020
 * Last change : 05.04.2020
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Functionality/Health/Posture/Posture.h"
#include "Filters/Filters.h"
#include "UART_IO.h"

// HAVE TO BE ADDED TO CONSTRUCTOR
extern UART_HandleTypeDef huart2;

/* Posture processing constructor */
mthl::PostureProc::PostureProc(IMU *IMUSens) : IMUSensor(IMUSens), deflAngles(0), calibrAngles(0)
{
  mthl::math::quater<float> gyro, accel;
  IMUSensor->readAccel(accel);

  calibrAngles = mthl::filters::complementary(calibrAngles, gyro, accel, 0, 1.0);

  for (int i = 0; i < 100; ++i)
  {
    IMUSensor->readGyro(gyro);
    IMUSensor->readAccel(accel);
    calibrAngles = mthl::filters::complementary(calibrAngles, gyro, accel, 0.001, 0.04);
    HAL_Delay(1);
  }

  deflAngles = calibrAngles;
} // End of 'mthl::PostureProc::PostureProc' constructor

/* Doing posture processing function */
void mthl::PostureProc::doFunction()
{
  static mthl::math::quater<float> gyro, accel, resultAngle;

  IMUSensor->readGyro(gyro);
  IMUSensor->readAccel(accel);

  deflAngles = mthl::filters::complementary(deflAngles, gyro, accel, 0.04, 0.2);
  resultAngle = deflAngles - calibrAngles;
  mthl::writeFloat(&huart2, resultAngle[0], " ");
  //mthl::writeFloat(&huart2, resultAngle[1], " ");
  mthl::writeFloat(&huart2, resultAngle[2], "\n");
  //mthl::writeFloat(&huart2, resultAngle[3], "\n");
  //mthl::writeFloat(&huart2, deflAngles[3], "\n");

  HAL_Delay(25);
} // End of 'mthl::PostureProc::doFunction' function




