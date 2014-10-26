#ifndef PAPER_SUMMARY_H
#define PAPER_SUMMARY_H
#include <string>
struct PaperSummary {
PaperSummary(int ipaperID, const std::string& ipaperName) :
paperID(ipaperID), paperName(ipaperName)
{ }
int paperID{0};
std::string paperName{""};
};
#endif
