#ifndef DISCUSSION_POST_H
#define DISCUSSION_POST_H

#include <string>

struct DiscussionPost {
  DiscussionPost(const std::string& icomment,
                 const std::string& ireviewerUName):
                 comment(icomment),
                 reviewerUName(ireviewerUName)
                 { }
  std::string comment;
  std::string reviewerUName;
};
#endif
