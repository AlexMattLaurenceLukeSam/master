#ifndef CONFERENCE_H
#define CONFERENCE_H

#include "../DataAll/Date.hpp"

#include <string>
#include <vector>

struct Conference {
    Conference()
    {
        isActive = false;
        title = "";
        confID = 0;
        topic = "";
        description = "";
        location = "";
        //keywords vector
        isBeforePaperDeadline = false;
        paperDeadline = Date();
        isBeforeAllocationDate = false;
        allocationDate = Date();
        isBeforeSoftReviewDeadline = false;
        reviewDeadlineSoft = Date();
        isBeforeHardReviewDeadline = false;
        reviewDeadlineHard = Date();
        isBeforeDiscussDeadline = false;
        discussDeadline = Date();
        reviewersPerPaper = 0;
        postWordLimit = 0;
    }

    Conference(
        bool iisActive,
        std::string& ititle,
        int& iconfID,
        std::string& itopic,
        std::string& idescription,
        std::string& ilocation,
        std::vector<std::string>& ikeywords,
        bool iisBeforePaperDeadline,
        Date& ipaperDeadline,
        bool iisBeforeAllocationDate,
        Date& iallocationDate,
        bool iisBeforeSoftReviewDeadline,
        Date& ireviewDeadlineSoft,
        bool iisBeforeHardReviewDeadline,
        Date& ireviewDeadlineHard,
        bool iisBeforeDiscussDeadline,
        Date& idiscussDeadline,
        int ireviewersPerPaper,
        int ipostWordLimit)
    {
  	    isActive = iisActive;
  	    title = ititle;
  	    confID = iconfID;
  	    topic = itopic;
  	    description = idescription;
  	    location = ilocation;
  	    keywords = ikeywords;
  	    isBeforePaperDeadline = iisBeforePaperDeadline;
  	    paperDeadline = ipaperDeadline;
  	    isBeforeAllocationDate = iisBeforeAllocationDate;
  	    allocationDate = iallocationDate;
  	    isBeforeSoftReviewDeadline = iisBeforeSoftReviewDeadline;
  	    reviewDeadlineSoft = ireviewDeadlineSoft;
  	    isBeforeHardReviewDeadline = iisBeforeHardReviewDeadline;
  	    reviewDeadlineHard = ireviewDeadlineHard;
  	    isBeforeDiscussDeadline = iisBeforeDiscussDeadline;
  	    discussDeadline = idiscussDeadline;
  	    reviewersPerPaper = ireviewersPerPaper;
  	    postWordLimit = ipostWordLimit;
    }

// Conference ID not known
    Conference(
    bool iisActive,
    std::string& ititle,
    std::string& itopic,
    std::string& idescription,
    std::string& ilocation,
    std::vector<std::string>& ikeywords,
    bool iisBeforePaperDeadline,
    Date& ipaperDeadline,
    bool iisBeforeAllocationDate,
    Date& iallocationDate,
    bool iisBeforeSoftReviewDeadline,
    Date& ireviewDeadlineSoft,
    bool iisBeforeHardReviewDeadline,
    Date& ireviewDeadlineHard,
    bool iisBeforeDiscussDeadline,
    Date& idiscussDeadline,
    int ireviewersPerPaper,
    int ipostWordLimit)
    {
  	    isActive = iisActive;
  	    title = ititle;
  	    topic = itopic;
  	    description = idescription;
  	    location = ilocation;
  	    keywords = ikeywords;
  	    isBeforePaperDeadline = iisBeforePaperDeadline;
  	    paperDeadline = ipaperDeadline;
  	    isBeforeAllocationDate = iisBeforeAllocationDate;
  	    allocationDate = iallocationDate;
  	    isBeforeSoftReviewDeadline = iisBeforeSoftReviewDeadline;
  	    reviewDeadlineSoft = ireviewDeadlineSoft;
  	    isBeforeHardReviewDeadline = iisBeforeHardReviewDeadline;
  	    reviewDeadlineHard = ireviewDeadlineHard;
  	    isBeforeDiscussDeadline = iisBeforeDiscussDeadline;
  	    discussDeadline = idiscussDeadline;
  	    reviewersPerPaper = ireviewersPerPaper;
  	    postWordLimit = ipostWordLimit;
    }

    bool isActive;
    std::string title;
    int confID;
    std::string topic;
    std::string description;
    std::string location;
    std::vector<std::string> keywords;
    bool isBeforePaperDeadline;
    Date paperDeadline;
    bool isBeforeAllocationDate;
    Date allocationDate;
    bool isBeforeSoftReviewDeadline;
    Date reviewDeadlineSoft;
    bool isBeforeHardReviewDeadline;
    Date reviewDeadlineHard;
    bool isBeforeDiscussDeadline;
    Date discussDeadline;
    int reviewersPerPaper;
    int postWordLimit;

};

#endif
