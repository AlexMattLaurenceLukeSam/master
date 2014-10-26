//incomplete
#ifndef PAPER_H
#define PAPER_H

#include "../DataAll/Discussion.hpp"
#include "../DataAll/Review.hpp"
//#include "User.hpp"
#include "../DataAll/PersonalInfo.hpp"

#include <QString>
#include <QVector>
#include <QDataStream>
#include <vector>

struct Paper {

    Paper() { }
    Paper(const int ipaperID,
      const int iconfID,
      const int ileadAuthorID,
      const std::string& ititle,
      const std::string& iabstract,
      const std::vector<PersonalInfo>& iauthors,
      const std::vector<std::string>& ikeywords,
      const std::string& iconfKeyword,
      const std::vector<Review>& ireviews,
      const Discussion& idiscussion)
      :
      paperID(ipaperID),
      confID(iconfID),
      leadAuthorID(ileadAuthorID),
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      confKeyword(iconfKeyword),
      reviews(ireviews),
      discussion(idiscussion)
      { }

    Paper(
      const int iconfID,
      const int ileadAuthorID,
      const std::string& ititle,
      const std::string& iabstract,
      const std::vector<PersonalInfo>& iauthors,
      const std::vector<std::string>& ikeywords,
      const std::string& iconfKeyword)
      :
      confID(iconfID),
      leadAuthorID(ileadAuthorID),
      title(ititle),
      abstract(iabstract),
      authors(iauthors),
      keywords(ikeywords),
      confKeyword(iconfKeyword)
      { }
    // no assignment operator or copy constructor deemed necessary at this point
    int paperID{0};
    int confID{0};
    int leadAuthorID{0};
    std::string title{""};
    std::string abstract{""};
    std::vector<PersonalInfo> authors;
    std::vector<std::string> keywords;
    std::string confKeyword;
    Discussion discussion;
    std::vector<Review> reviews;
    
    inline QDataStream& operator<<(QDataStream& out, Paper* pap)
    {
        QString tempQstring;
        QVector<QString> tempQvector;
        QVector<PersonalInfo> tempQvectorP;
        QVector<Review> tempQvectorR;
        out << pap->paperID;
        out << pap->confID;
        out << pap->leadAuthorID;
        tempQstring = QString::fromStdString(pap->title);
        out << tempQstring;
        tempQstring = QString::fromStdString(pap->abstract);
        out << tempQstring;
        for (unsigned int i = 0; i < pap->authors.size(); ++i)
        {
          tempQvectorP.append(pap->authors[i]);
        }
        out << tempQvectorP;
        tempQvectorP.clear();
        for (unsigned int i = 0; i < pap->keywords.size(); ++i)
        {
          tempQstring = QString::fromStdString(conf->keywords[i]);
          tempQvector.append(tempQstring);
        }
        out << tempQvector;
        tempQvector.clear();
        tempQstring = QString::fromStdString(pap->confKeyword);
        out << tempQstring;
        out << pap->dicussion;
        for (unsigned int i = 0; i < pap->reviews.size(); ++i)
        {
          tempQvectorR.append(pap->reviews[i]);
        }
        out << tempQvectorR;
        tempQvectorR.clear();
        return out;
    }
    
    inline QDataStream& operator<<(QDataStream& out, Paper& pap)
    {
        QString tempQstring;
        QVector<QString> tempQvector;
        QVector<PersonalInfo> tempQvectorP;
        QVector<Review> tempQvectorR;
        out << pap.paperID;
        out << pap.confID;
        out << pap.leadAuthorID;
        tempQstring = QString::fromStdString(pap.title);
        out << tempQstring;
        tempQstring = QString::fromStdString(pap.abstract);
        out << tempQstring;
        for (unsigned int i = 0; i < pap.authors.size(); ++i)
        {
          tempQvectorP.append(pap.authors[i]);
        }
        out << tempQvectorP;
        tempQvectorP.clear();
        for (unsigned int i = 0; i < pap.keywords.size(); ++i)
        {
          tempQstring = QString::fromStdString(conf.keywords[i]);
          tempQvector.append(tempQstring);
        }
        out << tempQvector;
        tempQvector.clear();
        tempQstring = QString::fromStdString(pap.confKeyword);
        out << tempQstring;
        out << pap.dicussion;
        for (unsigned int i = 0; i < pap.reviews.size(); ++i)
        {
          tempQvectorR.append(pap.reviews[i]);
        }
        out << tempQvectorR;
        tempQvectorR.clear();
        return out;
    }
    
    inline QDataStream& operator>>(QDataStream& in, Paper* pap)
    {
        QString tempQstring;
        QVector<QString> tempQvector;
        QVector<PersonalInfo> tempQvectorP;
        QVector<Review> tempQvectorR;
        in >> pap->paperID;
        in >> pap->confID;
        in >> pap->leadAuthorID;
        in >> tempQstring;
        pap->title = tempQstring.toStdString();
        in >> tempQstring;
        pap->abstract = tempQstring.toStdString();
        in >> tempQvectorP;
        for (unsigned int i = 0; i < tempQvectorP.size(); ++i)
          pap->authors.push_back(tempQvectorP[i]);
        tempQvector.clear();
        in >> tempQvector;
        for (unsigned int i = 0; i < tempQvector.size(); ++i)
          pap->keywords.push_back(tempQvector[i].toStdString());
        tempQvector.clear();
        in >> tempQstring;
        pap->confKeyword = tempQstring.toStdString();
        in >> pap->discussion;
        in >> tempQvectorR;
        for (unsigned int i = 0; i < tempQvectorR.size(); ++i)
          pap->reviews.push_back(tempQvectorR[i]);
        tempQvector.clear();
    }
    
    inline QDataStream& operator>>(QDataStream& in, Paper& pap)
    {
        QString tempQstring;
        QVector<QString> tempQvector;
        QVector<PersonalInfo> tempQvectorP;
        QVector<Review> tempQvectorR;
        in >> pap.paperID;
        in >> pap.confID;
        in >> pap.leadAuthorID;
        in >> tempQstring;
        pap.title = tempQstring.toStdString();
        in >> tempQstring;
        pap.abstract = tempQstring.toStdString();
        in >> tempQvectorP;
        for (unsigned int i = 0; i < tempQvectorP.size(); ++i)
          pap.authors.push_back(tempQvectorP[i]);
        tempQvector.clear();
        in >> tempQvector;
        for (unsigned int i = 0; i < tempQvector.size(); ++i)
          pap.keywords.push_back(tempQvector[i].toStdString());
        tempQvector.clear();
        in >> tempQstring;
        pap.confKeyword = tempQstring.toStdString();
        in >> pap.discussion;
        in >> tempQvectorR;
        for (unsigned int i = 0; i < tempQvectorR.size(); ++i)
          pap.reviews.push_back(tempQvectorR[i]);
        tempQvector.clear();
    }
};
#endif
