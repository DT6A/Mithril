/******************************
 * File name   : Request.cpp
 * Purpose     : Mithrill project.
 *               Controller module
 *               Request class implementation
 * Author      : Filippov Denis
 * Create date : 10.03.2020
 * Last change : 22.03.2020
 ******************************/

#include "Controller/Request/Request.h"
#include "UART_IO.h"

/* There are some externs. I don't think, that we have avoid it in this situation,
 * because there isn't any other places, where we need UART (for now).
 */
/* UART handler 2 */
extern UART_HandleTypeDef huart2;
/* UART handler 6 (for bluetooth) */
extern UART_HandleTypeDef huart6;

/* Map who mathes byte and it command */
std::map<uint8_t, mthl::Request::Command> mthl::Request::fromByteToCmdMap =
{
  {'1', Command::POWER_ON_LED},
  {'2', Command::POWER_OFF_LED}
};

/* Time variable, will be deleted. It helps to power on LD2 */
static bool isLD2On = false;
/* Map who matches commands and their function */
std::map<mthl::Request::Command, std::function<mthl::Request::State(void)>> mthl::Request::fromCmdToFuncMap =
{
  {Command::POWER_ON_LED,
   []() -> State
   {
     if (!isLD2On)
       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5), isLD2On = true;
     return State::OK;
   }
  },

  {Command::POWER_OFF_LED,
   []() -> State
   {
     if (isLD2On)
       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5), isLD2On = false;
     return State::OK;
   }
  }
};

/* Request from byte constructor */
mthl::Request::Request(uint8_t byte)
  : command(fromByteToCmdMap[byte])
{
  // There we  can check byte and throw exception for example
} // End of 'mthl::Request::Request' constructor

/* Doing command from request function */
mthl::Request::State mthl::Request::doCommand() const
{
  return fromCmdToFuncMap[command]();
} // End of 'mthl::Request::doCommand' function
