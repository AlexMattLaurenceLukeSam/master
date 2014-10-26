//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "Discussion.hpp"
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

    // no assignment operator or copy constructor deemed necessary at this point
};
#endif
