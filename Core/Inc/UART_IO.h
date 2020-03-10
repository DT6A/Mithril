/******************************
 * File name   : UART_IO.h
 * Purpose     : Mithrill project.
 *               UART I/O interface
 * Author      : Tarasov Denis
 * Create date : 01.03.2020
 * Last change : 10.03.2020
 ******************************/

#ifndef __UART_IO_H_
#define __UART_IO_H_

#include "stm32f4xx_hal.h"

// TODO Error handling

/* Mithril namespace */
namespace mthl
{
  static uint8_t UART_buf[19] = {0}, UART_rev[19] = {0}; // Buffers for writing

  /* Functions declarations */

  /*** Writing ***/
  inline void writeChar(UART_HandleTypeDef *huart, int32_t ch);
  inline void writeInt(UART_HandleTypeDef *huart, int32_t n,
      const char *end = nullptr);
  inline void writeFloat(UART_HandleTypeDef *huart, float n, const char *end = nullptr,
      int32_t precision = 4);
  inline void writeBytes(UART_HandleTypeDef *huart, const uint8_t *s, uint32_t len);
  inline void writeWord(UART_HandleTypeDef *huart, const char *s);

  /*** Reading ***/
  inline uint8_t readByte(UART_HandleTypeDef *huart);

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
    int32_t pos = 0;
    // Process negative number
    if (n < 0)
    {
      writeChar(huart, '-');
      n = -n;
    }

    // Get all digits
    do
    {
      buf[pos++] = '0' + n % 10;
      n /= 10;
    } while (n);

    // Flip digits
    for (int32_t i = 0; i < pos; ++i)
      rev[i] = buf[pos - i - 1];
    // Write all digits

    writeBytes(huart, rev, pos);

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

    // Write digits after dot to buffer
    for (int32_t i = 0; i < precision; ++i)
    {
      n *= 10;
      buf[i] = '0' + (int32_t)n;
      n -= (int32_t)n;
    }

    // Write buffer
    writeBytes(huart, buf, precision);

    // Write postfix
    if (end != nullptr)
      writeWord(huart, end);
  } // End of 'writeFloat' function

  /* Write bytes string with UART
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *   const uint8_t *s -- buffer to write
   *
   * Returns:
   *   None.
   */
  inline void writeBytes(UART_HandleTypeDef *huart, const uint8_t *s, uint32_t len)
  {
    // Write each buffer
    HAL_UART_Transmit(huart, (uint8_t *)s, len, 1000);
  } // End of 'writeBytes' function

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
    uint32_t len = 0;
    // Count length
    while (*s)
      len++, s++;
    // Write string
    writeBytes(huart, (uint8_t *)(s - len), len);
  } // End of 'writeWord' function

  /* Read one byte with UART
   * Waits until any byte is given
   *
   * Arguments:
   *   UART_HandleTypeDef *huart -- UART handler
   *
   * Returns:
   *   Byte which was read
   */
  inline uint8_t readByte(UART_HandleTypeDef *huart)
  {
    uint8_t byte = 0;

    while (HAL_UART_Receive(huart, &byte, 1, 1000) != HAL_OK)
      ;
    return byte;
  } // End of 'readByte' function

} // end of 'mthl' namespace

#endif // __UART_IO_H_
