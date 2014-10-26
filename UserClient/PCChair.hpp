#ifndef P_C_CHAIR_H
#define P_C_CHAIR_H

#include "Paper.hpp"
#include "PaperSummary.hpp"
#include "User.hpp"
#include "Conference.hpp" // for activeConference memeber variable

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
  void acceptOrRejectPaper(bool); // NOTE: changed parameter from int to bool to match function description
  void addReviewerToConf(int);
  void addReviewerToPaper(int, int);
  void fetchPapers();
  void fetchUsers();
  void checkConferencesDeadlines(); // NOTE: was not declared but function existed, putting here for now
  void addToAllPapers(const PaperSummary& in) {
    allPapers.push_back(in);
  }
  void removePaperFromOwnPapers(int paperToRemove) { //remove by paperID
    for(unsigned int i = 0; i < allPapers.size(); ++i)
    {
      if(allPapers[i].paperID == paperToRemove) {
        allPapers.erase(allPapers.begin() + i);
        return;
      }
    }
  }
  void addToAllUsers(const User& in) {
    allUsers.push_back(in);
  }
  void removeUser(int userToRemove) { //remove by paperID
    for(unsigned int i = 0; i < allUsers.size(); ++i)
    {
      if(allUsers[i].userID == userToRemove) {
        allUsers.erase(allUsers.begin() + i);
        return;
      }
    }
  }
  private:
  PaperSummary* getPaperByTitle(std::string);
  PaperSummary* getPaperById(int);
  std::vector<PaperSummary> allPapers;
  std::vector<User> allUsers;
  Conference* activeConference{nullptr};
};
#endif
