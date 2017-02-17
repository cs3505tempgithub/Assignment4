/* 
   This header file was created in collaboration by Linxi Li and Charles Clausen.
   This is intended for use in Assignment04 in University of Utah
   CS3505 Spring 2017.
*/

#ifndef DATE_H
#define DATE_H

#include<string>
namespace cs3505
{
  class date
  {
  
  public:
    date (std::string _date);
    date();
    void goto_tomorrow();
    std::string get_today_date();
    void change_date(std::string _date);
  private:
    int day;
    int month;
    int year;
  };
}

#endif
