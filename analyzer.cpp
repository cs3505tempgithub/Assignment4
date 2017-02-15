#include <iostream>
#include <map>
#include <ctime>
#include "warehouse.h"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp> 

#include "food.h"
using namespace std;
int main()
{
  std::ifstream in("data1.txt");
  std::string line;

  cs3505::date startdate("01/02/2013");
  //main
  //foodlist<uids, name, shelf-life>;
  //warehouse<names>
  //data
  //warehouse <keys-uid, foodobjects>
  //foodobjects<expdate, quantity>
  //

  cs3505::food fooder(startdate.get_today_date(),1,10);
  cout<<"food stocked in"<<startdate.get_today_date()<<"expires at"<< fooder.exp_date.get_today_date()<<"with a quantity of"<<fooder.quantity<<endl;
  cout<<startdate.get_today_date()<<endl;
  startdate.goto_tomorrow();
  cout<<startdate.get_today_date()<<endl;
  
  
  map<int, int> foodstuff;
  foodstuff[111] = 1;
  foodstuff[123] = 2;
  cs3505::warehouse w (foodstuff, startdate);
  w.add_inventory(123, 50);
  w.add_inventory(123, 1);
  w.add_inventory(111, 3);

  cout<<w.get_quantity(123)<<"quantity of 123"<<endl;
  cout << w.inventory[123].size() << endl;
  w.todays_date.goto_tomorrow();
  cout << "Before expiration: " << w.inventory[111].size() << endl;
  w.remove_expired_food();
  cout << "After expiration: " << w.inventory[111].size() << endl;

  w.todays_date.goto_tomorrow();
  cout << "Before expiration: " << w.inventory[111].size() << endl;
  w.remove_expired_food();
  cout << "After expiration: " << w.inventory[111].size() << endl;  
w.todays_date.goto_tomorrow();
  cout << "Before expiration: 123 " << w.inventory[123].size() << endl;
  w.remove_expired_food();
  cout << "After expiration: " << w.inventory[123].size() << endl;

    w.remove_inventory(123, 45);
  cout << w.inventory[123].size() << endl;
  w.remove_inventory(123, 6);
  cout << w.inventory[123].size() << endl;
 w.remove_inventory(123, 6);
  cout << w.inventory[123].size() << endl;
    cout<<w.get_quantity(123)<<"quantity of 123"<<endl;
    cout<<w.get_quantity(000)<<"quantity of 000"<<endl;

  while (std::getline(in,line))

    {
      std::cout<<"\n"<<line<<"\n";
    }

  return 0;
}
