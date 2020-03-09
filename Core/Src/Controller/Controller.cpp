/******************************
 * File name   : Controller.cpp
 * Purpose     : Mithrill project.
 *               Controller module.
 *               Controller class implementation.
 * Author      : Filippov Denis
 * Create date : 09.09.2020.
 * Last change : 09.09.2020.
 ******************************/

#include "stm32f4xx_hal.h"
#include "Controller/Controller.h"
#include "UART_IO.h"

extern UART_HandleTypeDef huart2;

/* Controller default constructor */
mthl::Controller::Controller()
{
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
  writeWord(&huart2, "Hello world\n");
} // End of 'mthl::Controller::Run' function


