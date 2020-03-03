/******************************
 * File name   : UART_IO.h
 * Purpose     : Mithrill project.
 *               UART I/O interface
 * Author      : Tarasov Denis
 * Create date : 01.03.2020
 * Last change : 02.03.2020
 ******************************/

#ifndef __UART_IO_H_
#define __UART_IO_H_

#include "stm32f4xx_hal.h"

// TODO Error handling

/* Mithril namespace */
namespace mthl
{
  /* Functions declarations */

  inline void writeChar(UART_HandleTypeDef *huart, int32_t ch);
  inline void writeInt(UART_HandleTypeDef *huart, int32_t n,
      const char *end = nullptr);
  inline void writeFloat(UART_HandleTypeDef *huart, float n, const char *end = nullptr,
      int32_t precision = 4);
  inline void writeWord(UART_HandleTypeDef *huart, const char *s);


  /* Functions definitions */

  /* Write single character with UART
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *   int32_t ch -- character to write
   *
   * Returns:
   *   None.
   */
  inline void writeChar(UART_HandleTypeDef *huart, int32_t ch)
  {
    // Send byte with UART
    HAL_UART_Transmit(huart, (uint8_t *)&ch, 1, 1000);
  } // End of 'writeChar' function

  /* Write integer number with UART
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *   int32_t n -- number to write
   *   const char *end -- line to append (default = nullptr)
   *
   * Returns:
   *   None.
   */
  inline void writeInt(UART_HandleTypeDef *huart, int32_t n, const char *end)
  {
    // Process negative number
    if (n < 0)
    {
      writeChar(huart, '-');
      n = -n;
    }

    // Get all digits
    int32_t pos = 0, buf[19];
    do
    {
      buf[pos++] = '0' + n % 10;
      n /= 10;
    } while (n);

    // Write all digits
    do
     {
      writeChar(huart, buf[--pos]);
     } while (pos);

    // Write postfix
    if (end != nullptr)
      writeWord(huart, end);
  } // End of 'writeInt' function

  /* Write float number with UART
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *   float n -- number to write
   *   const char *end -- line to append (default = nullptr)
   *   int32_t precision -- number of digits atfer the dot (default = 4)
   *
   * Returns:
   *   None.
   */
  inline void writeFloat(UART_HandleTypeDef *huart, float n, const char *end, int32_t precision)
  {
    // Process negative number
    if (n < 0)
    {
      writeChar(huart, '-');
      n = -n;
    }
    // Write digits before dot
    writeInt(huart, (int32_t)n);
    n -= (int32_t)n;
    writeChar(huart, '.');


    // Write digits after dot
    for (int32_t i = 0; i < precision; ++i)
    {
      n *= 10;
      writeChar(huart, '0' + (int32_t)n);
      n -= (int32_t)n;
    }

    // Write postfix
    if (end != nullptr)
      writeWord(huart, end);
  } // End of 'writeFloat' function

  /* Write c-style string with UART
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *   const char *s -- string to write
   *
   * Returns:
   *   None.
   */
  inline void writeWord(UART_HandleTypeDef *huart, const char *s)
  {
    // Write each character
    while (*s)
      writeChar(huart, *s++);
  } // End of 'writeWord' function

  // TODO INPUT

} // end of 'mthl' namespace

#endif // __UART_IO_H_
