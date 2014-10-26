void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = database->fetchPaper(paperID);
}

void PaperManager::addPaper(const std::string& pdf)
{
  database->createPaper(*currentPaper, pdf);
}

void PaperManager::modifyPaper(int paperID)
{
  fetchPaper(int paperID);
  database->updatePaper(*currentPaper);
}

void PaperManager::modifyPDF(int paperID, int confID, const std::string& pdf)
{
   database->updatePDF(paperID, confID, pdf);
}

void PaperManager::addReview(Review rev)
{
  db->modifyReview(currentPaper->confID, rev);
}

void PaperManager::fetchReview(int reviewerID)
{
  // send the following to client db->fetchReview(currentPaper->paperID, reviewerID, currentPaper->confID);
}

void PaperManager::modifyReview(Review rev)
{
  db->modifyReview(currentPaper->confID, rev);
}

void fetchDiscussion()
{
  // send the following to client db->fetchDiscussion(currentPaper->paperID, currentPaper->confID);
}

void fetchRebuttal(int userID)
{
  // send the following to client db->fetchRebuttal(currentPaper->paperID, userID, currentPaper->confID);
}

void createDiscussionPost(DiscussionPost discussionPost)
{
  db->createDiscussionPost(discussionPost, currentPaper->paperID, currentPaper->confID);
}

void PaperManager::sendPaper(int paperID)
{
  fetchPaper(paperID);
 //send *currentPaper to the client
}

void PaperManager::sendPaperSummaryBatch(int confID)
{
  std::vector<int> paperIDsOfConf = database->getPaperIDsForConf(confID);
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
 std::vector<int> paperIDsToReview = database->getPaperIDsForAllocatedReviewer(userID, confID); //or something like that
 std::vector<PaperSummary> papersToReview;
 for(unsigned int i = 0; i < paperIDsToReview.size(); ++i)
 {
   papersToReview[i] = fetchPaperSummary(paperIDsToReview[i]);
 }
  //send papersToReview to the client
}

void PaperManager::sendAuthoredPaperSummaries(int leadAuthorID, int confID)
{
 std::vector<int> paperIDsAuthored = database->getPaperIDsForLeadAuthor(leadAuthorID, confID); 
 std::vector<PaperSummary> papersAuthored;
 for(unsigned int i = 0; i < paperIDsAuthored.size(); ++i)
 {
   papersAuthored[i] = fetchPaperSummary(paperIDsAuthored[i]);
 }
  //send papersAuthored to the client
}

void sendPapersAccepted(int confID)
{
  std::vector<int> acceptedPaperIDs = db->fetchPaperAccepted(confID);
  std::vector<Paper> acceptedPapers;
  for(unsigned int i = 0; i < acceptedPaperIDs.size(); ++i)
  {
    fetchPaper(acceptedPaperIDs[i]);
    std::vector<Paper> acceptedPapers[i] = *currentPaper;
  }
  // send acceptedPapers to client 
}
void addPaperAccepted(int paperID)
{
  fetchPaper(paperID);
  db->addPaperAccepted(currentPaper->paperID, currentPaper->confID);
}



