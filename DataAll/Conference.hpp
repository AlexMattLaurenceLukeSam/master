#ifndef CONFERENCE_H
#define CONFERENCE_H

#include "../DataAll/Date.hpp"

#include <string>
#include <vector>
#include <QString>
#include <QVector>
#include <QDataStream>

struct Conference {
  Conference() {}
  
  Conference(bool iisActive,
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

Conference(bool iisActive, //no confID
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
  int ipostWordLimit):
  isActive(iisActive),
  title(ititle),
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
  int confID{0};
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

inline QDataStream& operator<<(QDataStream& out, Conference* conf)
{
    QString tempQstring;
    QVector<QString> tempQvector;
    
    out << conf->isActive;
    tempQstring = QString::fromStdString(conf->title);
    out << tempQstring;
    out << conf->confID;
    tempQstring = QString::fromStdString(conf->topic);
    out << tempQstring;
    tempQstring = QString::fromStdString(conf->description);
    out << tempQstring;
    tempQstring = QString::fromStdString(conf->location);
    out << tempQstring;
    
    for (unsigned int i = 0; i < conf->keywords.size(); ++i)
    {
        tempQstring = QString::fromStdString(conf->keywords[i]);
        tempQvector.append(tempQstring);
    }
    out << tempQvector;
    tempQvector.clear();
  
    out << conf->isBeforePaperDeadline;
    out << conf->paperDeadline;
    out << conf->isBeforeAllocationDate;
    out << conf->allocationDate;
    out << conf->isBeforeSoftReviewDeadline;
    out << conf->reviewDeadlineSoft;
    out << conf->isBeforeHardReviewDeadline;
    out << conf->reviewDeadlineHard;
    out << conf->isBeforeDiscussDeadline;
    out << conf->discussDeadline;
    out << conf->reviewersPerPaper;
    out << conf->postWordLimit;
    return out;
}

inline QDataStream& operator<<(QDataStream& out, Conference& conf)
{
    QString tempQstring;
    QVector<QString> tempQvector;
    
    out << conf.isActive;
    tempQstring = QString::fromStdString(conf.title);
    out << tempQstring;
    out << conf.confID;
    tempQstring = QString::fromStdString(conf.topic);
    out << tempQstring;
    tempQstring = QString::fromStdString(conf.description);
    out << tempQstring;
    tempQstring = QString::fromStdString(conf.location);
    out << tempQstring;
    
    for (unsigned int i = 0; i < conf.keywords.size(); ++i)
        tempQvector.append(QString::fromStdString(conf.keywords[i]));
    out << tempQvector;
    tempQvector.clear();
  
    out << conf.isBeforePaperDeadline;
    out << conf.paperDeadline;
    out << conf.isBeforeAllocationDate;
    out << conf.allocationDate;
    out << conf.isBeforeSoftReviewDeadline;
    out << conf.reviewDeadlineSoft;
    out << conf.isBeforeHardReviewDeadline;
    out << conf.reviewDeadlineHard;
    out << conf.isBeforeDiscussDeadline;
    out << conf.discussDeadline;
    out << conf.reviewersPerPaper;
    out << conf.postWordLimit;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Conference* conf)
{
    QString tempQstring;
    QVector<QString> tempQvector;
    
    in >> conf->isActive;
    in >> tempQstring;
    conf->title = tempQstring.toStlString();
    in >> conf->confID;
    tempQstring = QString::fromStdString(conf->topic);
    in >> tempQstring;
    tempQstring = QString::fromStdString(conf->description);
    in >> tempQstring;
    tempQstring = QString::fromStdString(conf->location);
    in >> tempQstring;
    
    in >>  tempQvector;
    for (unsigned int i = 0; i < tempQvector.size(); ++i)
        conf->keywords.push_back(tempQvector[i].toStdString());
    tempQvector.clear();
  
    in >>  conf->isBeforePaperDeadline;
    in >>  conf->paperDeadline;
    in >>  conf->isBeforeAllocationDate;
    in >>  conf->allocationDate;
    in >>  conf->isBeforeSoftReviewDeadline;
    in >>  conf->reviewDeadlineSoft;
    in >>  conf->isBeforeHardReviewDeadline;
    in >>  conf->reviewDeadlineHard;
    in >>  conf->isBeforeDiscussDeadline;
    in >>  conf->discussDeadline;
    in >>  conf->reviewersPerPaper;
    in >>  conf->postWordLimit;
    return in;
}

inline QDataStream& operator>>(QDataStream& in, Conference& conf)
{
    QString tempQstring;
    QVector<QString> tempQvector;
    
    in >> conf.isActive;
    tempQstring = QString::fromStdString(conf.title);
    in >> tempQstring;
    in >> conf.confID;
    tempQstring = QString::fromStdString(conf.topic);
    in >> tempQstring;
    tempQstring = QString::fromStdString(conf.description);
    in >> tempQstring;
    tempQstring = QString::fromStdString(conf.location);
    in >> tempQstring;
    
    in >>  tempQvector;
    for (unsigned int i = 0; i < tempQvector.size(); ++i)
        conf.keywords.push_back(tempQvector[i].toStdString());
    tempQvector.clear();
  
    in >>  conf.isBeforePaperDeadline;
    in >>  conf.paperDeadline;
    in >>  conf.isBeforeAllocationDate;
    in >>  conf.allocationDate;
    in >>  conf.isBeforeSoftReviewDeadline;
    in >>  conf.reviewDeadlineSoft;
    in >>  conf.isBeforeHardReviewDeadline;
    in >>  conf.reviewDeadlineHard;
    in >>  conf.isBeforeDiscussDeadline;
    in >>  conf.discussDeadline;
    in >>  conf.reviewersPerPaper;
    in >>  conf.postWordLimit;
}

#endif
