void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = db->fetchPaper(paperID);
}

void PaperManager::sendAuthoredPaper(int paperID)
{
 fetchPaper(paperID);
  //send Paper to client
}

void PaperManager::sendPapersToReview(int userID)
{
 std::vector<int> paperIDsToReview = db->fetchPapersFromUserID(userID); //or something like that
 std::vector<Paper> papersToReview;
 for(unsigned int i = 0; i < paperIDsToReview.size(); ++i)
 {
   fetchPaper; //curentPaper now points to it
   papersToReview[i] = *currentPaper;
 }
  //send this vector to the client
}

void PaperManager::sendPaper()
{
 //send *currentPaper to the client
}
