/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Posture processing class declaration module.
 * Author      : Filippov Denis
 * Create date : 04.04.2020
 * Last change : 12.05.2020
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
    mthl::math::quater<float>
      deflAngles,   // deflection angles
      calibrAngles; // angles from calibration

    struct spineApproxFunc final
    {
      struct basePoint
      {
        float x = 0, y = 0;
      };
      struct point final
      {
        float distPrev, distNext;
        float direv = 100;
        float x = 0, y = 0;
      };

      std::vector<point> points{};
      spineApproxFunc(const std::vector<float> &dists, const std::vector<std::pair<bool, float>> &angles)
      {
        points.resize(angles.size());
        if (dists.size())
          points[0] = {-1, dists[0], angles[0].first ? std::atan(angles[0].second): 1000};
        for (std::size_t i = 1; i < points.size() - 1; i++)
          points[i] = {dists[i - 1], dists[i], angles[i].first ? std::atan(angles[i].second) : 1000};
      }

      basePoint getPointByDist(float dist)
      {
        // TODO
        return {0, 0};
      }
      // dists between start point and that along function
      float getAngle(float dist1, float dist2, float dist3)
      {
        basePoint p1 = getPointByDist(dist1), p2 = getPointByDist(dist2), p3 = getPointByDist(dist3);
        basePoint v1 = {p1.x - p2.x, p1.y - p2.y}, v2 = {p3.x - p2.x, p3.y - p2.y};
        float
          len1 = v1.x * v1.x + v1.y * v1.y,
          len2 = v2.x * v2.x + v2.y * v2.y;
        return std::acos((v1.x * v2.x + v1.y * v2.y) / (len1 * len2)) * 180 / 3.14159265;
      }
    };
  }; // End of 'PostureFunc' class declaration
} // end of 'mthl' namespace

#endif // __POSTURE_H_
