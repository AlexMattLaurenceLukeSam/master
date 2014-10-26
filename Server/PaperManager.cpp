void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = db->fetchPaper(paperID);
}

void PaperManager::sendPaper(int paperID)
{
  fetchPaper(paperID);
 //send *currentPaper to the client
}

void PaperManager::addPaper()
{
  db->createPaper(*currentPaper);
}

void PaperManager::modifyPaper()
{
  db->updatePaper(*currentPaper);
}

void PaperManager::sendPaperSummaryBatch(int confID)
{
  std::vector<int> paperIDsOfConf = db->getPaperIDsForConf(confID);
  //returns all paperSummaries using that confID
  std::vector<PaperSummary> papersOfConf;
  for(unsigned int i = 0; i < paperIDsOfConf.size(); ++i)
  {
    papersOfConf[i] = fetchPaperSummary(paperIDsOfConf[i]);
  }
  //send papersOfConf to the client
}

void PaperManager::sendPaperSummariesToReview(int userID, int confID)
{
 std::vector<int> paperIDsToReview = db->getPaperIDsForAllocatedReviewer(userID, confID); //or something like that
 std::vector<PaperSummary> papersToReview;
 for(unsigned int i = 0; i < paperIDsToReview.size(); ++i)
 {
   papersToReview[i] = fetchPaperSummary(paperIDsToReview[i]);
 }
  //send papersToReview to the client
}

void PaperManager::sendAuthoredPaperSummaries(int leadAuthorID, int confID)
{
 std::vector<int> paperIDsAuthored = db->fetchPapersFromLeadAuthorIDAndConfID(leadAuthorID, confID); 
 //or something like that
 std::vector<PaperSummary> papersAuthored;
 for(unsigned int i = 0; i < paperIDsAuthored.size(); ++i)
 {
   papersAuthored[i] = fetchPaperSummary(paperIDsAuthored[i]);
 }
  //send papersAuthored to the client
}



