/******************************
 * File name   : Request.h
 * Purpose     : Mithrill project.
 *               Controller module.
 *               Request class declaration.
 * Author      : Filippov Denis
 * Create date : 09.03.2020
 * Last change : 22.03.2020
 ******************************/


#ifndef __REQUEST_H_
#define __REQUEST_H_

#include <string>
#include <queue>
#include <map>
#include <functional>

#include "stm32f4xx.h"

/* Mithril namespace */
namespace mthl
{
  /* Request class declaration.
   * Requests can be given by application, button on T-shirt etc.
   */
  class Request
  {
  public:
    /* State after doing command from tequest enum class declaration */
    enum class State : uint8_t
    {
      EXIT, // got request for shutting down of STM
      OK    // got request
    }; // End of 'State' enun class

    /* Request from byte constructor.
     *
     * Arguments
     *   uint8_t byte -- byte of command.
     */
    Request(uint8_t byte);

    /* Doing command from request function.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   State of programm.
     */
    State doCommand() const;

  private:
    /* Request command enum class declaration */
    enum class Command : uint8_t
    {
      POWER_ON_LED,
      POWER_OFF_LED
    }; // End of 'Command' enum class

    Command command; // command of this request

    /* Map who mathes byte and it command */
    static std::map<uint8_t, Command> fromByteToCmdMap;
    /* Map who matches commands and their function */
    static std::map<Command, std::function<State(void)>> fromCmdToFuncMap;
  }; // End of 'Request' class
} // end of 'mthl' namespace

#endif /* __REQUEST_H_ */
