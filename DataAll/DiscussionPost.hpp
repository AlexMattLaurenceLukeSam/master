#ifndef DISCUSSION_POST_H
#define DISCUSSION_POST_H
#include <string>

struct DiscussionPost {
  DiscussionPost(const std::string& icomment,
                 int ireviewerID,
                 int ipostID):
                 comment(icomment),
                 reviewerID(ireviewerID),
                 postID(ipostID)
                 { }
  std::string comment{""};
  int reviewerID{0};
  int postID{0};
};
#endif
