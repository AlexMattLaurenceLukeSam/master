#ifndef DATE_H
#define DATE_H

#include <sstream>

class Date {
    
public:
    Date() { }
    Date(int iday,
         int imonth,
         int iyear):
         day(iday),
         month(imonth),
         year(iyear)
             { }
    
    Date(const Date& in)
    {
        day = in.day;
        month = in.month;
        year = in.year;
    }
    
// NOTE: changed get functions, new below
    void setDay(int iday) {day = iday;}
    void setMonth(int imonth) {month = imonth;}
    void setYear(int iyear) {year = iyear;}
    int getDay() {return day;}
    int getMonth() {return month;}
    int getYear() {return year;}
    
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

  std::string convertToString()
  {
    std::stringstream temp;
    temp << day << "/" << month << "/" << year; 
    return(temp.str());
  } 
    
private:
    int day{0};
    int month{0};
    int year{0};
    
};

inline QDataStream& operator<<(QDataStream& out, const Date* d)
{
    out << d->day;
    out << d->month;
    out << d->year;
    return out;
}

inline QDataStream& operator<<(QDataStream& out, const Date& d)
{
    out << d.day;
    out << d.month;
    out << d.year;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Date* d)
{
    in >> d->day;
    in >> d->month;
    in >> d->year;
    return in;
}

inline QDataStream& operator>>(QDataStream& in, const Date& d)
{
    in >> d.day;
    in >> d.month;
    in >> d.year;
    return in;
}

#endif
