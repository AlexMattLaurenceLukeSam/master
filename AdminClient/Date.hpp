#ifndef DATE_H
#define DATE_H
struct Date {
  Date() { }
  Date(int iday,
    int imonth,
    int iyear):
    day(iday),
    month(imonth),
    year(iyear)
    { }

  Date(const Date& in) {
  day = in.day;
  month = in.month;
  year = in.year;}
  bool compare(const Date& idate) //returns true if idate is before or on the same day as this
  {
    if(idate.year != year) {
      return idate.year < year;
    } else {
      if(idate.month != month) {
        return idate.month < month;
        } else {
        if(idate.day != day) {
      return idate.day < day;
          }
        }  
    }
    return true;
  }

int day{0};
int month{0};
int year{0};
};
#endif
