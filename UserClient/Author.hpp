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
    void submitRebuttal();*/

    Author(const std::string& iuserName,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         const std::string& ipassword,
         int iuserID,
         UserType_t iuserType,
         const std::vector<std::string>& ikeywords,
         const std::vector<PaperSummary>& iownPapers):
         User(iuserName,
         iname,
         iemail,
         iorganisation,
         iphone,
         ipassword,
         iuserID,
         iuserType
         ),
         keywords(ikeywords),
         ownPapers(iownPapers)
         { }
    virtual void view();
    void getAllPapers();
    void getPaper();
    void submitPaper();
    void modifyPaper();
    void submitRebuttal();
    void modifyDetails();

    std::vector<std::string> keywords;
    std:vector<PaperSummary> getOwnPapers() {return ownPapers;}
    void setOwnPapers(const std::vector<PaperSummary>& iownPapers) {ownPapers = iownPapers;}
  protected:
    std::vector<PaperSummary> ownPapers;
};
#endif
