#include "PCChair.hpp"

void PCChair::checkConferencesDeadlines()
{
  //calls checkDeadlines in conferenceManager on server with activeConference* 
  //need to use getActiveConference to obtain it
  //returns nothing
}

void PCChair::fetchPapers()
{
    //request PaperSummaries for ALL Papers belonging to this conference
    //populate allPapers vector with the PaperSummaries in the response

}

void PCChair::fetchUsers()
{
    //as above except for Users

}

void PCChair::removeReviewerFromConf(int)
{
    //construct packet matching data of the user with given uid but changing the utype to author
    //no response
}

void PCChair::editConfDetails()
{
    //send modified conference packet to the server
    //no response
}

void PCChair::acceptOrRejectPaper(bool)
{
    //send paper packet to server with data matching the current except that paper status is set to accepted if bool = true
    //else set to false

}

void PCChair::addReviewerToConf(int)
{
    //construct packet matching data of the user with given uid but changing the utype to reviewer
    //no response
}

void PCChair::addReviewerToPaper(int, int)
{
    //send PaperAssigned packet to server
    //no response
}

void PCChair::removeReviewerFromPaper(int, int)
{
    //send PaperAssigned packet to server to be deleted
    //no resposne

}
