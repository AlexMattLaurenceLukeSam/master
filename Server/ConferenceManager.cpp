#include <ctime>
#include <iostream>

#include "ConferenceManager.hpp"
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

void ConferenceManager::checkDeadlines(Conference* in)
{
    if (in == nullptr) {
        return;
    }
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    Date today(now->tm_year + 1900,
               now->tm_mon + 1,
               now->tm_mday);
    Date yesterday(now->tm_year + 1900,
               now->tm_mon + 1,
               now->tm_mday - 1);
    in->isBeforePaperDeadline = in->paperDeadline.compare(today);
    in->isBeforeAllocationDate = in->allocationDate.compare(yesterday);
    //for deadlines, you can still submit papers on the day of the paper deadline
    //for dates, it occurs on the day, so if it is the day of the allocation date or after, allocation is done
    //this means that it occurs one day earlier, this is why we use yesterday
    in->isBeforeSoftReviewDeadline = in->reviewDeadlineSoft.compare(today);
    
    if(!isBeforeAllocationDate) {
        //run allocation
    }
    
    in->isBeforeHardReviewDeadline = in->reviewDeadlineHard.compare(today);
    in->isBeforeDiscussDeadline = in->discussDeadline.compare(today);

}

void ConferenceManager::checkAllDeadlines()
{
    for (unsigned i=0; i < conferences.size(); i++) {
    checkDeadlines(conferences[i]);
  }
}
