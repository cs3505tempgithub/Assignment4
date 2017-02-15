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
