#ifndef REVIEW_H
#define REVIEW_H

//#include "Paper.hpp"

class Paper;

struct Review {
  Review() { }
  Review(Paper* ipaper,
    int ireviewerID,
    int ioverall,
    int iconfidence,
    int irelevance,
    int ioriginality,
    int isignificance,
    int ipresentation,
    int itechQuality,
    int ievalution,
    const std::string& icommentsStrength,
    const std::string& icommentsWeakness,
    const std::string& icommentsSuggestions,
    const std::string& icommentsShortPaper,
    const std::string& icommentsBestAward):
    paper(ipaper),
    reviewerID(ireviewerID),
    overall(ioverall),
    confidence(iconfidence),
    relevance(irelevance),
    originality(ioriginality),
    significance(isignificance),
    presentation(ipresentation),
    techQuality(itechQuality),
    evalution(ievalution),
    commentsStrength(icommentsStrength),
    commentsWeakness(icommentsWeakness),
    commentsSuggestions(icommentsSuggestions),
    commentsShortPaper(icommentsShortPaper),
    commentsBestAward(icommentsBestAward)
    { }
  Paper* paper{nullptr};
  int reviewerID{0};
  int overall{0};
  int confidence{0};
  int relevance{0};
  int originality{0};
  int significance{0};
  int presentation{0};
  int techQuality{0};
  int evalution{0};
  std::string commentsStrength{""};
  std::string commentsWeakness{""};
  std::string commentsSuggestions{""};
  std::string commentsShortPaper{""};
  std::string commentsBestAward{""};

};
#endif
