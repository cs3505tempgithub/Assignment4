#include <iostream>
#include <map>
#include <ctime>
#include "warehouse.h"
#include <fstream>
#include <sstream>
#include <string>
#include<list>
#include <stdlib.h>  
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

  
  map<std::string,cs3505::warehouse*>warehouses;
  map<std::string,std::string>foodnames;//uid goes first, then name
  map<std::string,int>leaderboard;

  std::list<std::string>unstocks;
  map<std::string,int>how_many_stocks;
  map<std::string, int> foodlifes;
  


  while (std::getline(in,line))

    {
      std::string foodname;
      int shelflife;
      std::string uid;
      std::string word;
      istringstream iss(line);
 
      iss >> word;
        /* do stuff with word */
      if(word.compare("FoodItem")==0)
	{
	  iss >> word; 	iss >> word; 	iss >> word; 	iss >> word;
	  uid=word;

	  iss >> word; 	iss >> word; 	iss >> word; 
	  shelflife=atoi(word.c_str());        
	  iss >> word; 
	
	  while(iss>>word)
	    {
	      foodname+=word+=" ";
	    }
        
	  foodlifes[uid]=shelflife;
	  foodnames[uid]=foodname;
          leaderboard[uid]=0;
	}
      if(word.compare("Warehouse")==0)
	{
	  iss >> word; 	iss >> word;

	  warehouses[word] = new cs3505::warehouse(foodlifes);
	}

      if(word.compare("Start")==0)
	{
	   iss >> word; 	iss >> word;
	   startdate.change_date(word);
	  
	   for (std::map<std::string, cs3505::warehouse*>::iterator i = warehouses.begin(); i != warehouses.end(); ++i)
	     {
	       i->second->todays_date=startdate;
	     }	   
	}
      
      if (word.compare("Recieve:") == 0)
	{
	  iss >> word;
	  std::string tempID = word;
	  iss >> word;
	  int temp_q = atoi(word.c_str());
	  iss >> word;
	  std::string warehouse_name = word;
	  warehouses[warehouse_name]->add_inventory(tempID, temp_q);
	}
      
      if (word.compare("Request:") == 0)
	{
	  iss >> word;
	  std::string tempID = word;
	  iss >> word;
	  int temp_q = atoi(word.c_str());
	  iss >> word;
	  std::string warehouse_name = word;
	  warehouses[warehouse_name]->remove_inventory(tempID, temp_q);
	  leaderboard[uid]+=temp_q;
	}

      if(word.compare("Next") == 0)
	{
	  startdate.goto_tomorrow();
	   for (std::map<std::string, cs3505::warehouse*>::iterator i = warehouses.begin(); i != warehouses.end(); ++i)
	     {
	       i->second->todays_date.goto_tomorrow();
	       i->second->remove_expired_food();
	     }	   
	}

    
    }
    
  cout<<"report by Linxi and Charlie"<<endl;
    return 0;
    }


