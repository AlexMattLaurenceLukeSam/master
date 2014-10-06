//incomplete
#include "Discussion.hpp"
#include "Review.hpp"

#include <fstream>
#include <memory>
#include <vector>

Struct Paper {

    Paper() { *discussion = new Discussion;}
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<string>& iauthorNames,
      const std::vector<string>& ikeywords,
//      const std::string& ifname,
//      char* ipaper,
      const std::vector<review>& ireviews)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
//      fname(ifname),
//      paper(ipaper), // constructs from cstring
      reviews(ireviews)
      {*discussion = new Discussion;}
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
