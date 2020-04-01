/******************************
 * File name   : Filters.h
 * Purpose     : Mithrill project.
 *               IMU sensors filters
 *
 * Author      : Tarasov Denis
 * Create date : 31.03.2020
 * Last change : 01.04.2020
 ******************************/

#ifndef __FILTERS_H_
#define __FILTERS_H_

#include "Math/quater.h"

/* Mithril namespace */
namespace mthl {
  namespace filters
  {
    /* Complementary filter function.
     * Arguments:
     *   quater prev -- old angles state
     *   quater gyro -- data from gyroscope
     *   quater accel -- data from accelerometer
     *   float dtime -- time passed
     *   float  delta -- delta value for the filter
     *
     * Returns:
     *   Filtered data.
     */
    math::quater<float> complementary(math::quater<float> prev, math::quater<float> gyro,
        math::quater<float> accel, float dtime, float delta);
  } // end of 'filters' namespace
}  // end of 'mthl' namespace

#endif /* __FILTERS_H_ */
