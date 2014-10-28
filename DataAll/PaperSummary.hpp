#ifndef PAPER_SUMMARY_H
#define PAPER_SUMMARY_H

#include <string>

struct PaperSummary 
{
    PaperSummary()
    {
        paperID = 0;
        paperName = "";
    }

    PaperSummary(int ipaperID, const std::string& ipaperName)
    {
        paperID = ipaperID;
    paperName = ipaperName;
    }

    int paperID;
    std::string paperName;
};

#endif
