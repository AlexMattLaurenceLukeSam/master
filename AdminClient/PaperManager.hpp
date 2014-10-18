#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

Struct PaperManager {
  PaperManager() {temp = NULL;}
  PaperManager(Paper* itemp) : temp(itemp) { }
  ~PaperManager() {delete temp;}
  createPaper()
  removePaper()
  listPapers()
  viewPaper()
  editPaper()

  Paper* temp;
private:
  viewDiscussion()
  addDiscPost()
  removeDiscPost()
  editDiscPost()
  addReview()
  listReviews()
  editReview()
  removeReview()
};
#endif
