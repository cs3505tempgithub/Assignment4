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
  map<std::string,std::string>foodnames;//uid goes first, then name\
  map<std::string,int>request_leaderboard;

  std::list<std::string>unstocks;
  map<std::string,int>how_many_stocks;
  map<std::string, int> foodlifes;
  


  while (std::getline(in,line))

    {std::string foodname;
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
      
      
    
    }
    return 0;
    }


