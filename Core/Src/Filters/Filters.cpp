/******************************
 * File name   : Filters.cpp
 * Purpose     : Mithrill project.
 *               IMU sensors filters
 *               
 * Author      : Tarasov Denis
 * Create date : 31.03.2020
 * Last change : 01.04.2020
 ******************************/

#include "Filters/Filters.h"

/* Complementary filter function */
mthl::math::quater<float> mthl::filters::complementary(mthl::math::quater<float> prev,
    mthl::math::quater<float> gyro, mthl::math::quater<float> accel, float dtime, float delta)
{
  using mthl::math::quater;

  return (prev + gyro * dtime) * (1 - delta) + quater<float>(
      atan2(accel[0], sqrt(accel[1] * accel[1] + accel[2] * accel[2])),
      atan2(accel[1], sqrt(accel[0] * accel[0] + accel[2] * accel[2])),
      atan2(sqrt(accel[0] * accel[0] + accel[1] * accel[1]), accel[2])
      ) * delta * 180 / 3.14159265;
}
