#include <ctime>
#include <iostream>

#include "ConferenceManager.hpp"
#include "../DataAll/Date.hpp"

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
    
    const bool oldisBeforePaperDeadline = in->isBeforePaperDeadline;
    const bool oldisBeforeAllocationDate = in->isBeforeAllocationDate;
    const bool oldisBeforeSoftReviewDeadline = in->isBeforeSoftReviewDeadline;
    const bool oldisBeforeHardReviewDeadline = in->isBeforeHardReviewDeadline;
    const bool oldisBeforeDiscussDeadline = in->isBeforeDiscussDeadline;
    
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
    if(!in->isBeforeAllocationDate) {
        //run allocation
        //algo is responsible for updating the database with the reviwere paper allocations
    }
    in->isBeforeSoftReviewDeadline = in->reviewDeadlineSoft.compare(today);
    in->isBeforeHardReviewDeadline = in->reviewDeadlineHard.compare(today);
    in->isBeforeDiscussDeadline = in->discussDeadline.compare(today);
    
    if(!(oldisBeforePaperDeadline == in->isBeforePaperDeadline && //ie something changed
    oldisBeforeAllocationDate == in->isBeforeAllocationDate &&
    oldisBeforeSoftReviewDeadline == in->isBeforeSoftReviewDeadline &&
    oldisBeforeHardReviewDeadline == in->isBeforeHardReviewDeadline &&
    oldisBeforeDiscussDeadline == in->isBeforeDiscussDeadline))
    {
        updateConference(*in); // update conference in database if something changed
    }

}

void ConferenceManager::checkAllDeadlines()
{
    std::vector<Conference> in = getAllConferences(); //gets all conferences in database
    
    for (unsigned i = 0; i < in.size(); i++) {
      checkDeadlines(&in[i])
  }
}

std:vector<Conferences> ConferenceManager::getAllActiveConferences()
{
    std::vector<int> activeConfs = database->activeConfIDs();
    
    std::vector<Conference> conferences;
    
    for(unsigned int i = 0; i < activeConfs.size(); ++i)
    {
        conferences.push_back(database->fetchConference(activeConfs[i]));
    }
    
    return conferences;
}

std:vector<Conference> ConferenceManager::getAllConferences()
{
    std::vector<int> allConfs = database->allConfIDs();
    
    std::vector<Conference> conferences;
    
    for(unsigned int i = 0; i < activeConfs.size(); ++i)
    {
        conferences.push_back(database->fetchConference(allConfs[i]));
    }
    
    return conferences;
}

void ConferenceManager::fetchConference(int confID)
{
    *currentConference = database->fetchConference(confID);
}


void ConferenceManager::allocatePapers()
{
        //for each paper!!!!
        //NEED LOOP HERE
        PaperForReview(paperID, &currentConference, currentConference->reviewersPerPaper, getDatabase());
}   
    
void ConferenceManager::sendConference()
{
    //send *currentConference to the user
}

void ConferenceManager::sendConferenceBatch()
{
    //send getAllActiveConferences to the client
}
