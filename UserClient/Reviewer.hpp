#include "Author.hpp"
#include "Review.hpp"

Class Reviewer : public Author {
  public:
    Reviewer(const std::string& iusername,
      const std::string& iname,
      const std::string& iemail,
      const std::string& iorganisation,
      const std::string& iphone,
      int iuserID,
      const std::vector<string>& ikeywords,
      const std::vector<Paper>& iownPapers,
      const std::vector<Paper>& iallocatedPapers,
      const std::vector<Paper>& ipapersToBid,
      const std::vector<Review>& ireviews)
      :
      username(iusername),
      name(iname),
      email(iemail),
      organisation(iorganisation),
      phone(iphone),
      userID(iuserID),
      keywords(ikeywords),
      ownPapers(iownPapers),
      allocatedPapers(iallocatedPapers),
      papersToBid(ipapersToBid),
      reviews(ireviews)
      { }
    void view();
    std::vector<Paper> getAllocatedPapers() {return allocatedPapers;}
    std::vector<Paper> getPapersToBid() {return papersToBid;}
    std::vector<Review> getReviews() {return reviews;}
    void setAllocatedPapers(const std::vector<Paper>& iallocatedPapers) {allocatedPapers = iallocatedPapers;}
    void setPapersToBid(const std::vector<Paper>& ipapersToBid) {papersToBid = ipapersToBid;}
    void setReviews(const std::vector<Review>& ireviews) {reviews = ireviews;}

  private:
    std::vector<Paper> allocatedPapers;
    std::vector<Paper> papersToBid;
    std::vector<Review> reviews;
};

