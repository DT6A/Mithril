/******************************
 * File name   : IMU.h
 * Purpose     : Mithrill project.
 *               IMU sensors interface
 * Author      : Tarasov Denis
 * Create date : 02.03.2020
 * Last change : 05.03.2020
 ******************************/

#ifndef __IMU_H_
#define __IMU_H_

#include <stdexcept>

#include "math/vec.h"

/* Mithril namespace */
namespace mthl
{
  /* IMU class declaration
   * Base interface for IMU sensors
   */
  class IMU
  {
  public:
    IMU() = default;
    virtual ~IMU() = default;

    /* Read data from accelerometer
     *
     * Arguments:
     *   math::vec &v -- vector to store data
     *
     * Returns:
     *   None.
     */
    virtual void readAccel(math::vec<float> &v) {throw std::logic_error("Not implemented");};

    /* Read data from gyroscope
     *
     * Arguments:
     *   math::vec &v -- vector to store data
     *
     * Returns:
     *   None.
     */
    virtual void readGyro(math::vec<float> &v) {throw std::logic_error("Not implemented");};

    /* Read data from accelerometer
     *
     * Arguments:
     *   float &t -- variable to store data
     *
     * Returns:
     *   None.
     */
    virtual void readTemp(float &t) {throw std::logic_error("Not implemented");};

    /* Calibrate device
     *
     * Arguments:
     *   int32_t iterations -- number of iterations to calibrate
     *
     * Returns:
     *   None.
     */
    virtual void calibrate(int32_t iterations = 1000) {throw std::logic_error("Not implemented");};
  }; // End of 'IMU' class
} // end of 'mthl' namespace

#endif /* __IMU_H_ */
