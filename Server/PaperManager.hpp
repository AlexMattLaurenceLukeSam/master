#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

struct PaperManager {
  PaperManager() {temp = NULL;}
  PaperManager(Paper* itemp) : temp(itemp) { }
  ~PaperManager() {delete temp;}
  Paper* temp;

  void addPaper();
  void modifyPaper(int);
  bool deleteDiscPost(int);
  void modifyDiscPost(int);
  bool deleteReview(int);
  void modifyReview(int);
  bool deletePaper(int);
  void sendPaper();
  void sendPaperBatch(int);
  void sendAuthoredPaper(int);
  void sendPapersToReview(int);

private:
void fetchPaper(int);

};
#endif
