#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "../DataAll/DiscussionPost.hpp"

#include <list>

struct Discussion 
{
    Discussion()
    {
        //discussion list
    }

    Discussion(const std::list<DiscussionPost>& idiscussion)
    {
        discussion = idiscussion;
    }

    Discussion(const Discussion& in) 
    {
        discussion = in.discussion;
    }

    std::list<DiscussionPost> discussion;
};

#endif
