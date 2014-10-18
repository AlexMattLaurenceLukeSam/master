#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

Struct PaperManager {
  PaperManager() {temp = NULL;}
  PaperManager(Paper* itemp) : temp(itemp) { }
  ~PaperManager() {delete temp;}
  Paper* temp;

  addPaper()
  modifyPaper(int)
  bool deleteDiscPost(int)
  modifyDiscPost(int)
  bool deleteReview(int)
  modifyReview(int)
  bool deletePaper(int)
  sendPaper()
  sendPaperBatch(int)
  sendAuthoredPaper(int)
  sendPapersToReview(int)

private:
  fetchPaper(int)

};
#endif
