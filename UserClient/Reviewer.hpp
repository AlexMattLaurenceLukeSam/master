#ifndef REVIEWER_H
#define REVIEWER_H

#include "Author.hpp"
#include "PaperSummary.hpp"
#include "Review.hpp"

class Reviewer : public Author {
  public:
/*    Reviewer(const std::string& iuserName,
      const std::string& iname,
      const std::string& iemail,
      const std::string& iorganisation,
      const std::string& iphone,
      int iuserID,
      const std::vector<std::string>& ikeywords,
      const std::vector<Paper>& iownPapers,
      const std::vector<Paper>& iallocatedPapers,
      const std::vector<Paper>& ipapersToBid,
      const std::vector<Review>& ireviews)
      :
      userName(iuserName),
      name(iname),
      email(iemail),
      organisation(iorganisation),
      phone(iphone),
      userID(iuserID),
      keywords(ikeywords),
      ownPapers(iownPapers),
      allocatedPapers(iallocatedPapers),
      papersToBid(ipapersToBid),
      reviews(ireviews)
      { } */
    Reviewer() {}
    Reviewer(const std::string& iuserName,
      const std::string& iname,
      const std::string& iemail,
      const std::string& iorganisation,
      const std::string& iphone,
      const std::string& ipassword,
      int iuserID,
      UserType_t iuserType,
      const std::vector<std::string>& ikeywords,
      const std::vector<PaperSummary>& iownPapers,
      const std::vector<PaperSummary>& iallocatedPapers,
      const std::vector<PaperSummary>& ipapersToBid,
      const std::vector<Review>& ireviews)
      :
      Author(iuserName,
      iname,
      iemail,
      iorganisation,
      iphone,
      ipassword,
      iuserID,
      iuserType,
      ikeywords,
      iownPapers
      ),
      allocatedPapers(iallocatedPapers),
      papersToBid(ipapersToBid),
      reviews(ireviews)
      { }
    void view();
    void getPapersToReview();
    void submitReview();
    void editReview();
    void bidOnPaper();
//    void modifyPaper();
    void getDiscussion();
    void addDiscussion();

    std::vector<PaperSummary> getAllocatedPapers() {return allocatedPapers;}
    std::vector<PaperSummary> getPapersToBid() {return papersToBid;}
    std::vector<Review> getReviews() {return reviews;}
    void setAllocatedPapers(const std::vector<PaperSummary>& iallocatedPapers) {allocatedPapers = iallocatedPapers;}
    void setPapersToBid(const std::vector<PaperSummary>& ipapersToBid) {papersToBid = ipapersToBid;}
    void setReviews(const std::vector<Review>& ireviews) {reviews = ireviews;}
    void addToAllocatedPapers(const PaperSummary& in) {
      allocatedPapers.push_back(in);
    }
    void removeAllocatedPaper(int paperToRemove) { //remove by paperID
      for(unsigned int i = 0; i < allocatedPapers.size(); ++i)
      {
        if(allocatedPapers[i].paperID == paperToRemove) {
          allocatedPapers.erase(allocatedPapers.begin() + i);
          return;
        }
      }
    } 
    
    void addToPapersToBid(const PaperSummary& in) {
      papersToBid.push_back(in);
    }
    void removePaperToBid(int paperToRemove) {
      for(unsigned int i = 0; i < papersToBid.size(); ++i)
      {
        if(papersToBid[i].paperID == paperToRemove) {
          papersToBid.erase(papersToBid.begin() + i);
          return;
        }
      }
    } 
    
    void addToReviews(const Review& in) {
      reviews.push_back(in);
    }
    void removeReview(int paperToRemove) {
      for(unsigned int i = 0; i < reviews.size(); ++i)
      {
        if(reviews[i].paperID == paperToRemove) {
          reviews.erase(reviews.begin() + i);
          return;
        }
      }
    } 
    
  private:
    Paper* getPaperByTitle(std::string); // helper
    Paper* getPaperByIndex(int); // helper

    std::vector<PaperSummary> allocatedPapers;
    std::vector<PaperSummary> papersToBid;
    std::vector<Review> reviews;
};
#endif
