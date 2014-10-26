#ifndef REVIEW_H
#define REVIEW_H

struct Paper;

struct Review {
  Review() { }
  Review(int ipaperID,
    int ireviewerID,
    int ioverall,
    int iconfidence,
    int irelevance,
    int ioriginality,
    int isignificance,
    int ipresentation,
    int itechQuality,
    int ievaluation,
    const std::string& icommentsStrength,
    const std::string& icommentsWeakness,
    const std::string& icommentsSuggestions,
    const std::string& icommentsShortPaper,
    const std::string& icommentsBestAward):
    paperID(ipaperID),
    reviewerID(ireviewerID),
    overall(ioverall),
    confidence(iconfidence),
    relevance(irelevance),
    originality(ioriginality),
    significance(isignificance),
    presentation(ipresentation),
    techQuality(itechQuality),
    evaluation(ievaluation),
    commentsStrength(icommentsStrength),
    commentsWeakness(icommentsWeakness),
    commentsSuggestions(icommentsSuggestions),
    commentsShortPaper(icommentsShortPaper),
    commentsBestAward(icommentsBestAward)
    { }

  Review(int ireportID,
    int ipaperID,
    int ireviewerID,
    int ioverall,
    int iconfidence,
    int irelevance,
    int ioriginality,
    int isignificance,
    int ipresentation,
    int itechQuality,
    int ievaluation,
    const std::string& icommentsStrength,
    const std::string& icommentsWeakness,
    const std::string& icommentsSuggestions,
    const std::string& icommentsShortPaper,
    const std::string& icommentsBestAward):
    reportID(ireportID),
    paperID(ipaperID),
    reviewerID(ireviewerID),
    overall(ioverall),
    confidence(iconfidence),
    relevance(irelevance),
    originality(ioriginality),
    significance(isignificance),
    presentation(ipresentation),
    techQuality(itechQuality),
    evaluation(ievaluation),
    commentsStrength(icommentsStrength),
    commentsWeakness(icommentsWeakness),
    commentsSuggestions(icommentsSuggestions),
    commentsShortPaper(icommentsShortPaper),
    commentsBestAward(icommentsBestAward)
    { }

  int reportID{0};
  int paperID{0};
  int reviewerID{0};
  int overall{0};
  int confidence{0};
  int relevance{0};
  int originality{0};
  int significance{0};
  int presentation{0};
  int techQuality{0};
  int evaluation{0};
  std::string commentsStrength{""};
  std::string commentsWeakness{""};
  std::string commentsSuggestions{""};
  std::string commentsShortPaper{""};
  std::string commentsBestAward{""};

};
#endif
