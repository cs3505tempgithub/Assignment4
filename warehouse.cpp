#include <map>
#include <queue>
#include <string>
#include "warehouse.h"


/* This class takes a map of food IDs to shelf life and today's effective date
   when created.  It is used to keep track of inventory at various locations
   and there should be one of these classes per warehouse.  It adds and deletes
   inventory, removes expired food, and can return quantity of desired item.
   It holds the map passed in called food_life and a map of string food ID
   to a deque of those item.  The deque holds each shipment of inventory
   seperately.
 */

namespace cs3505
{
 warehouse::warehouse(std::map<std::string, int> properties)
  {
    this->food_life = properties;
  }

   
  /*
    This method adds inventory of an item, taking the string ID of the food
    and the quantity.  It adds it to an existing deque or creates a new one
   */
  void warehouse::add_inventory(std::string uid, int quantity)
  {
    // Count returns 0 or 1 when searching for a key
    // If it doesn't exist, make a new queue of that type of food
    if (inventory.count(uid) == 0)
      {
	std::deque<food> new_element;
	inventory[uid] = new_element;
	food new_food (todays_date.get_today_date(), this->food_life[uid], quantity);
	inventory[uid].push_back(new_food);
      }
    else
      {
	food new_food (todays_date.get_today_date(), this->food_life[uid], quantity);
	inventory[uid].push_back(new_food);
      }
  }


  /*
    This method removes inventory from the warehouse if it exists.  It takes
    the food ID and the requested ammount as paramters.  It searches the 
    warehouses map of inventory and removes the requested amount from the
    deque.
   */
  bool warehouse::remove_inventory(std::string uid, int requested)
  {
    // Not in inventory
    if (inventory.count(uid) == 0)
      {
	return false;
      }
    // Temp
    int remaining_request = requested;
    
    // Loop while the requested amount isn't met or the deque isn't empty
    while (remaining_request > 0 || inventory[uid].size() != 0)
      {
	inventory[uid].front().quantity -= remaining_request;
	if (inventory[uid].front().quantity <= 0)
	  {
	    remaining_request = inventory[uid].front().quantity * -1;
	    if (inventory[uid].size() > 0)
	      inventory[uid].pop_front();
	    else
	      return false;
	  }
	else
	  {
	    remaining_request = 0;
	    return true;
	  }	
      } 
    return true;
  }


  /*
    This method traverses the inventory map and the inventory in each deque
    and checks tody's effective date with the expiration date stored in food
    objects.  If it is that day, pop that shipment off the deque.
   */
  void warehouse::remove_expired_food()
  {
    for(std::map<std::string, std::deque<food> >::iterator it=inventory.begin(); it!=inventory.end(); it++)
      {
	// Compare returns 0 if strings are identical and date is a string
	while (it->second.front().exp_date.get_today_date().compare(this->todays_date.get_today_date()) == 0)
	  {
	    if (it->second.size() > 0)
	      it->second.pop_front();
	  }
      }
  }


  /*
    This method takes the food ID as a paramter and traverses the inventory map.
    It counts the inventory amount of the desired food and returns the count.
   */
  int warehouse::get_quantity(std::string uid)
  {
    int result=0;
    if (inventory.count(uid) == 0)
      {
	return 0;
      }
    for (std::deque<food>::iterator it=inventory[uid].begin(); it!=inventory[uid].end(); it++)
      {
	result += it->quantity;
      }
    return result;
  }
}
