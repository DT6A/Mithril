/******************************
 * File name   : Controller.cpp
 * Purpose     : Mithrill project.
 *               Controller module.
 *               Controller class implementation.
 * Author      : Filippov Denis
 * Create date : 09.03.2020.
 * Last change : 04.04.2020.
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Controller.h"

#include "Sensors/MCU6050.h"
#include "Controller/Functionality/Health/Posture/Posture.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

/* Controller default constructor */
mthl::Controller::Controller()
{
  //IMUSensors.push_back(new MCU6050(&hi2c1));
  mithrilFuncs.push_back({new PostureProc(IMUSensors[0]), true});
} // End of 'mthl::Controller::Controller' constructor

/* Controller default destructor */
mthl::Controller::~Controller()
{
  for (auto imu : IMUSensors)
    delete imu;
}

/* Getting instance of controller function */
mthl::Controller & mthl::Controller::getInstance()
{
  static Controller instance;

  return instance;
} // End of 'mthl::Controller::getInstance' function

/* Run program function */
void mthl::Controller::Run()
{
  /* Initialize smth (maybe) */
  /// TODO

  /* Initialize state of request */
  Request::State state = Request::State::OK;

  /* Main loop of getting requests */
  while (state != Request::State::EXIT)
  {
    while (!reqQueue.empty())
    {
      state = reqQueue.front().doCommand();
      /* This will recomment when exceptions are added */
      /*
      try
      {
        state = reqQueue.top().doCommand();
      }
      catch (mthl::log::exception e)
      {
        /// TODO
      }
      */
      reqQueue.pop();
    }

    /* Process all powered on functions */
    for (auto mF : mithrilFuncs)
      if (mF.second)
        mF.first->doFunction();
  }
} // End of 'mthl::Controller::Run' function


