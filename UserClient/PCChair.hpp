#ifndef P_C_CHAIR_H
#define P_C_CHAIR_H

#include "User.hpp"

#include <vector>

Class PCChair : public User {
  public:
  PCChair(const std::vector<std::string>& iallPapers)
  : allPapers(iallPapers)
  { }
  std::vector<Paper> getAllPapers() {return allPapers;}
  void setAllPapers(const std::vector<Paper>& iallPapers) {allPapers = iallPapers;}
  void view();
  void removeReviewer()
  bool removeReviewerByName(std::string)
  void editConfDetails()
  void setConfDeadlines()
  void setConfKWords()
  int getAvgScoreForPaper()
  void acceptOrRejectPaper()
  void addReviewerToConf()

  private:
  Paper* getPaperByTitle(std::string)
  std::vector<std::string> allPapers;

};
#endif
