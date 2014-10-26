//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "../DataAll/Discussion.hpp"
#include "../DataAll/Review.hpp"
//#include "User.hpp"
#include "../DataAll/PersonalInfo.hpp"

#include <vector>

struct Paper {

    Paper() { }
    Paper(int &ipaperID,
      int &iconfID,
      int &ileadAuthorID,
      std::string& ititle,
      std::string& iabstract,
      std::vector<PersonalInfo>& iauthors,
      std::vector<std::string>& ikeywords,
      std::string& iconfKeyword,
      std::vector<Review>& ireviews,
      Discussion& idiscussion)
      :
      paperID(ipaperID),
      confID(iconfID),
      leadAuthorID(ileadAuthorID),
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      confKeyword(iconfKeyword),
      reviews(ireviews),
      discussion(idiscussion)
      { }

    Paper(
      int &iconfID,
      int &ileadAuthorID,
      std::string& ititle,
      std::string& iabstract,
      std::vector<PersonalInfo>& iauthors,
      std::vector<std::string>& ikeywords,
      std::string& iconfKeyword)
      :
      confID(iconfID),
      leadAuthorID(ileadAuthorID),
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      confKeyword(iconfKeyword)
      { }
    // no assignment operator or copy constructor deemed necessary at this point
    int paperID{0};
    int confID{0};
    int leadAuthorID{0};
    std::string title{""};
    std::string abstract{""};
    std::vector<PersonalInfo> authors;
    std::vector<std::string> keywords;
    std::string confKeyword;

    Discussion discussion;
    std::vector<Review> reviews;
};
#endif
