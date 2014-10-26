//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "../DataAll/Discussion.hpp"
#include "Review.hpp"
#include "User.hpp"

#include <vector>

struct Paper {

    std::string title{""};
    std::string abstract{""};
    std::vector<User> authors;
    std::vector<std::string> keywords;
    std::string confKeyword{""};
    std::vector<Review> reviews;
    Discussion discussion;
    int paperID{0};
    int confID{0};
    int leadAuthorID{0};

    Paper() { }
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<User>& iauthors,
      const std::vector<std::string>& ikeywords,
      const std::string& iconfKeyword,
      const std::vector<Review>& ireviews,
      const Discussion& idiscussion,
      int ipaperID,
      int iconfID,
      int ileadAuthorID)
      :
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      confKeyword(iconfKeyword),
      reviews(ireviews),
      discussion(idiscussion),
      paperID(ipaperID),
      confID(iconfID),
      leadAuthorID(ileadAuthorID)
      { }
    
    void addToKeywords(const std::string& in) {
      keywords.push_back(in);
    }
    void removeKeyword(const std::string& keywordToRemove) { //remove by paperID
      for(unsigned int i = 0; i < keywords.size(); ++i)
      {
        if(keywords[i] == keywordToRemove) {
          keywords.erase(keywords.begin() + i);
          return;
        }
      }
    }
    void addToAuthors(const User& in) {
      authors.push_back(in);
    }
    void removeAuthor(int userToRemove) { //remove by paperID
      for(unsigned int i = 0; i < authors.size(); ++i)
      {
        if(authors[i].userID == userToRemove) {
          authors.erase(authors.begin() + i);
          return;
        }
      }
    }
    void addToReviews(const Review& in) {
      reviews.push_back(in);
    }
    void removeReview(int reviewToRemove) { //remove by reviewer ID
      for(unsigned int i = 0; i < reviews.size(); ++i)
      {
        if(reviews[i].reviewerID == reviewToRemove) {
          reviews.erase(reviews.begin() + i);
          return;
        }
      }
    }
    // no assignment operator or copy constructor deemed necessary at this point
};
#endif
