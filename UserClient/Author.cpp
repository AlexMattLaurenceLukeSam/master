#include "Author.hpp"

void Author::getAllPapers()
{
    //sends request to server asking for PaperSummaries

    //populates ownPaper vector with response
}

void Author::getPaper()
{
    //sends request to server asking for Paper with id matching the id of the current PaperSummary
    //sets currentPaper equal to the Paper returned in the response
}

void Author::modifyDetails()
{
    //sends a modified User packet to the server
    //no response
}

void Author::modifyPaper()
{
    //sends a modified Paper packet to the server
    //no response
}
