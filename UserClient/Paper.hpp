//incomplete
#include "Discussion.hpp"

#include <fstream>
#include <vector>

Class Paper {
  public:
    Paper() { *discussion = new Discussion;}
    ~Paper() {delete discussion;}
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<string>& iauthorNames,
      const std::vector<string>& ikeywords,
      const std::string& ifname,
      char* ipaper)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
      fname(ifname),
      paper(ipaper) // constructs from cstring
      {*discussion = new Discussion;} // Means you can't initialize with a discussion, but that seems to be a hairy area anyway
      // In those edge cases one could still initialize then set or use copy constructor
/*    Paper(const Paper& ipaper) {
      title = ipaper.title;
      abstract = ipaper.abstract;
      authorNames = ipaper.authorNames;
      keywords = ipaper.keywords;
      fname = ifname;
      paper = ipaper.paper;
    }  */

 /*   void operator=(const Paper& ipaper) {
      title = ipaper.title;
      abstract = ipaper.abstract;
      authorNames = ipaper.authorNames;
      keywords = ipaper.keywords;
      fname = ifname;
      paper = ipaper.paper;
    }  */


    std::string getTitle() {return title;}
    std::string getAbstract() {return abstract;}
    std::vector<std::string> getAuthorNames() {return authorNames;}
    std::vector<std::string> getKeywords() {return keywords;}
    std::string getFname() {return fname;}
    std::fstream getPaper() {return paper;}
    Discussion* getDiscussion() {return discussion;}
    void setTitle(const std::string& ititle) {title = ititle;}
    void setAbstract(const std::string& iabstract) {abstract = iabstract;}
    void setAuthorNames(const std::vector<std::string>& iauthorNames) {authorNames = iauthorNames;}
    void setKeywords(const std::vector<std::string>& ikeywords) {keywords = ikeywords;}
    void setFname(const std::fstream& ipaper) {paper = ipaper;}
    void setDiscussion(Discussion* idiscussion) {discussion = idiscussion;} // potentially if the papers have the wrong discussions they can be swapped using this

  private:
    std::string title;
    std::string abstract;
    std::vector<std::string> authorNames;
    std::vector<std::string> keywords;
    std::string fname;
    std::fstream paper;
    Discussion* discussion;
};
