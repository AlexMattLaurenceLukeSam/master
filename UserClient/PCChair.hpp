#include "User.hpp"

#include <vector>

Class PCChair : public User {
  public:
  PCChair(const std::vector<std::string>& iallPapers)
  : allPapers(iallPapers)
  { }
  std::vector<Paper> getAllPapers() {return allPapers;}
  void setAllPapers(const std::vector<Paper>& iallPapers) {allPapers = iallPapers;}
  void view();
  private:
  std::vector<std::string> allPapers;

};
