#ifndef DISCUSSION_POST_H
#define DISCUSSION_POST_H

#include <string>

struct DiscussionPost 
{
    DiscussionPost()
    {
        comment = "";
        reviewerID = 0;
        postID = 0;
    }
    
    DiscussionPost(const std::string& icomment,
        int ireviewerID,
        int ipostID)
    {
        comment = icomment;
        reviewerID = ireviewerID;
        postID = ipostID;
    }
    
// No postID
    DiscussionPost(const std::string& icomment,
        int ireviewerID)
    {
        comment = icomment;
        reviewerID = ireviewerID;
    }
    
    std::string comment;
    int reviewerID;
    int postID;
};

#endif
