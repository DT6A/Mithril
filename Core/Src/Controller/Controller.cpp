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
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(100);
} // End of 'mthl::Controller::Run' function


