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

void ConferenceManager::checkDeadlines(const Conference& in)
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    Date today(now->tm_year + 1900,
               now->tm_mon + 1,
               now->tm_mday);
    in.isBeforePaperDeadline = in.paperDeadline.compare(today);
    in.isBeforeSoftReviewDeadline = in.reviewDeadlineSoft.compare(today);
    in.isBeforeHardReviewDeadline = in.reviewDeadlineHard.compare(today);
    in.isBeforeDiscussDeadline = in.discussDeadline.compare(today);

}

void ConferenceManager::checkAllDeadlines()
{
    for (unsigned i=0; i < conferences.size(); i++) {
    checkDeadlines(conferences[i]);
  }
}
