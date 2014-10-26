#ifndef DISCUSSION_POST_H
#define DISCUSSION_POST_H

#include <string>

struct DiscussionPost {
  DiscussionPost(const std::string& icomment,
                 int ireviewerID):
                 comment(icomment),
                 reviewerID(ireviewerID)
                 { }
  std::string comment{""};
  int reviewerID{""};
};
#endif
