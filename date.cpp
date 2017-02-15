#include<string>
#include "date.h"
#include <stdlib.h>  
#include <sstream>

namespace cs3505
{
  date::date()
  {
    this->day=1;
    this->month=1;
    this->year=1990;
  }

  date::date(std::string _date)
  {
    std::string _month=_date.substr(0,2);
    std::string _day=_date.substr(3,2);
    std::string _year=_date.substr(6,4);
    this->day=atoi(_day.c_str());
    this->month=atoi(_month.c_str());
    this->year=atoi(_year.c_str());
  }



  std::string date::get_today_date()
 {
  std::string day;
  std::stringstream out_day;
  out_day << this->day;
  day = out_day.str();
  if(day.length()==1){day="0"+day;}

  std::string month;
  std::stringstream out_month;
  out_month << this->month;

  month = out_month.str();
  if(month.length()==1){month="0"+month;}
  std::string year;
  std::stringstream out_year;
  out_year << this->year;
  year = out_year.str();
  return month+"/"+day+"/"+year;
 }
  void date::goto_tomorrow()

  {
    if(this->day<28)//general case
      {
	this->day++;
	return;
      }
    if(this->day==28&&this->month!=2)//a normal 28th not in feburary
      {
	this->day=29;

	return;
      }
    if(this->day==28&&this->month==2&&this->year%400==0)//a feburary 28th bit year ie 2000
      {
	this->day=29;
	return;
      }
    if(this->day==28&&this->month==2&&this->year%4==0&&this->year%100 !=0)//another february 28th big year ie 1996
      {

	this->day=29;
	return;
      } 
     if(this->day==28&&this->month==2&&this->year%4!=0)//1905
      {
	this->day=1;
	this->month=3;	
	return;
      }
    if(this->day==28&&this->month==2&&this->year%100==0&&this->year%400!=0)//1900
      {
	this->day=1;
	this->month=3;	
	return;
      }
    if(this->day==29&&this->month==2)//a feb 29

      {	
	this->day=1;
	this->month=3;
	return;
      }
    if(this->day==29&&this->month!=2)//a normal 29th
      {
	this->day=30;
	return;
      }
    if(this->day==30)
      {
	if(this->month==1||this->month==3||this->month==5||this->month==7||this->month==8||this->month==10||this->month==12)
	  {
	    this->day=31;
	    return;
	  }
	else
	  {
	    this->day=1;
	    this->month++;
	    return;
	  }
      }
    if(this->day==31&&this->month!=12)//a normal 31st
      {
	this->day=1;
	this->month++;
	return;
      }
    if(this->day==31&&this->month==12)//end of year
      {
	this->day=1;
	this->month=1;
	this->year++;
	return;
      }
      

  }
  void date::change_date(std::string _date)
  {
   std::string _month=_date.substr(0,2);
    std::string _day=_date.substr(3,2);
    std::string _year=_date.substr(6,4);
    this->day=atoi(_day.c_str());
    this->month=atoi(_month.c_str());
    this->year=atoi(_year.c_str());
  }

}

