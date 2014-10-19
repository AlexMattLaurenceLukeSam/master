#ifndef AUTHOR_H
#define AUTHOR_H

#include "Paper.hpp"
#include "PaperSummary.hpp"
#include "User.hpp"

#include <vector>

class Author : public User {
  public:
    Author() { }
    /*
    Author(const std::string& iuserName,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         int iuserID,
         const std::vector<std::string>& ikeywords,
         const std::vector<Paper>& iownPapers):
         userName(iuserName),
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         userID(iuserID),
         keywords(ikeywords),
         ownPapers(iownPapers)
         { }
    virtual void view();
    void getPapers();
    void submitPaper();
    void modifyPaper();
    void submitRebuttal(); */
    
    Author(const std::string& iuserName,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         int iuserID,
         const std::vector<std::string>& ikeywords,
         const std::vector<PaperSummary>& iownPapers):
         User(iuserName, 
         iname,
         iemail,
         iorganisation,
         iphone,
         iuserID
         ),
         keywords(ikeywords),
         ownPapers(iownPapers)
         { }
    virtual void view();
    void getPapers();
    void submitPaper();
    void modifyPaper();
    void submitRebuttal(); 

    std::vector<std::string> keywords;

  protected:
    std::vector<PaperSummary> ownPapers;

};
#endif
