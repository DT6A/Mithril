/******************************
 * File name   : Posture.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Posture processing classes (ML and approx. spine to function) declaration module.
 * Author      : Filippov Denis
 *               Tarasov Denis
 * Create date : 04.04.2020
 * Last change : 27.05.2020
 ******************************/

#ifndef __POSTURE_H_
#define __POSTURE_H_

#include <memory>
#include <cmath>
#include <vector>
#include <array>

#include "Controller/Functionality/Functionality.h"
#include "Sensors/IMU.h"
#include "Math/quater.h"

/* Mithril namespace */
namespace mthl
{
  // TODO: make base class for posture processing

  /* Posture processing by machine learning class declaration */
  class PostureProcML final : public BaseFunc
  {
  public:
    /* Posture processing by machine learning constructor.
     *
     * Arguments:
     *  const std::vector<std::unique_ptr<IMU>> &IMUSensors -- IMU-sensor vector
     */
    PostureProcML(const std::vector<std::unique_ptr<IMU>> &IMUSensors);

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
  }; // End of 'PostureProcML' class declaration


  /* Posture processing by approximation spine to function class declaration */
  class PostureProcASF final : public BaseFunc
  {
  public:
    /* Posture processing by approximation spine to function constructor.
     *
     * Arguments:
     *  const std::vector<std::unique_ptr<IMU>> &IMUSensors -- IMU-sensor vector
     */
    PostureProcASF(const std::vector<std::unique_ptr<IMU>> &IMUSensors);

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

    /* Spine approximation function */
    struct spineApproxFunc final
    {
      struct basePoint final
      {
        float x = 0, y = 0;
      };
      struct point final
      {
        float distNext = 0;
        float
          cosLeft = -1,
          cosRight = 1,
          sinLeft = 0,
          sinRight = 0;
      };

      std::vector<point> points{};
      static constexpr float PI = 3.1415926535;

      static float degToRad(float angleInDeg)
      {
        return angleInDeg * PI / 180;
      }

      static float radToDeg(float angleInRad)
      {
        return angleInRad * 180 / PI;
      }

      // don't forget that angles left have to be > pi / 2
      void updateAngles(const std::vector<std::pair<float, float>> &angles)
      {
        for (std::size_t i = 0; i < points.size(); ++i)
        {
          points[i].cosLeft = std::cos(degToRad(angles[i].first));
          points[i].cosRight = std::cos(degToRad(angles[i].second));
          points[i].sinLeft = std::sin(degToRad(angles[i].first));
          points[i].sinRight = std::sin(degToRad(angles[i].second));
        }
      }

      // distToNext[i] -- distance from points[i] to points[i + 1]
      // if angles.first === false, point is inflection point of function, else point in part of function
      spineApproxFunc(const std::vector<float> &distToNext
                      /*, const std::vector<std::pair<float, float>> &angles*/)
      {
        points.resize(distToNext.size());
        for (std::size_t i = 0; i < points.size(); i++)
          points[i].distNext = distToNext[i];
        /* updateAngles(angles); */
      }

      basePoint getPointByDistFromStart(float dist)
      {
        if (dist < 0)
          return {points[0].cosLeft * dist, points[0].sinLeft * dist};
        float curDist = 0, curX = 0, curY = 0;
        std::size_t i;
        for (i = 0; i < points.size(); i++)
        {
          if (curDist + points[i].distNext > dist)
            break;
          curX += points[i].cosRight * points[i].distNext;
          curY += points[i].sinRight * points[i].distNext;
          curDist += points[i].distNext;
        }
        // points.back().distNext == 0;
        i = std::min(points.size(), i);
        curX += points[i].cosRight * (dist - curDist);
        curY += points[i].sinRight * (dist - curDist);
        return {curX, curY};

        return {0, 0};
      }

      // dists between start point and that along function
      float getAngle(const std::array<float, 3> dists)
      {
        basePoint
          point1 = getPointByDistFromStart(dists[0]),
          point2 = getPointByDistFromStart(dists[1]),
          point3 = getPointByDistFromStart(dists[2]);
        basePoint
          vecOfAngle1 = {point1.x - point2.x, point1.y - point2.y},
          vecOfAngle2 = {point3.x - point2.x, point3.y - point2.y};
        float
          lenVec1 = sqrt(vecOfAngle1.x * vecOfAngle1.x + vecOfAngle1.y * vecOfAngle1.y),
          lenVec2 = sqrt(vecOfAngle2.x * vecOfAngle2.x + vecOfAngle2.y * vecOfAngle2.y);

        return radToDeg(std::acos((vecOfAngle1.x * vecOfAngle2.x + vecOfAngle1.y * vecOfAngle2.y) /
                        (lenVec1 * lenVec2)));
      }
    };

    spineApproxFunc SPFunc;
  }; // End of 'PostureProcAF' class declaration
} // end of 'mthl' namespace

#endif // __POSTURE_H_
