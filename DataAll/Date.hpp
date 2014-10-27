#ifndef DATE_H
#define DATE_H

#include <sstream>
#include <QDataStream>

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

  inline QDataStream& operator<<(QDataStream& out, Date* d)
{
    out << d->getDay();
    out << d->getMonth();
    out << d->getYear();
    return out;
}

inline QDataStream& operator<<(QDataStream& out, Date& d)
{
    out << d.getDay();
    out << d.getMonth();
    out << d.getYear();
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Date* d)
{
    int tmp;
    in >> tmp;
    d->setDay(tmp);
    in >> tmp;
    d->setMonth(tmp);
    in >> tmp;
    d->setYear(tmp);
    return in;
}

inline QDataStream& operator>>(QDataStream& in, Date& d)
{
    int tmp;
    in >> tmp;
    d.setDay(tmp);
    in >> tmp;
    d.setMonth(tmp);
    in >> tmp;
    d.setYear(tmp);
    return in;
}

#endif
