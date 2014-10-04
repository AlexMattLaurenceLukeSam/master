//incomplete
#include "Discussion.hpp"
#include "Review.hpp"

#include <fstream>
#include <memory>
#include <vector>

Struct Paper {

    Paper() { discussion = std::unique_ptr<Discussion>(new Discussion);}
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<string>& iauthorNames,
      const std::vector<string>& ikeywords,
      const std::string& ifname,
      char* ipaper,
      const std::vector<review>& ireviews)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
      fname(ifname),
      paper(ipaper), // constructs from cstring
      reviews(ireviews)
      {discussion = std::unique_ptr<Discussion>(new Discussion);}

    std::string title;
    std::string abstract;
    std::vector<std::string> authorNames;
    std::vector<std::string> keywords;
    std::string fname;
    std::fstream paper;
    std::unique_ptr<Discussion> discussion;
    std::vector<review> reviews;
};
