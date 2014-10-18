#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "DiscussionPost.hpp"

#include <list>

Struct Discussion {
  Discussion(const std::list<DiscussionPost>& idiscussion):
               discussion(idiscussion)
               { }
  std::list<DiscussionPost> discussion;
};
#endif
