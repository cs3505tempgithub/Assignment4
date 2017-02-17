/* 
   This header file was created in collaboration by Linxi Li and Charles Clausen.
   This is intended for use in Assignment04 in University of Utah
   CS3505 Spring 2017.
*/

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include "food.h"
#include <map>
#include <deque>

namespace cs3505
{
  class warehouse
  {
  public:
    warehouse(std::map<std::string, int> properties);
    void add_inventory(std::string uid, int quantity);
    bool remove_inventory(std::string uid, int quantity);
    int get_quantity(std::string uid);
    void remove_expired_food();    
    date todays_date;
    std::map<std::string, int> food_life;
    std::map<std::string, std::deque<food> > inventory;
  };
}


#endif
