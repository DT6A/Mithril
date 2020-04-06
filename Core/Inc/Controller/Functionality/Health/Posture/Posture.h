/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 * Create date : 04.04.2020
 * Last change : 04.04.2020
 ******************************/

#ifndef __POSTURE_H_
#define __POSTURE_H_

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
     *  IMU *IMUSens -- pointer on IMU-sensor
     */
    PostureProc(IMU *IMUSens);

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
    IMU *IMUSensor; // IMU-Sensor pointer
    mthl::math::quater<float>
      deflAngles,   // deflection angles
      calibrAngles; // angles from calibration
  }; // End of 'PostureFunc' class declaration
} // end of 'mthl' namespace

#endif // __POSTURE_H_
