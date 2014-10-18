#ifndef DATE_H
#define DATE_H

struct Date {
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
bool compare(Date);

int day{0};
int month{0};
int year{0};
};
#endif
