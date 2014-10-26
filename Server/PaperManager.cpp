void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = db->fetchPaper(paperID);
}

void PaperManager::sendPaper(int paperID)
{
  fetchPaper(paperID);
 //send *currentPaper to the client
}

void PaperManager::sendPaperSummaryBatch(int confID)
{
  std::vector<int> paperIDsOfConf = db->getPaperIDsForConf(confID);
  //returns all paperSummaries using that confID
  std::vector<PaperSummaries> papersOfConf;
  for(unsigned int i = 0; i < paperIDsOfConf.size(); ++i)
  {
    fetchPaper(paperIDsOfConf[i]); //curentPaper now points to it
    papersOfConf[i] = PaperSummary(currentPaper->paperID, currentPaper->title);
  }
  //send papersOfConf to the client
}

void PaperManager::sendPaperSummariesToReview(int userID, int confID)
{
 std::vector<int> paperIDsToReview = db->fetchPapersFromUserIDAndConfID(userID, confID); //or something like that
 std::vector<PaperSummaries> papersToReview;
 for(unsigned int i = 0; i < paperIDsToReview.size(); ++i)
 {
   fetchPaper(paperIDsToReview[i]); //curentPaper now points to it
   papersToReview[i] = PaperSummary(currentPaper->paperID, currentPaper->title);
 }
  //send papersToReview to the client
}

void PaperManager::sendAuthoredPaperSummaries(int leadAuthorID, int confID)
{
 std::vector<int> paperIDsAuthored = db->fetchPapersFromLeadAuthorIDAndConfID(leadAuthorID, confID); 
 //or something like that
 std::vector<PaperSummaries> papersAuthored;
 for(unsigned int i = 0; i < paperIDsAuthored.size(); ++i)
 {
   fetchPaper(paperIDsAuthored[i]); //curentPaper now points to it
   papersAuthored[i] = PaperSummary(currentPaper->paperID, currentPaper->title);
 }
  //send papersAuthored to the client
}



