#ifndef PAPER_SUMMARY_H
#define PAPER_SUMMARY_H
#include <string>
struct PaperSummary {
PaperSummary(int ipaperId, const std::string& ipaperName) :
paperId(ipaperId), paperName(ipaperName)
{ }
int paperID{0};
std::string paperName{""};
};
#endif
