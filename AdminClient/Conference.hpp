#ifndef CONFERENCE_H
#define CONFERENCE_H
#include "Date.hpp"

#include <string>
#include <vector>

struct Conference {
  Conference(bool iisActive,
  const std::string& ititle,
  const std::string& iconfID,
  const std::string& itopic,
  const std::string& idescription,
  const std::string& ilocation,
  const std::vector<std::string>& ikeywords,
  bool iisBeforePaperDeadline,
  const Date& ipaperDeadline,
  bool iisBeforeAllocationDate,
  const Date& iallocationDate,
  bool iisBeforeSoftReviewDeadline,
  const Date& ireviewDeadlineSoft,
  bool iisBeforeHardReviewDeadline,
  const Date& ireviewDeadlineHard,
  bool iisBeforeDiscussDeadline,
  const Date& idiscussDeadline,
  int ireviewersPerPaper,
  int ipostWordLimit):
  isActive(iisActive),
  title(ititle),
  confID(iconfID),
  topic(itopic),
  description(idescription),
  location(ilocation),
  keywords(ikeywords),
  isBeforePaperDeadline(iisBeforePaperDeadline),
  paperDeadline(ipaperDeadline),
  isBeforeAllocationDate(iisBeforeAllocationDate),
  allocationDate(iallocationDate),
  isBeforeSoftReviewDeadline(iisBeforeSoftReviewDeadline),
  reviewDeadlineSoft(ireviewDeadlineSoft),
  isBeforeHardReviewDeadline(iisBeforeHardReviewDeadline),
  reviewDeadlineHard(ireviewDeadlineHard),
  isBeforeDiscussDeadline(iisBeforeDiscussDeadline),
  discussDeadline(idiscussDeadline),
  reviewersPerPaper(ireviewersPerPaper),
  postWordLimit(ipostWordLimit)
  { }

  bool isActive;
  std::string title{""};
  std::string confID{""};
  std::string topic{""};
  std::string description{""};
  std::string location{""};
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
  int reviewersPerPaper{0};
  int postWordLimit{0};

};
#endif
