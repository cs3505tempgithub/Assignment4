#include <iostream>
#include <map>
#include <ctime>
#include "warehouse.h"
#include <fstream>
#include <sstream>
#include <string>
#include<vector>
#include <stdlib.h>  
#include <algorithm>

using namespace std;


int main(int argc, char *argv[])
{

  // Check for correct number of arguments
  if (argc !=2)
    {
      return 0;
    }

  // Get the file from command line and open it
  std::string filename = argv[1];
  std::ifstream in(argv[1]);
  std::string line;

  // Initialize a start date that will be changed later
  cs3505::date startdate("01/02/2013");

  // maps warehouse names to pointers to all the different warehouse objects
  map<std::string,cs3505::warehouse*>warehouses;

  // maps product id to the name of product
  map<std::string,std::string>foodnames;

  // maps most popular products by name to quantity
  map<std::string, int>leaderboard;

  // maps unstocked items by name to quantity
  map<std::string,int>unstocks;

  // maps food names to quantity to help with most popular items
  map<std::string,int>how_many_stocks;

  // maps food names to product shelflife
  map<std::string, int> foodlifes;

  // used to help with popular items
  vector<int> popular;
  
  // Read the file line by line
  while (std::getline(in,line))
    {
      // Temp variables
      std::string foodname;
      int shelflife;
      std::string uid;
      std::string word;
      
      istringstream iss(line); 
      iss >> word;
      
      /* Ugly but works well */

      /* Logic for when a food item must be parsed, based on the 
	 structure of the file, malformed input will break this */
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
        
	  /* Store the new items shelflife, name, and initialize it on the 
	     leaderboard for popular products */
	  foodlifes[uid]=shelflife;
	  foodnames[uid]=foodname;
          leaderboard[uid]=0;
	}

      /* Logic for when a warehouse must be parsed */
      if(word.compare("Warehouse")==0)
	{
	  iss >> word; 	iss >> word;

	  warehouses[word] = new cs3505::warehouse(foodlifes);
	}

      /* Begin the actual recieve and send logic, first initialize
	 all the warehouses to be on the correct start date */
      if(word.compare("Start")==0)
	{
	   iss >> word; 	iss >> word;
	   startdate.change_date(word);
	  
	   for (std::map<std::string, cs3505::warehouse*>::iterator i = warehouses.begin(); i != warehouses.end(); ++i)
	     {
	       i->second->todays_date=startdate;
	     }	   
	}
      
      /* Logic for recieving a shipment, storing the food in a warehouse, 
	 which holds a map of food ids to a deque structure of shipments */
      if (word.compare("Receive:") == 0)
	{
	  iss >> word;
	  std::string tempID = word;
	  iss >> word;
	  int temp_q = atoi(word.c_str());
	  iss >> word;
	  std::string warehouse_name = word;
	  warehouses[warehouse_name]->add_inventory(tempID, temp_q);
	
	}
      
      /* Logic for requested items, removing the items from the warehouse
         designated */
      if (word.compare("Request:") == 0)
	{
	  iss >> word;
	  std::string tempID = word;
	  iss >> word;
	  int temp_q = atoi(word.c_str());
	   leaderboard[tempID]+=temp_q;

	  iss >> word;
	  std::string warehouse_name = word;
	  
	  warehouses[warehouse_name]->remove_inventory(tempID, temp_q);

	 
	}

      /* Change the date in all the warehouses and remove expired food */
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
    
  // Outputting the report and a little bit more logic
  cout<<"Report by Linxi Li and Charles Clausen"<<endl<<endl;
  
  cout<<"Unstocked Products:"<<endl;

  /* Iterate the foodnames and warehouses and count the quantity,
     store the results of this into a map */
  for (std::map<std::string, string>::iterator i = foodnames.begin(); i != foodnames.end(); ++i)
    {
	     
      for (std::map<std::string, cs3505::warehouse*>::iterator k = warehouses.begin(); k != warehouses.end(); ++k)
	{
	  int quantity= k->second->get_quantity(i->first);
	  unstocks[i->first]+=quantity;
	 }	   
     }
  
  /* Iterate through the map we just made and print out any item that has 0 product
     in any warehouse */
   for (std::map<std::string, int>::iterator i = unstocks.begin(); i != unstocks.end(); ++i)
     {

       if(i->second==0)
	 {
	   cout<<i->first<<" "<<foodnames[i->first]<<endl;
	 }
     }	 
   
   cout<<endl;

   /* Loop through the foodnames and warehouse and count the stock of each */
   cout<<"Well-Stocked Products:"<<endl;
   for (std::map<std::string, string>::iterator i = foodnames.begin(); i != foodnames.end(); ++i)
     {
	     
       for (std::map<std::string, cs3505::warehouse*>::iterator k = warehouses.begin(); k != warehouses.end(); ++k)
	 {
	   if(k->second->get_quantity(i->first)>0)
	     {
	       how_many_stocks[i->first]+=1;
	     }
	 }	   
      }
  
   /* Iterate through the map we just made and print the top 3 */
   for (std::map<std::string, int>::iterator i =  how_many_stocks.begin(); i !=  how_many_stocks.end(); ++i)
     {
    
       if(i->second>=2)
	 {
	   cout<<i->first<<" "<<foodnames[i->first]<<endl;
	 }

     }	 
   
   cout<<endl;

   /* Iterate over the leaderboard map and store all items in a vector */
   cout<<"Most Popular Products:"<<endl;
   for (std::map<std::string, int>::iterator it = leaderboard.begin(); it != leaderboard.end(); it++)
     {
       popular.push_back(it->second);      
     }
   /* Sort the aforementioned vector */ 
   std::sort(popular.begin(), popular.end());
   std::reverse(popular.begin(), popular.end());
   /* Print em out */
   for (int i=0; i<popular.size() && i<3; i++)
     { 
       for (std::map<std::string, int>::iterator it = leaderboard.begin(); it != leaderboard.end(); it++)
	 {
	   if(it->second==popular[i])
	     {
	       cout<<it->first<< " "<<foodnames[it->first]<<endl;
	       leaderboard.erase(it);
	     }
	 }

     }
   cout <<endl;
   
   // End program
    return 0;
}


