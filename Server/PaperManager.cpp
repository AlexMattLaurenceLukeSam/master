void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = db->fetchPaper(paperID);
}

PaperManager::sendAuthoredPaper(int paperID)
{
 fetchPaper(paperID);
  //send Paper to client
}

