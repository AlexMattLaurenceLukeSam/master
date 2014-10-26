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
    std::string fname{""};
    std::vector<Review> reviews;
    Discussion discussion;
    int paperId{0};

    Paper() { }
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<User>& iauthors,
      const std::vector<std::string>& ikeywords,
      const std::string& ifname,
      const std::vector<Review>& ireviews,
      const Discussion& idiscussion,
      int ipaperId)
      :
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      fname(ifname),
      reviews(ireviews),
      discussion(idiscussion),
      paperId(ipaperId)
      { }

    // no assignment operator or copy constructor deemed necessary at this point
};
#endif
