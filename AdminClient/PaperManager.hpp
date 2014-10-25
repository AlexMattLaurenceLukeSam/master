#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "Paper.hpp"

class PaperManager {
public:
  PaperManager() { }
  PaperManager(Paper* itemp) : temp(itemp) { }
  ~PaperManager() { if(temp != nullptr)
                     delete temp;}
  void createPaper();
  void removePaper();
  void listPapers();
  void viewPaper();
  void editPaper();
  void downloadPaper();

  Paper* temp{nullptr};
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
