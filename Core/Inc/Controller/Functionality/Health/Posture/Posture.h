/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 *               Tarasov Denis
 * Create date : 04.04.2020
 * Last change : 19.05.2020
 ******************************/

#ifndef __POSTURE_H_
#define __POSTURE_H_

#include <memory>
#include <cmath>
#include <vector>

#include "Controller/Functionality/Functionality.h"
#include "Sensors/IMU.h"
#include "Math/quater.h"

/* Mithril namespace */
namespace mthl
{
  /* Posture processing class declaration */
  class PostureProc final : public BaseFunc
  {
  public:
    /* Posture processing constructor.
     * It will get some parametres for processing.
     *
     * Arguments:
     *  const std::vector<std::unique_ptr<IMU>> &IMUSensors -- IMU-sensor vector
     */
    PostureProc(const std::vector<std::unique_ptr<IMU>> &IMUSensors);

    /* Doing posture processing function.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   None.
     */
    void doFunction() override;

  private:
    const std::vector<std::unique_ptr<IMU>> &IMUSens; // reference on IMU-Sensors vector

    /** Ridge classifier coefficients **/
    constexpr static float a11 = -0.22837643649834735, a12 = 0.004623785286151828,
       a13 = -0.250472523316491, a21 = 0.0006772766899397244, a22 = 0.006967943364773297,
       a23 = 0.1497574860779648, a41 = 0.1617428204390021, a42 = -0.08251909275653284,
       a43 = -0.0799760851616042977, bias = -0.5213019836385582;
  }; // End of 'PostureFunc' class declaration
} // end of 'mthl' namespace

#endif // __POSTURE_H_
