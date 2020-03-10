/******************************
 * File name   : Request.cpp
 * Purpose     : Mithrill project.
 *               Controller module
 *               Request class implementation
 * Author      : Filippov Denis
 * Create date : 10.03.2020
 * Last change : 10.03.2020
 ******************************/

#include "Controller/Request/Request.h"

/* Map who mathes byte and it command */
std::map<uint8_t, mthl::Request::Command> mthl::Request::fromByteToCmdMap =
{
  {1, Command::POWER_ON_LED},
  {2, Command::POWER_OFF_LED}
};

/* Map who matches commands and their function */
std::map<mthl::Request::Command, std::function<void(void)>> mthl::Request::fromCmdToFuncMap =
{
  {Command::POWER_ON_LED,
   []()
   {
     HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
   }
  },

  {Command::POWER_OFF_LED,
   []()
   {
     HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
   }
  }
};

/* Request from byte constructor */
mthl::Request::Request(uint8_t byte)
  : command(fromByteToCmdMap[byte])
{
} // End of 'mthl::Request::Request' constructor

/* Get requests from application function */
mthl::Request::State mthl::Request::getRequests(std::queue<Request> &reqQueue)
{
  /*
  uint8_t byte;
  while ((byte = readByte(&BLUETOOTH)) != std::null_optional && byte != exitByte) //
  {
    reqQueue.push(Request(byte));
  }
  */
  return State::OK;
} // End of 'mthl::Request::getRequests' function

/* Doing command from request function */
void mthl::Request::doCommand() const
{
  fromCmdToFuncMap[command]();
} // End of 'mthl::Request::doCommand' function
