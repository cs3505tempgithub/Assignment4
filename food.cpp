/* 
   This class file was created in collaboration by Linxi Li and Charles Clausen.
   This is intended for use in Assignment04 in University of Utah
   CS3505 Spring 2017.
*/

#include<string>
#include "food.h"


/*
  This class represents the product that will be stored in the warehouse class.
  It takes the effective date, the shelf life, and the quantity as parameters.
  It holds the information for its expiration date for use in warehouse class.
 */

namespace cs3505 
{
  food::food(std::string today_date, int shelflife, int quantity)
  { cs3505::date result(today_date);
    this->exp_date = result;
    this->exp_date = get_expdate(today_date, shelflife);
    this->quantity = quantity;
  }


  /*
    This function is used in the constructor to calculate this foods expiration
    date for use in the warehouse class.  It takes the effective date and 
    the shelflife of the item as parameters.
   */
  cs3505::date food::get_expdate(std::string today_date, int shelflife)
  {
    int times = shelflife;
    cs3505::date result(today_date);
    while(times>0)
      {
	result.goto_tomorrow();
	times--;
      }
    return result;
  }
}

