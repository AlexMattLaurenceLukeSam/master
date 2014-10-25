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

  void createPaper();
  void removePaper();
  void listPapers();
  void viewPaper();
  void editPaper();
  void downloadPaper();

private:
  void viewDiscussion();
  void addDiscPost();
  void removeDiscPost();
  void editDiscPost();
  void addReview();
  void listReviews();
  void editReview();
  void removeReview();

  Paper* currentPaper{nullptr};

};
#endif
