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
  void removeReviewerFromConf(int);
  void removeReviewerFromPaper(int, int);
  bool removeReviewerByName(std::string);
  void editConfDetails();
  //void setConfDeadlines();
  //void setConfKWords();covered by above
  //int getAvgScoreForPaper();dont think we really need this
  void acceptOrRejectPaper(int);
  void addReviewerToConf(int);
  void addReviewerToPaper(int, int);
  void fetchPapers();
  void fetchUsers();

  private:
  PaperSummary* getPaperByTitle(std::string);
  PaperSummary* getPaperById(int);
  std::vector<PaperSummary> allPapers;
  std::vector<User> allUsers;
  Conference* activeConference{nullptr};
};
#endif
