#ifndef PAPER_H
#define PAPER_H

#include "Discussion.hpp"

#include <vector>

class Paper {
  public:
    Paper() { }
    Paper(const std::string& ititle,
      const std::string& iabstract,
      const std::vector<std::string>& iauthorNames,
      const std::vector<std::string>& ikeywords,
      const std::string& ifname,
      const Discussion& idiscussion)
      :
      title(ititle),
      abstract(iabstract),
      authorNames(iauthorNames),
      keywords(ikeywords),
      fname(ifname),
      discussion(idiscussion)
      { } // Means you can't initialize with a discussion, but that seems to be a hairy area anyway
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

// assignment operator or copy constructor deemed not needed at this time

    std::string getTitle() {return title;}
    std::string getAbstract() {return abstract;}
    std::vector<std::string> getAuthorNames() {return authorNames;}
    std::vector<std::string> getKeywords() {return keywords;}
    std::string getFname() {return fname;}
    //std::fstream getPaper() {return paper;}
    Discussion* getDiscussion() {return discussion;}
    void setTitle(const std::string& ititle) {title = ititle;}
    void setAbstract(const std::string& iabstract) {abstract = iabstract;}
    void setAuthorNames(const std::vector<std::string>& iauthorNames) {authorNames = iauthorNames;}
    void setKeywords(const std::vector<std::string>& ikeywords) {keywords = ikeywords;}
    void setFname(const std::string& ifname) {fname = ifname;}
    void setDiscussion(Discussion* idiscussion) {discussion = idiscussion;} // potentially if the papers have the wrong discussions they can be swapped using this
    void downloadPaper();

  private:
    std::string title{""};
    std::string abstract{""};
    std::vector<std::string> authorNames;
    std::vector<std::string> keywords;
    std::string fname{""};
    Discussion discussion;
};
#endif
