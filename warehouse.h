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
    warehouse(std::map<int, int> properties, date d);
    void add_inventory(int uid, int quantity);
    bool remove_inventory(int uid, int quantity);
    int get_quantity(int uid);
    void remove_expired_food();    
    date todays_date;
    std::map<int, int> food_life;
    std::map<int, std::deque<food> > inventory;
  };
}


#endif
