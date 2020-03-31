/******************************
 * File name   : quater.h
 * Purpose     : Mithril project.
 *               Quaternion
 * Author      : Tarasov Denis
 * Create date : 31.03.2020
 * Last change : 31.03.2020
 ******************************/

#ifndef __QUATER_H_
#define __QUATER_H_

#include "vec.h"

 /* Mithril namespace */
namespace mthl
{
  namespace math
  {
    /* quater class
     * Quaternion
     */
    template<class Type = float>
    class quater
    {
    private:
      Type a; // Real number
      vec<Type> vector;

    public:
      /* Quaternion constructor.
       * Arguments:
       *   Type a, b, c, d -- quaternion coordinates
       */
      quater(const Type &a, const Type &b, const Type &c, const Type &d) : a(a), vector(b, c, d)
      {

      } // End of 'quater' constructor

      /* Quaternion constructor.
       * Arguments:
       *   Type a, b, c -- quaternion coordinates
       */
      quater(const Type &a, const Type &b, const Type &c) : a(a), vector(b, c)
      {

      } // End of 'quater' constructor

      /* Quaternion constructor.
       * Arguments:
       *   Type a, b -- quaternion coordinates
       */
      quater(const Type &a, const Type &b) : a(a), vector(b)
      {

      } // End of 'quater' constructor

      /* Quaternion constructor.
       * Arguments:
       *    Type a -- quaternion coordinates
       */
      explicit quater(const Type & a = 0) : a(a), vector(a)
      {

      } // End of 'quater' constructor

      /* Quaternion constructor.
       * Arguments:
       *   Type a -- real part
       *   vec<Type> v -- vector part
       */
      quater(const Type &a, const vec<Type> &b) : a(a), vector(b)
      {

      } // End of 'quater' constructor

      /* Quaternion copy constructor.
       * Arguments:
       *   vec v -- quaternion to copy
       */
      quater(const quater<Type> &q) : a(q.a), vector(q.vector)
      {

      } // End of 'quater' constructor

      /* operator[] overload function.
       * Arguments:
       *   int32_t i -- coordinate number
       * Returns:
       *   Quaternion coordinate with given number.
       */
      Type operator[](int32_t i) const
      {
        if (i < 0)
          i = 0;
        else if (i >= 4)
          i = 3;

        if (i == 0)
          return a;
        else
          return vector[i - 1];
      } // End of 'operator[]' function

      /* operator[] overload function.
       * Arguments:
       *   int32_t i -- coordinate number
       * Returns:
       *   Quaternion coordinate with given number.
       */
      Type & operator[](int32_t i)
      {
        if (i < 0)
          i = 0;
        else if (i >= 4)
          i = 3;

        if (i == 0)
          return a;
        else
          return vector[i - 1];
      } // End of 'operator[]' function

      /* operator! overload function.
       * Arguments: None.
       *
       * Returns:
       *   Quaternion length.
       */
      Type operator!() const
      {
        return sqrt(a * a + vector.lengthSquared());
      } // End of 'operator!' function


      /* operator* overload function.
       * Arguments:
       *   quater q -- quater to multiply with
       *
       * Returns:
       *   Production of two quaternions.
       */
      quater<Type> operator*(const quater<Type> & q) const
      {
        return quater(a * q.a - (vector & q.vector), q.vector * a + vector * q.a + vector % q.vector);
      } // End of 'operator*' function

      /* operator* overload function.
       * Arguments:
       *   Type c -- number to multiply with
       *
       * Returns:
       *   Production of quaternion and number.
       */
      quater<Type> operator*(const Type &c) const
      {
        return quater(a * c, vector * c);
      } // End of 'operator*' function

      /* operator+ overload function.
       * Arguments:
       *   quater q -- quaternion to add
       *
       * Returns:
       *   Sum of quaternions
       */
      quater<Type> operator+(const quater<Type> &q) const
      {
        return quater<Type>(a + q.a, vector + q.vector);
      } // End of 'operator+' function

      /* operator/ overload function.
       * Arguments:
       *   Type c -- number to devide
       *
       * Returns:
       *   Divided quaternion
       */
      quater<Type> operator/(const Type &c) const
      {
        if (c == 0)
          return quater<Type>();
        return quater<Type>(a / c, vector / c);
      } // End of 'operator/' function

      /* operator- overload function.
       * Arguments:
       *   quater q -- quaternion to substruct
       *
       * Returns:
       *   Sum of quaternions
       */
      quater<Type> operator-(const quater<Type> &q) const
      {
        return quater<Type>(a - q.a, vector - q.vector);
      } // End of 'operator-' function

      /* operator- overload function.
       * Arguments: None.
       *
       * Returns:
       *   Inverse quanternion
       */
      quater<Type> operator-() const
      {
        return quater<Type>(-a, -vector);
      } // End of 'operator-' function

      /* operator*= overload function.
       * Arguments:
       *   Type c -- number to multiply with
       *
       * Returns:
       *   Result of multiplication
       */
      quater<Type> & operator*=(const Type &c)
      {
        a *= c;
        vector *= c;

        return *this;
      } // End of 'operator*=' function

      /* operator+ overload function.
       * Arguments:
       *   quater q -- quaternion to add
       *
       * Returns:
       *   Result of sum
       */
      quater<Type> & operator+=(const quater<Type> &q)
      {
        a += q.a;
        vector += q.vector;

        return *this;
      } // End of 'operator+=' function

      /* operator*= overload function.
       * Arguments:
       *   quater q -- quaternion to multiply
       *
       * Returns:
       *   Result of multiplication
       */
      quater<Type> & operator*=(const quater<Type> &q)
      {
        *this = quater(a * q.a - (vector & q.vector), q.vector * a + vector * q.a + vector % q.vector);

        return *this;
      } // End of 'operator*=' function

      /* operator- overload function.
       * Arguments:
       *   quater q -- quaternion to substract
       *
       * Returns:
       *   Result of substraction
       */
      quater<Type> & operator-=(const quater<Type> &q)
      {
        a -= q.a;
        vector -= q.vector;

        return *this;
      } // End of 'operator-=' function

      /* operator/= overload function.
       * Arguments:
       *   Type c -- number to devide on
       *
       * Returns:
       *   Result of division
       */
      quater<Type> & operator/=(const Type &c)
      {
        a /= c;
        vector /= c;

        return *this;
      } // End of 'operator/=' function

      /* Normalize quaternion function.
       * Arguments: None.
       *
       * Returns:
       *   Normalized vector
       */
      quater<Type> normalize() const
      {
        return *this / !(*this);
      } // End of 'Normalize' function

      /* Quaternion squared length function.
       * Arguments: None.
       *
       * Returns:
       *   Quaternion squared length.
       */
      Type lengthSquared() const
      {
        return a * a + vector.lengthSquared();
      } // End of 'LengthSquared' function

      /* Quaternion conjugate element function.
       * Arguments: None.
       *
       * Returns:
       *   Conjugate element.
       */
      quater<Type> conjugate() const
      {
        return quater(a, -vector);
      } // End of 'conjugate' function


      /* Quaternion reciprocal element function.
       * Arguments: None.
       *
       * Returns:
       *   Reciprocal element.
       */
      quater<Type> reciprocal() const
      {
        if (a == 0 && vector.lengthSquared() == 0)
          return quater();
        return conjugate() / lengthSquared();
      } // End of 'reciprocal' function

       /* operator/ overload function.
       * Arguments:
       *   quater q -- quternion to devide
       *
       * Returns:
       *   Division result
       */
      quater<Type> operator/(const quater<Type> &q) const
      {
        return *this * q.reciprocal();
      } // End of 'operator/' function

      /* operator/= overload function.
       * Arguments:
       *   quater q -- quternion to devide
       *
       * Returns:
       *   Division result
       */
      quater<Type> & operator/=(const quater<Type> &q)
      {
        *this *= q.reciprocal();
        return *this;
      } // End of 'operator/=' function

      /* Sign function.
       * Arguments: None
       *
       * Returns:
       *   Quaternion sign
       */
      quater<Type> sign() const
      {
        return *this / !(*this);
      } // End of 'sign' function

      /* Argument function.
       * Arguments: None
       *
       * Returns:
       *   Quaternion argument
       */
      Type arg() const
      {
        return acosf(a / !(*this));
      } // End of 'sign' function

      /* operator& overload function.
       * Arguments:
       *   quater q -- quater to multiply with
       *
       * Returns:
       *   Dot production of two quaternions.
       */
      Type operator&(const quater<Type> & q) const
      {
        return ((conjugate() * q + q.conjugate() * (*this)) / 2).a;
      } // End of 'operator&' function

      /* operator% overload function.
       * Arguments:
       *   quater q -- quater to multiply with
       *
       * Returns:
       *   Cross production of two quaternions.
       */
      quater<Type> operator%(const quater<Type> & q) const
      {
        return ((*this) * q - q * (*this)) / 2;
      } // End of 'operator%' function


      /* operator%= overload function.
       * Arguments:
       *   quater q -- quater to multiply with
       *
       * Returns:
       *   Cross production of two quaternions.
       */
      quater<Type> & operator%=(const quater<Type> & q)
      {
        return *this = ((*this) * q - q * (*this)) / 2;
      } // End of 'operator%=' function
    }; // End of 'quater' class
  }// end of 'math' namespace
} // end of 'mthl' namespace

#endif // __QUATER_H_
