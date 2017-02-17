/* 
   This header file was created in collaboration by Linxi Li and Charles Clausen.
   This is intended for use in Assignment04 in University of Utah
   CS3505 Spring 2017.
*/

#ifndef FOOD_H
#define FOOD_H

#include<string>
#include "date.h"
namespace cs3505
{
  class food
  {
  public:    
    date exp_date;    
    int quantity;
    food(std::string today_date, int shelflife, int quantity);
  private:
    date get_expdate(std::string today_date, int shelflife);
  };

}

#endif
