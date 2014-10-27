#ifndef PERSONAL_INFO_H 
#define PERSONAL_INFO_H

#include <string>
#include <QString>
#include <QDataStream>
#include <vector>


struct PersonalInfo {
  PersonalInfo() {}
  
  PersonalInfo(
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         int iinfoID
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         infoID(iinfoID)
         { }

  PersonalInfo(
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone)
         { }
  int infoID{0};
  std::string name{""};
  std::string email{""};
  std::string organisation{""};
  std::string phone{""};
  
};

  
  inline QDataStream& operator<<(QDataStream& out, PersonalInfo* pers)
  {
     QString tempQstring;
     out << pers->infoID;
     tempQstring = QString::fromStdString(pers->name);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers->email);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers->organisation);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers->phone);
     out << tempQstring;
     return out;
  }
  
  inline QDataStream& operator<<(QDataStream& out, PersonalInfo& pers)
  {
     QString tempQstring;
     out << pers.infoID;
     tempQstring = QString::fromStdString(pers.name);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers.email);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers.organisation);
     out << tempQstring;
     tempQstring = QString::fromStdString(pers.phone);
     out << tempQstring;
     return out;
  }
  
  inline QDataStream& operator>>(QDataStream& in, PersonalInfo* pers)
  {
     QString tempQstring;
     in >> pers->infoID;
     in >> tempQstring;
     pers->name = tempQstring.toStdString();
     in >> tempQstring;
     pers->email = tempQstring.toStdString();
     in >> tempQstring;
     pers->organisation = tempQstring.toStdString();
     in >> tempQstring;
     pers->phone = tempQstring.toStdString();
     return in;
  }
  
  inline QDataStream& operator>>(QDataStream& in, PersonalInfo& pers)
  {
     QString tempQstring;
     in >> pers.infoID;
     in >> tempQstring;
     pers.name = tempQstring.toStdString();
     in >> tempQstring;
     pers.email = tempQstring.toStdString();
     in >> tempQstring;
     pers.organisation = tempQstring.toStdString();
     in >> tempQstring;
     pers.phone = tempQstring.toStdString();
     return in;
  }


#endif
