#ifndef AUTHOR_H
#define AUTHOR_H

#include "Paper.hpp"
#include "User.hpp"

#include <vector>

Class Author : public User {
  public:
    Author(const std::string& iusername,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         int iuserID,
         const std::vector<string>& ikeywords,
         const std::vector<Paper>& iownPapers):
         username(iusername),
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         userID(iuserID),
         keywords(ikeywords),
         ownPapers(iownPapers)
         { }
    virtual void view();
    void getPapers()
    void submitPaper()
    void modifyPaper()
    void submitRebuttal()


    std::vector<std::string> keywords;

  protected:
    std::vector<Paper> ownPapers;
};
#endif
