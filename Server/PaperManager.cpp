void PaperManager::fetchPaper(int paperID)
{
  *currentPaper = db->fetchPaper(paperID);
}
