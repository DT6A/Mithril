/******************************
 * File name   : Function.h
 * Purpose     : Mithril project.
 *               Mithril functionality module.
 *               Base function class declaration.
 * Author      : Filippov Denis
 * Create date : 04.04.2020
 * Last change : 04.04.2020
 ******************************/

#ifndef __FUNCTIONALITY_H_
#define __FUNCTIONALITY_H_

/* Mithril namespace */
namespace mthl
{
  /* Functionality base class declaration */
  class BaseFunc
  {
  public:
    /* Doing funtion of Mithril function.
     *
     * Arguments:
     *   None.
     *
     * Returns:
     *   None.
     */
    virtual void doFunction()
    {
      /// std::logic_error("Functionality not emplementated");
    }
  }; // End of 'BaseFunc' declaration
} // end of 'mthl' namespace

#endif /* __FUNCTIONALITY_H_ */
