#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

struct PaperManager {
  PaperManager() {temp = NULL;}
  PaperManager(Paper* itemp) : temp(itemp) { }
  ~PaperManager() {delete temp;}
  void createPaper();
  void removePaper();
  void listPapers();
  void viewPaper();
  void editPaper();

  Paper* temp;
private:
  void viewDiscussion();
  void addDiscPost();
  void removeDiscPost();
  void editDiscPost();
  void addReview();
  void listReviews();
  void editReview();
  void removeReview();
};
#endif
