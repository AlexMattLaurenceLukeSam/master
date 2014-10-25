#include "Reviewer.hpp"

void Reviewer::getPapersToReview()
{
    //sends request to server asking for all PaperSummaries allocated to the reviewer
    //populates the allocatedPapers vector with the response PaperSummaries
}

void Reviewer::submitReview()
{
    //sends a Review packet to the server
    // no response
}

void Reviewer::editReview()
{
    //sends a Review packet to the server
    // no response
    //may not need this function, may just be able to use the above
}

void Reviewer::bidOnPaper()
{
    //sends a bid packet to the server
    //no response
}

//void Reviewer::modifyPaper()
//{
//dont think this is needed
//}

void Reviewer::getDiscussion()
{
    //requests a dicussion packet from the server
    //sets the discussion of the currentPaper based on the response
}

void Reviewer::addDiscussion()
{
    //sends a discussion packet to the server
    //no response, gui will hack the text onto the end of the discussion
}
