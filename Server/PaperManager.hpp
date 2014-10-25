#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

class PaperManager {
public:
  PaperManager() { }
  PaperManager(Paper* icurrentPaper) : currentPaper(icurrentPaper) { }
  ~PaperManager() { if(currentPaper != nullptr)
                      delete currentPaper;}

  Paper* getCurrentPaper() {return currentPaper;}
  void setCurrentPaper(Paper* icurrentPaper) {currentPaper = icurrentPaper;}
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
Paper* currentPaper{nullptr};
};
#endif
