#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H
#include "../DataAll/Paper.hpp"

class PaperManager {
public:
  PaperManager() { }
  PaperManager(Paper* icurrentPaper) : currentPaper(icurrentPaper) { }
  ~PaperManager() { if(currentPaper != nullptr)
                     delete currentPaper;}
  Paper* getCurrentPaper() {return currentPaper;}
  void setCurrentPaper(Paper* icurrentPaper) {currentPaper = icurrentPaper;}

  void downloadPaper();
void addToKeywords(const std::string& in) {
      currentPaper->keywords.push_back(in);
    }
    void removeKeyword(const std::string& keywordToRemove) { //remove by paperID
      for(unsigned int i = 0; i < currentPaper->keywords.size(); ++i)
      {
        if(currentPaper->keywords[i] == keywordToRemove) {
          currentPaper->keywords.erase(currentPaper->keywords.begin() + i);
          return;
        }
      }
    }
    void addToAuthors(const User& in) {
      currentPaper->authors.push_back(in);
    }
    void removeAuthor(int userToRemove) { //remove by paperID
      for(unsigned int i = 0; i < currentPaper->authors.size(); ++i)
      {
        if(currentPaper->authors[i].userID == userToRemove) {
          currentPaper->authors.erase(currentPaper->authors.begin() + i);
          return;
        }
      }
    }
    void addToReviews(const Review& in) {
      currentPaper->reviews.push_back(in);
    }
    void removeReview(int reviewToRemove) { //remove by reviewer ID
      for(unsigned int i = 0; i < currentPaper->reviews.size(); ++i)
      {
        if(currentPaper->reviews[i].reviewerID == reviewToRemove) {
          currentPaper->reviews.erase(currentPaper->reviews.begin() + i);
          return;
        }
      }
    }

private:
/*  void viewDiscussion();
  void addDiscPost();
  void removeDiscPost();
  void editDiscPost();
  void addReview();
  void listReviews();
  void editReview();
  void removeReview(); */

  Paper* currentPaper{nullptr};

};
#endif
