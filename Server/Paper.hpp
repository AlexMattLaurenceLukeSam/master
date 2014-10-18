//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "Discussion.hpp"
#include "Review.hpp"

#include <fstream>
#include <memory>
#include <vector>

struct Paper {

    Paper() { discussion = new Discussion;}
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<std::string>& iauthorNames,
      const std::vector<std::string>& ikeywords,
//      const std::string& ifname,
//      char* ipaper,
      const std::vector<Review>& ireviews)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
//      fname(ifname),
//      paper(ipaper), // constructs from cstring
      reviews(ireviews)
      {discussion = new Discussion;}
    ~Paper() {delete discussion;}
    // no assignment operator or copy constructor deemed necessary at this point
    std::string title;
    std::string abstract;
    std::vector<std::string> authorNames;
    std::vector<std::string> keywords;
//    std::string fname;
//    std::fstream paper;
    Discussion* discussion;
    std::vector<Review> reviews;
};
#endif
