/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functions module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 *               Tarasov Denis
 * Create date : 04.04.2020
 * Last change : 19.05.2020
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Functionality/Health/Posture/Posture.h"
#include "Filters/Filters.h"
#include "Controller/Controller.h"
#include "UART_IO.h"

extern UART_HandleTypeDef huart6;

/* Posture processing constructor */
mthl::PostureProc::PostureProc(const std::vector<std::unique_ptr<IMU>> &IMUSensors) : IMUSens(IMUSensors)
{

} // End of 'mthl::PostureProc::PostureProc' constructor

/* Doing posture processing function */
void mthl::PostureProc::doFunction()
{
  if (!mthl::Controller::getInstance().isPostureOnGet())
    return;

  auto deviceAngles1 = IMUSens[0]->getAngles(),
    deviceAngles2 = IMUSens[1]->getAngles(),
    deviceAngles3 = IMUSens[2]->getAngles();

  mthl::math::quater<float> deviceGravity1, deviceGravity2, deviceGravity3;

  IMUSens[0]->readAccel(deviceGravity1);
  IMUSens[1]->readAccel(deviceGravity2);
  IMUSens[2]->readAccel(deviceGravity3);

  bool isPostureCorrect = (a11 * deviceAngles1[0] + a12 * deviceAngles1[1] + a13 * deviceAngles1[2] +
      g11 * deviceGravity1[0] + g12 * deviceGravity1[1] + g13 * deviceGravity1[2] +
      a21 * deviceAngles2[0] + a22 * deviceAngles2[1] + a23 * deviceAngles2[2] +
      g21 * deviceGravity2[0] + g22 * deviceGravity2[1] + g23 * deviceGravity2[2] +
      a41 * deviceAngles3[0] + a42 * deviceAngles3[1] + a43 * deviceAngles3[2] +
      g41 * deviceGravity3[0] + g42 * deviceGravity3[1] + g43 * deviceGravity3[2]) > bias;

  mthl::writeInt(&huart6, isPostureCorrect);

  HAL_Delay(20);
} // End of 'mthl::PostureProc::doFunction' function




