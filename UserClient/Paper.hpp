#ifndef PAPER_H
#define PAPER_H

#include "Discussion.hpp"

#include <vector>

class User;

class Paper {
  public:
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

// assignment operator or copy constructor deemed not needed at this time

    std::string getTitle() {return title;}
    std::string getAbstract() {return abstract;}
    std::vector<User> getAuthors() {return authors;}
    std::vector<std::string> getKeywords() {return keywords;}
    std::string getConfKeyword() {return confKeyword;}
    std::vector<Review> getReviews() {return reviews;}
    Discussion getDiscussion() {return discussion;}
    int getPaperID() {return paperID;}
    int getConfID() {return confID;}
    int getLeadAuthorID() {return leadAuthorID;}
    
    void setTitle(const std::string& ititle) {title = ititle;}
    void setAbstract(const std::string& iabstract) {abstract = iabstract;}
    void setAuthors(const std::vector<User>& iauthors) {authors = iauthors;}
    void setKeywords(const std::vector<std::string>& ikeywords) {keywords = ikeywords;}
    void setConfKeyWord(const std::string& iconfKeyword) {confKeyword = iconfKeyword;}
    void setReviews(const std::Vector<Review>& ireviews) {reviews = ireviews;}
    void setDiscussion(Discussion idiscussion) {discussion = idiscussion;} // potentially if the papers have the wrong discussions they can be swapped using this
    void setPaperID(int ipaperID) {paperID = ipaperID;}
    void setConfID(int iconfID) {confID = iconfID;}
    void setLeadAuthorID(int ileadAuthorID) {leadAuthorID = ileadAuthorID;}
    void downloadPaper();

  private:
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
};
#endif
