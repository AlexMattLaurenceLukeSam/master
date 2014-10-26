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
    
    const bool oldisBeforePaperDeadline = isBeforePaperDeadline;
    const bool oldisBeforeAllocationDate = isBeforeAllocationDate;
    const bool oldisBeforeSoftReviewDeadline = isBeforeSoftReviewDeadline;
    const bool oldisBeforeHardReviewDeadline = isBeforeHardReviewDeadline;
    const bool oldisBeforeDiscussDeadline = isBeforeDiscussDeadline;
    
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
    if(!isBeforeAllocationDate) {
        //run allocation
        //algo is responsible for updating the database with the reviwere paper allocations
    }
    in->isBeforeSoftReviewDeadline = in->reviewDeadlineSoft.compare(today);
    in->isBeforeHardReviewDeadline = in->reviewDeadlineHard.compare(today);
    in->isBeforeDiscussDeadline = in->discussDeadline.compare(today);
    
    if(!(oldisBeforePaperDeadline == isBeforePaperDeadline && //ie something changed
    oldisBeforeAllocationDate == isBeforeAllocationDate &&
    oldisBeforeSoftReviewDeadline == isBeforeSoftReviewDeadline &&
    oldisBeforeHardReviewDeadline == isBeforeHardReviewDeadline &&
    oldisBeforeDiscussDeadline == isBeforeDiscussDeadline))
    {
        updateConference(*in); // update conference in database if something changed
    }

}

void ConferenceManager::checkAllDeadlines()
{
    std::vector<Conference> in = getAllConferences(); //gets all conferences in database
    
    for (unsigned i=0; i < in.size(); i++) {
      checkDeadlines(&in[i])
  }
}

std:vector<Conferences> ConferenceManager::getAllActiveConferences()
{
    std::vector<int> activeConfs = db->activeConfIDs();
    
    std::vector<Conference> conferences;
    
    for(int i = 0; i < activeConfs.size(); ++i)
    {
        conferences.push_back(db->fetchConference(activeConfs[i]));
    }
    
    return conferences;
}

std:vector<Conferences> ConferenceManager::getAllConferences()
{
    std::vector<int> allConfs = db->allConfIDs();
    
    std::vector<Conference> conferences;
    
    for(int i = 0; i < activeConfs.size(); ++i)
    {
        conferences.push_back(db->fetchConference(allConfs[i]));
    }
    
    return conferences;
}
