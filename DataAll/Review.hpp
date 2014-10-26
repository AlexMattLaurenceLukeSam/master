#ifndef REVIEW_H
#define REVIEW_H

#include <QString>
#include <QVector>
#include <QDataStream>

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

  inline QDataStream& operator<<(QDataStream& out, Review* rev)
  {
     QString tempQstring;
     out << rev->reportID;
     out << rev->paperID;
     out << rev->reviewerID;
     out << rev->overall;
     out << rev->confidence;
     out << rev->relevance;
     out << rev->originality;
     out << rev->significance;
     out << rev->presentation;
     out << rev->techQuality;
     out << rev->evaluation;
     tempQstring = QString::fromStdString(rev->commentsStrength);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev->commentsWeakness);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev->commentsSuggestions);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev->commentsShortPaper);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev->commentsBestAward);
     out << tempQstring;
     return out;
  }
  
  inline QDataStream& operator<<(QDataStream& out, Review& rev)
  {
     QString tempQstring;
     out << rev.reportID;
     out << rev.paperID;
     out << rev.reviewerID;
     out << rev.overall;
     out << rev.confidence;
     out << rev.relevance;
     out << rev.originality;
     out << rev.significance;
     out << rev.presentation;
     out << rev.techQuality;
     out << rev.evaluation;
     tempQstring = QString::fromStdString(rev.commentsStrength);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev.commentsWeakness);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev.commentsSuggestions);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev.commentsShortPaper);
     out << tempQstring;
     tempQstring = QString::fromStdString(rev.commentsBestAward);
     out << tempQstring;
     return out;
  }

  inline QDataStream& operator>>(QDataStream& in, Review* rev)
  {
    QString tempQstring;
    in >> rev->reportID;
    in >> rev->paperID;
    in >> rev->reviewerID;
    in >> rev->overall;
    in >> rev->confidence;
    in >> rev->relevance;
    in >> rev->originality;
    in >> rev->significance;
    in >> rev->presentation;
    in >> rev->techQuality;
    in >> rev->evaluation;
    in >> tempQstring;
    rev->commentsStrength = tempQstring.toStdString();
    in >> tempQstring;
    rev->commentsWeakness = tempQstring.toStdString();
    in >> tempQstring;
    rev->commentsSuggestions = tempQstring.toStdString();
    in >> tempQstring;
    rev->commentsShortPaper = tempQstring.toStdString();
    in >> tempQstring;
    rev->commentsBestAward = tempQstring.toStdString();
    return in;
  }
  
  inline QDataStream& operator>>(QDataStream& in, Review& rev)
  {
    QString tempQstring;
    in >> rev.reportID;
    in >> rev.paperID;
    in >> rev.reviewerID;
    in >> rev.overall;
    in >> rev.confidence;
    in >> rev.relevance;
    in >> rev.originality;
    in >> rev.significance;
    in >> rev.presentation;
    in >> rev.techQuality;
    in >> rev.evaluation;
    in >> tempQstring;
    rev.commentsStrength = tempQstring.toStdString();
    in >> tempQstring;
    rev.commentsWeakness = tempQstring.toStdString();
    in >> tempQstring;
    rev.commentsSuggestions = tempQstring.toStdString();
    in >> tempQstring;
    rev.commentsShortPaper = tempQstring.toStdString();
    in >> tempQstring;
    rev.commentsBestAward = tempQstring.toStdString();
    return in;
  }


#endif
