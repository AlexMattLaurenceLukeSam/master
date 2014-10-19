//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "Discussion.hpp"
#include "Review.hpp"

#include <memory>
#include <vector>

struct Paper {

    Paper() { }
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<std::string>& iauthorNames,
      const std::vector<std::string>& ikeywords,
      const std::string& ifname,
      const std::vector<Review>& ireviews,
      const Discussion& idiscussion)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
      fname(ifname),
      reviews(ireviews),
      discussion(idiscussion)
      { }

    // no assignment operator or copy constructor deemed necessary at this point
    void downloadPaper();

    std::string title;
    std::string abstract;
    std::vector<std::string> authorNames;
    std::vector<std::string> keywords;
    std::string fname;
    std::fstream paper;
    Discussion discussion;
    std::vector<Review> reviews;
};
#endif
