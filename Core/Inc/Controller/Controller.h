/******************************
 * File name   : Controller.h
 * Purpose     : Mithrill project.
 *               Controller module.
 *               Controller class declaration.
 * Author      : Filippov Denis
 * Create date : 09.03.2020
 * Last change : 22.03.2020
 ******************************/

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <vector>
#include <queue>
#include <functional>

#include "Sensors/IMU.h"
#include "Request/Request.h"

/* Mithril namespace */
namespace mthl
{
  /* Controller class declaration.
   * It is a singletone class.
   * This class start, process and finished whole program on STM.
   * It initializes all sensors, gets requests from application, takes data from
   * sensors and work with them.
   */
  class Controller
  {
  public:
    /* Getting instance of controller function.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   Reference on singletone controller.
     */
    static Controller & getInstance();

    /* Run program function.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   None.
     */
    void Run();

  private:
    std::vector<IMU> IMUSensors;  // list of IMU-sensors
    std::queue<Request> reqQueue; // queue of requests

    /* Declaration of friend. This and only this external function
     * need reqQueue. Moreover, it will put requests in this queue only, because we have
     * singletone controller. In result we avoid globalization of reqQueue.
     */
    friend void ::HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

    /* Controller default constructor.
     * Constructor is private because controller is singletone.
     *
     * Arguments:
     *   None.
     */
    Controller();
  }; // End of 'Controller' class
} // end of 'mthl' namespace

#endif // __CONTROLLER_H_
