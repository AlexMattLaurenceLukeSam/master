#ifndef DISCUSSION_POST_H
#define DISCUSSION_POST_H

#include <QString>
#include <QDataStream>
#include <string>

struct DiscussionPost {
  DiscussionPost() {}

  DiscussionPost(const std::string& icomment,
                 int ireviewerID,
                 int ipostID):
                 comment(icomment),
                 reviewerID(ireviewerID),
                 postID(ipostID)
                 { }

  DiscussionPost(const std::string& icomment,
                 int ireviewerID):
                 comment(icomment),
                 reviewerID(ireviewerID)
                 { }
  
  std::string comment{""};
  int reviewerID{0};
  int postID{0};
};

  inline QDataStream& operator<<(QDataStream& out, DiscussionPost* discp)
  {
    QString tempQstring;
    out << discp->reviewerID;
    out << discp->postID;
    tempQstring = QString::fromStdString(discp->comment);
    out << tempQstring;
    return out;
  }
  
  inline QDataStream& operator<<(QDataStream& out, DiscussionPost& discp)
  {
    QString tempQstring;
    out << discp.reviewerID;
    out << discp.postID;
    tempQstring = QString::fromStdString(discp.comment);
    out << tempQstring;
    return out;
  }
  
  inline QDataStream& operator>>(QDataStream& in, DiscussionPost* discp)
  {
    QString tempQstring;
    in >> discp->reviewerID;
    in >> discp->postID;
    in >> tempQstring;
    discp->comment = tempQstring.toStdString();
    return in;
  }
  
  inline QDataStream& operator>>(QDataStream& in, DiscussionPost& discp)
  {
    QString tempQstring;
    in >> discp.reviewerID;
    in >> discp.postID;
    in >> tempQstring;
    discp.comment = tempQstring.toStdString();
    return in;
  }

#endif
