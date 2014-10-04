Struct Review {
  Review(const std::string& ireviewerName
  int reviewId;
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
  reviewerName(ireviewerName),
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
  commentsBestAward(icommentsBestAward))
  { }
  std::string reviewerName;
  int reviewId;
  int overall;
  int confidence;
  int relevance;
  int originality;
  int significance;
  int presentation;
  int techQuality;
  int evalution;
  std::string commentsStrength;
  std::string commentsWeakness;
  std::string commentsSuggestions;
  std::string commentsShortPaper;
  std::string commentsBestAward;

};
