//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "../DataAll/Discussion.hpp"
#include "Review.hpp"
#include "User.hpp"

#include <vector>

struct Paper {

    Paper() { }
    Paper(const int ipaperID,
      const int iconfID,
      const int ileadAuthorID,
      const std::string& ititle,
      const std::string& iabstract,
      const std::vector<std::string>& iauthors,
      const std::vector<std::string>& ikeywords,
      const std::string& iconfKeyword,
      const std::vector<Review>& ireviews,
      const Discussion& idiscussion)
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
    // no assignment operator or copy constructor deemed necessary at this point
    int paperID{0};
    int confID{0};
    int leadAuthorID{0};
    std::string title{""};
    std::string abstract{""};
    std::vector<User> authors;
    std::vector<std::string> keywords;
    std::string confKeyword

    Discussion discussion;
    std::vector<Review> reviews;
};
#endif
