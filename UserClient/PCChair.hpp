#ifndef P_C_CHAIR_H
#define P_C_CHAIR_H

#include "Paper.hpp"
#include "PaperSummary.hpp"
#include "User.hpp"

#include <vector>

class PCChair : public User {
  public:
  PCChair(const std::vector<PaperSummary>& iallPapers)
  : allPapers(iallPapers)
  { }
  std::vector<PaperSummary> getAllPapers() {return allPapers;}
  void setAllPapers(const std::vector<PaperSummary>& iallPapers) {allPapers = iallPapers;}
  void view();
  void removeReviewer();
  bool removeReviewerByName(std::string);
  void editConfDetails();
  void setConfDeadlines();
  void setConfKWords();
  int getAvgScoreForPaper();
  void acceptOrRejectPaper();
  void addReviewerToConf();

  private:
  PaperSummary* getPaperByTitle(std::string);
  PaperSummary* getPaperById(int);
  std::vector<PaperSummary> allPapers;
  Conference* activeConference;
};
#endif
