#ifndef DISCUSSION_H
#define DISCUSSION_H

#include "../DataAll/DiscussionPost.hpp"

#include <list>
#include <QList>
#include <QDataStream>

struct Discussion {
  Discussion() { }
  Discussion(const std::list<DiscussionPost>& idiscussion):
               discussion(idiscussion)
               { }
  Discussion(const Discussion& in) {
    discussion = in.discussion;
  }
  std::list<DiscussionPost> discussion;
};

  inline QDataStream& operator<<(QDataStream& out, Discussion* disc)
  {
    QList<Discussion> tempQList;
     for (unsigned int i = 0; i < disc->discussion.size(); ++i)
       tempQList.append(disc->discussion[i]);
     out << tempQList;
     tempQList.clear();

     return out;
  }
  
  inline QDataStream& operator<<(QDataStream& out, Discussion& disc)
  {
    QList<Discussion> tempQList;
     for (unsigned int i = 0; i < disc.discussion.size(); ++i)
       tempQList.append(QString::fromStdString(disc.discussion[i]));
     out << tempQList;
     tempQList.clear();
     return out;
  }
  
  inline QDataStream& operator>>(QDataStream& in, Discussion* disc)
  {
    QList<Discussion> tempQList;
    in >> tempQList;
    for (unsigned int i = 0; i < tempQList.size(); ++i)
      disc->discussion.push_back(tempQList[i].toStdString());
    tempQList.clear();
    return in;
  }
  
  inline QDataStream& operator>>(QDataStream& in, Discussion& disc)
  {
    QList<Discussion> tempQList;
    in >> tempQList;
    for (unsigned int i = 0; i < tempQList.size(); ++i)
      disc.discussion.push_back(tempQList[i].toStdString());
    tempQList.clear();
    return in;
  }


#endif
