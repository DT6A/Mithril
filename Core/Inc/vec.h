/******************************
 * File name   : VEC.h
 * Purpose     : Mithrill project.
 *               Math vector
 * Author      : Tarasov Denis
 * Create date : 03.03.2020
 * Last change : 03.03.2020
 ******************************/

#ifndef __VEC_H_
#define __VEC_H_

#include <cmath>
#include <cstdlib>

/* Mithril namespace */
namespace mthl
{
  namespace math
  {
  /* vec class
   * Math vector
   */
  template<class Type = float>
    class vec
    {
    private :
      Type x, y, z; // Vector coordinates

    public :
      /* Vector constructor.
       * Arguments:
       *   Type a, b, c -- vector coordinates
       */
      vec(const Type &a, const Type &b, const Type &c) : x(a), y(b), z(c)
      {

      } // End of 'vec' constructor

      /* Vector constructor.
       * Arguments:
       *   Type a, b -- vector coordinates
       */
      vec(const Type &a, const Type &b) : x(a), y(b), z(b)
      {

      } // End of 'vec' constructor

      /* Vector constructor.
       * Arguments:
       *    Type a -- vector coordinates
       */
      explicit vec(const Type & a = 0) : x(a), y(a), z(a)
      {

      } // End of 'vec' constructor

      /* Vector copy constructor.
       * Arguments:
       *   vec V -- vector to copy
       */
      vec(const vec<Type> &V) : x(V.x), y(V.y), z(V.z)
      {

      } // End of 'vec' constructor

      /* operator[] overload function.
       * Arguments:
       *   int32_t i -- coordinate number
       * Returns:
       *   Vector coordinate with given number.
       */
      Type operator[](int32_t i) const
      {
        if (i < 0)
          i = 0;
        else if (i >= 3)
          i = 2;

        return *(&this->x + i);
      } // End of 'operator[]' function

      /* operator[] overload function.
       * Arguments:
       *   int32_t i -- coordinate number
       * Returns:
       *   Vector coordinate with given number.
       */
      Type & operator[](int32_t i)
      {
        return GetField(i);
      } // End of 'operator[]' function

      /* operator! overload function.
       * Arguments: None.
       *
       * Returns:
       *   Vector length.
       */
      Type operator!() const
      {
        return sqrt(x * x + y * y + z * z);
      } // End of 'operator!' function

      /* operator& overload function.
       * Arguments:
       *   vec V -- vector to multiply with
       *
       * Returns:
       *   Dot production of two vectors.
       */
      Type operator&(const vec<Type> & V) const
      {
        return (x * V.x + y * V.y + z * V.z);
      } // End of 'operator&' function

      /* operator% overload function.
       * Arguments:
       *  vec V - vector to multiply with
       *
       * Returns:
       *   Cross production of two vectors.
       */
      vec<Type> operator%(const vec<Type> & V) const
      {
        return vec<Type>(y * V.z - z * V.y, -(x * V.z - z * V.x), x * V.y - y * V.x);
      } // End of 'operator%' function

      /* operator* overload function.
       * Arguments:
       *   vec V -- vector to multiply with
       *
       * Returns:
       *   Component production of two vectors.
       */
      vec<Type> operator*(const vec<Type> &V) const
      {
        return vec<Type>(x * V.x, y * V.y, z * V.z);
      } // End of 'operator *' function

      /* operator* overload function.
       * Arguments:
       *   Type V -- number to multiply with
       *
       * Returns:
       *   Production of vector and number.
       */
      vec<Type> operator*(const Type &C) const
      {
        return vec<Type>(x * C, y * C, z * C);
      } // End of 'operator*' function

      /* operator+ overload function.
       * Arguments:
       *   vec V -- vector to add
       *
       * Returns:
       *   Sum of vectors
       */
      vec<Type> operator+(const vec<Type> & V) const
      {
        return vec<Type>(x + V.x, y + V.y, z + V.z);
      } // End of 'operator+' function

      /* operator/ overload function.
       * Arguments:
       *   Type C -- number to devide
       *
       * Returns:
       *   Divided vector
       */
      vec<Type> operator/(const Type &C) const
      {
        if (C == 0)
          return vec<Type>();
        return vec<Type>(x / C, y / C, z / C);
      } // End of 'operator/' function

      /* operator- overload function.
       * Arguments:
       *   vec V -- vector to substract
       *
       * Returns:
       *   Result of substraction
       */
      vec<Type> operator-(const vec<Type> &V) const
      {
        return vec<Type>(x - V.x, y - V.y, z - V.z);
      } // End of 'operator-' function

      /* operator- overload function.
       * Arguments: None.
       *
       * Returns:
       *   Inverse vector
       */
      vec<Type> operator-() const
      {
        return vec<Type>(-x, -y, -z);
      } // End of 'operator-' function

      /* operator*= overload function.
       * Arguments:
       *   Type C -- number to multiply with
       *
       * Returns:
       *   Result of multiplication
       */
      vec<Type> & operator*=(const Type &C)
      {
        x *= C;
        y *= C;
        z *= C;

        return *this;
      } // End of 'operator*=' function

      /* operator+ overload function.
       * Arguments:
       *   vec V -- vector to add
       *
       * Returns:
       *   Result of sum
       */
      vec<Type> & operator+=(const vec<Type> &V)
      {
        x += V.x;
        y += V.y;
        z += V.z;

        return *this;
      } // End of 'operator+=' function

      /* operator- overload function.
       * Arguments:
       *   vec V -- vector to substract
       *
       * Returns:
       *   Result of substraction
       */
      vec<Type> & operator-=(const vec<Type> &V)
      {
        x -= V.x;
        y -= V.y;
        z -= V.z;

        return *this;
      } // End of 'operator-=' function

      /* operator/= overload function.
       * Arguments:
       *   Type C -- number to devide on
       *
       * Returns:
       *   Result of division
       */
      vec<Type> & operator/=(const Type &C)
      {
        x /= C;
        y /= C;
        z /= C;

        return *this;
      } // End of 'operator/=' function

      /* Get vector field function.
       * Arguments:
       *   int32_t i -- coordinate number
       *
       * Returns:
       *   Vector coordinate with given number
       */
      Type & GetField(const int32_t i)
      {
        if (i <= 0)
          return x;
        else if (i == 1)
          return y;

        return z;
      } // End of 'GetField' function

      /* Normalize vector function.
       * Arguments: None.
       *
       * Returns:
       *   Normalized vector
       */
      vec<Type> Normalize() const
      {
        return *this / !(*this);
      } // End of 'Normalize' function

      /* Vector squared length function.
       * Arguments: None.
       *
       * Returns:
       *   Vector squared length.
       */
      Type LengthSquared() const
      {
        return x * x + y * y + z * z;
      } // End of 'LengthSquared' function

      /* Distance evaluation function.
       * Arguments:
       *   vec V -- vector to find distance with
       *
       * Returns:
       *   Distance between points.
       */
      Type Distance( const vec<Type> & V ) const
      {
        return !(*this - V);
      } // End of 'Distance' function

      /* Random vector generation function.
       * Arguments: None.
       *
       * Returns:
       *   Random normalized vector.
       */
      static vec<Type> RandomVector( void )
      {
        return vec<Type>(2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1,
            2.0 * rand() / RAND_MAX - 1);
      } // End of 'RandomVector' function

      /* Vector with zero fields creation function.
       * Arguments: None.
       *
       * Returns:
       *   Vector with zero coordinates.
       */
      static vec<Type> Zero( void )
      {
        return vec<Type>();
      } // End of 'Zero' function
    }; // End of 'vec' class
  }// end of 'math' namespace
} // end of 'mthl' namespace

#endif // __VEC_H_

/* END OF 'VEC.H' FILE */
