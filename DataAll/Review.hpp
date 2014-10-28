#ifndef REVIEW_H
#define REVIEW_H

struct Review 
{
    Review()
    {
        reportID = 0;
        paperID = 0;
        reviewerID = 0;
        overall = 0;
        confidence = 0;
        relevance = 0;
        originality = 0;
        significance = 0;
        presentation = 0;
        techQuality = 0;
        evaluation = 0;
        commentsStrength = "";
        commentsWeakness = "";
        commentsSuggestions = "";
        commentsShortPaper = "";
        commentsBestAward = "";
    }
    
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
        const std::string& icommentsBestAward)
    {
        paperID = ipaperID;
        reviewerID = ireviewerID;
        overall = ioverall;
        confidence = iconfidence;
        relevance = irelevance;
        originality = ioriginality;
        significance = isignificance;
        presentation = ipresentation;
        techQuality = itechQuality;
        evaluation = ievaluation;
        commentsStrength = icommentsStrength;
        commentsWeakness = icommentsWeakness;
        commentsSuggestions = icommentsSuggestions;
        commentsShortPaper = icommentsShortPaper;
        commentsBestAward = icommentsBestAward;
    }
    
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
        const std::string& icommentsBestAward)
    {
        reportID = ireportID;
        paperID = ipaperID;
        reviewerID = ireviewerID;
        overall = ioverall;
        confidence = iconfidence;
        relevance = irelevance;
        originality = ioriginality;
        significance = isignificance;
        presentation = ipresentation;
        techQuality = itechQuality;
        evaluation = ievaluation;
        commentsStrength = icommentsStrength;
        commentsWeakness = icommentsWeakness;
        commentsSuggestions = icommentsSuggestions;
        commentsShortPaper = icommentsShortPaper;
        commentsBestAward = icommentsBestAward;
    }

    int reportID;
    int paperID;
    int reviewerID;
    int overall;
    int confidence;
    int relevance;
    int originality;
    int significance;
    int presentation;
    int techQuality;
    int evaluation;
    std::string commentsStrength;
    std::string commentsWeakness;
    std::string commentsSuggestions;
    std::string commentsShortPaper;
    std::string commentsBestAward;

};
#endif
