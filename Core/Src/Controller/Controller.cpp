/******************************
 * File name   : Controller.cpp
 * Purpose     : Mithrill project.
 *               Controller module.
 *               Controller class implementation.
 * Author      : Filippov Denis
 * Create date : 09.03.2020.
 * Last change : 14.03.2020.
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Controller.h"
#include "UART_IO.h"

/* Controller default constructor */
mthl::Controller::Controller()
{
  /// Stoop initialization
} // End of 'mthl::Controller::Controller' constructor

/* Getting instance of controller function */
mthl::Controller & mthl::Controller::getInstance()
{
  static Controller instance;

  return instance;
} // End of 'mthl::Controller::getInstance' function

/* Run program function */
void mthl::Controller::Run()
{
  /* Initialize smth */
  // TODO

  /* Initialize state of request */
  Request::State state = Request::State::OK;

  /* Main loop of getting requests */
  while (state != Request::State::EXIT)
  {
    state = mthl::Request::getRequests(reqQueue);

    while (!reqQueue.empty())
    {
      reqQueue.front().doCommand();
      /* This will recomment when exceptions are added */
      /*
      try
      {
        state = reqQueue.top().doCommand();
      }
      catch (mthl::log::exception e)
      {
        // TODO
      }
      */
      reqQueue.pop();
    }
  }
} // End of 'mthl::Controller::Run' function


