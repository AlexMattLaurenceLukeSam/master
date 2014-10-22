#include <ctime>
#include <iostream>

#include "Conference.hpp"
#include "Date.hpp"

/*int main() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int foo = now->tm_year + 1900;
    std::cout << (foo) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
}*/

void Conference::checkDeadlines()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    Date today(now->tm_year + 1900,
               now->tm_mon + 1,
               now->tm_mday);
    isBeforePaperDeadline = paperDeadline.compare(today);
    isBeforeSoftReviewDeadline = reviewDeadlineSoft.compare(today);
    isBeforeHardReviewDeadline = reviewDeadlineHard.compare(today);
    isBeforeDiscussDeadline = discussDeadline.compare(today);

}
