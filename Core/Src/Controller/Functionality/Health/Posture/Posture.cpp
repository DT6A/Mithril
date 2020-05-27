/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functions module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 *               Tarasov Denis
 * Create date : 04.04.2020
 * Last change : 26.05.2020
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Functionality/Health/Posture/Posture.h"
#include "Filters/Filters.h"
#include "Controller/Controller.h"
#include "UART_IO.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

bool isFirstColibProc = true;
/* Posture processing by machine learning constructor */
mthl::PostureProcML::PostureProcML(const std::vector<std::unique_ptr<IMU>> &IMUSensors) : IMUSens(IMUSensors)
{

} // End of 'mthl::PostureProcML::PostureProcML' constructor

/* Doing posture processing function */
void mthl::PostureProcML::doFunction()
{
  if (!mthl::Controller::getInstance().isPostureOnGet())
    return;

  auto deviceAngles1 = IMUSens[0]->getAnglesOfDefl(),
    deviceAngles2 = IMUSens[1]->getAnglesOfDefl(),
    deviceAngles3 = IMUSens[2]->getAnglesOfDefl();

  mthl::math::quater<float> deviceGravity1, deviceGravity2, deviceGravity3;

  IMUSens[0]->readAccel(deviceGravity1);
  IMUSens[1]->readAccel(deviceGravity2);
  IMUSens[2]->readAccel(deviceGravity3);

  float realBias  = (a11 * deviceAngles1[0] + a12 * deviceAngles1[1] + a13 * deviceAngles1[2] +
      //g11 * deviceGravity1[0] + g12 * deviceGravity1[1] + g13 * deviceGravity1[2] +
      a21 * deviceAngles2[0] + a22 * deviceAngles2[1] + a23 * deviceAngles2[2] +
      //g21 * deviceGravity2[0] + g22 * deviceGravity2[1] + g23 * deviceGravity2[2] +
      a41 * deviceAngles3[0] + a42 * deviceAngles3[1] + a43 * deviceAngles3[2]);
      //g41 * deviceGravity3[0] + g42 * deviceGravity3[1] + g43 * deviceGravity3[2]);/// > bias;

  static bool prev = false;
  bool isPostureCorrect = (realBias >= bias);//(-0.4 <= realBias && realBias <= 0.9);
  if (isFirstColibProc)
  {
    if (isPostureCorrect)
        mthl::writeWord(&huart6, " Good\n");
    else
      mthl::writeWord(&huart6, " Bad\n");

    isFirstColibProc = false;
  }
  else if (isPostureCorrect != prev)
  {
    if (isPostureCorrect)
      mthl::writeWord(&huart6, " Good\n");
    else
      mthl::writeWord(&huart6, " Bad\n");
  }
  prev = isPostureCorrect;

  mthl::writeInt(&huart2, isPostureCorrect, "     ");
  mthl::writeFloat(&huart2, realBias, "     ");
  // 1
  mthl::writeFloat(&huart2, deviceAngles1[0], ";");
  mthl::writeFloat(&huart2, deviceAngles1[1], ";");
  mthl::writeFloat(&huart2, deviceAngles1[2], ";");

  mthl::writeFloat(&huart2, deviceGravity1[0], ";");
  mthl::writeFloat(&huart2, deviceGravity1[1], ";");
  mthl::writeFloat(&huart2, deviceGravity1[2], ";");

  // 2
  mthl::writeFloat(&huart2, deviceAngles2[0], ";");
  mthl::writeFloat(&huart2, deviceAngles2[1], ";");
  mthl::writeFloat(&huart2, deviceAngles2[2], ";");

  mthl::writeFloat(&huart2, deviceGravity2[0], ";");
  mthl::writeFloat(&huart2, deviceGravity2[1], ";");
  mthl::writeFloat(&huart2, deviceGravity2[2], ";");

  // 3
  mthl::writeFloat(&huart2, deviceAngles3[0], ";");
  mthl::writeFloat(&huart2, deviceAngles3[1], ";");
  mthl::writeFloat(&huart2, deviceAngles3[2], ";");

  mthl::writeFloat(&huart2, deviceGravity3[0], ";");
  mthl::writeFloat(&huart2, deviceGravity3[1], ";");
  mthl::writeFloat(&huart2, deviceGravity3[2], ";");

  mthl::writeChar(&huart2, '\n');
/*
*/
  HAL_Delay(20);
} // End of 'mthl::PostureProcML::doFunction' function


namespace
{
  /// Number of point == 5
  // TODO
  static const std::vector<float> dists = {16, 11, 17, 16, 0};
      //{14.5, 9.5, 17.5, 18, 0};
}
/* Posture processing by approximation to function constructor */
mthl::PostureProcASF::PostureProcASF(const std::vector<std::unique_ptr<IMU>> &IMUSensors)
  : IMUSens(IMUSensors), SPFunc(dists)
{
} // End of 'mthl::PostureProcASF::PostureProcASF' constructor

/* Doing posture processing function */
void mthl::PostureProcASF::doFunction()
{
  if (!mthl::Controller::getInstance().isPostureOnGet())
    return;
  // take angles
  auto deviceAngles1 = IMUSens[0]->getAbsAngles(),
    deviceAngles2 = IMUSens[1]->getAbsAngles(),
    deviceAngles3 = IMUSens[2]->getAbsAngles();

  // Correction of angles
  deviceAngles1[0] += spineApproxFunc::PI / 2;
  deviceAngles2[0] += spineApproxFunc::PI / 2;
  deviceAngles3[0] = spineApproxFunc::PI / 2 - deviceAngles3[0];

  // update angles
  // TODO: check axis of angles. Result -- we need axis
  SPFunc.updateAngles({{deviceAngles1[0], deviceAngles1[0]},
                       {deviceAngles1[0], deviceAngles2[0]},
                       {deviceAngles2[0], deviceAngles2[0]},
                       {deviceAngles2[0], deviceAngles3[0]},
                       {deviceAngles3[0], deviceAngles3[0]}});

  // get angle by distances of points on
  struct angle
  {
    const std::array<float, 3> dists{};
    const float minValue, maxValue;
    bool check(float angle) const
    {
      return minValue <= angle && angle <= maxValue;
    }
  };

  // TODO: add distances
  static const angle angles[] =
  {
    {{dists[0] + dists[1], dists[0] + dists[1] + dists[2],
      dists[0] + dists[1] + dists[2] + dists[3]}, 139, 152}, // upper angle, C3-TH5-L3
    {{0, dists[0], dists[0] + dists[1]}, 137, 153}, // lower angle, TH5-L3-as
  };

  static bool prev = false;
  bool isPostureCorrect = true;
  float angleReal[2] = {SPFunc.getAngle(angles[0].dists), SPFunc.getAngle(angles[1].dists)};
  isPostureCorrect &= angles[0].check(angleReal[0]);
  //isPostureCorrect &= angles[1].check(angleReal[1]);

  mthl::writeFloat(&huart2, angleReal[0], ";");
  mthl::writeFloat(&huart2, angleReal[1], ";           ");
  if (isFirstColibProc)
  {
    if (isPostureCorrect)
        mthl::writeWord(&huart6, " Good\n");
    else
      mthl::writeWord(&huart6, " Bad\n");

    isFirstColibProc = false;
  }
  else if (isPostureCorrect != prev)
  {
    if (isPostureCorrect)
      mthl::writeWord(&huart6, " Good\n");
    else
      mthl::writeWord(&huart6, " Bad\n");
  }
  prev = isPostureCorrect;

  mthl::writeInt(&huart2, isPostureCorrect, "     ");

  // 1
  mthl::writeFloat(&huart2, deviceAngles1[0], ";");
  deviceAngles1 = IMUSens[0]->getAnglesOfDefl(),
  mthl::writeFloat(&huart2, deviceAngles1[0], ";      ");
  //mthl::writeFloat(&huart2, deviceAngles1[1], ";");
  //mthl::writeFloat(&huart2, deviceAngles1[2], ";");
  // 2
  mthl::writeFloat(&huart2, deviceAngles2[0], ";");
  deviceAngles2 = IMUSens[1]->getAnglesOfDefl(),
  mthl::writeFloat(&huart2, deviceAngles2[0], ";     ");
  //mthl::writeFloat(&huart2, deviceAngles2[1], ";");
  //mthl::writeFloat(&huart2, deviceAngles2[2], ";");

  // 3
  mthl::writeFloat(&huart2, deviceAngles3[0], ";");
  deviceAngles3 = IMUSens[2]->getAnglesOfDefl();
  mthl::writeFloat(&huart2, deviceAngles3[0], ";");
  //mthl::writeFloat(&huart2, deviceAngles3[1], ";");
  //mthl::writeFloat(&huart2, deviceAngles3[2], ";");
/*
*/
  mthl::writeChar(&huart2, '\n');

  HAL_Delay(100);
} // End of 'mthl::PostureProcASF::doFunction' function





