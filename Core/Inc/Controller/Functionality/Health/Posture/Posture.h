/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 *               Tarasov Denis
 * Create date : 04.04.2020
 * Last change : 13.05.2020
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
    constexpr static float a11 = 0.014977389982184662, a12 = -0.01118480188008519, a13 = -0.032147824131394886,
                             g11 = -2.1675882770028507, g12 = 2.3486384028881497, g13 = -2.030030389559555,
                             a21 = -0.030590159104874896, a22 = 0.01554960218675369, a23 = 0.01260956237056558,
                             g21 = 0.64924847147549, g22 = -1.847955959410111, g23 = 1.0133895279563099,
                             a41 = 0.003762414102879997, a42 = -0.006763972898504504, a43= -0.014074311031744523,
                             g41 = -0.09457515120207083, g42 = 1.193689419236368, g43 = -0.6622413215817751,
                             bias = 1.2202560232746031;
  }; // End of 'PostureFunc' class declaration
} // end of 'mthl' namespace

#endif // __POSTURE_H_
