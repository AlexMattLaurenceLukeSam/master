#ifndef PAPER_SUMMARY_H
#define PAPER_SUMMARY_H

#include <QString>
#include <QDataStream>
#include <string>

struct PaperSummary 
{
	PaperSummary() {}

	PaperSummary(int ipaperID, const std::string& ipaperName)
    {
	    paperID = ipaperID;
        paperName = ipaperName;
	}

	int paperID = 0;
	std::string paperName;
};

	inline QDataStream& operator<<(QDataStream& out, PaperSummary* paps)
        {
           QString tempQstring;
           out << paps->paperID;
           tempQstring = QString::fromStdString(paps->paperName);
           out << tempQstring;
           return out;
        }
        
        inline QDataStream& operator<<(QDataStream& out, PaperSummary& paps)
        {
           QString tempQstring;
           out << paps.paperID;
           tempQstring = QString::fromStdString(paps.paperName);
           out << tempQstring;
           return out;
        }
        
        inline QDataStream& operator>>(QDataStream& in, PaperSummary* paps)
        {
           QString tempQstring;
           in >> paps->paperID;
           in >> tempQstring;
           paps->paperName = tempQstring.toStdString();
           return in;
        }
        
        inline QDataStream& operator>>(QDataStream& in, PaperSummary& paps)
        {
           QString tempQstring;
           in >> paps.paperID;
           in >> tempQstring;
           paps.paperName = tempQstring.toStdString();
           return in;
        }

#endif
