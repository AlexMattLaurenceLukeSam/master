#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H

#include "Conference.hpp"

class ConferenceManager {
public:
  ConferenceManager(std::vector<Conference*> iconferences) : conferences(iconferences) { }
  ~ConferenceManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
}

  std::vector<Conference*> getConferences() {return conferences;}
  void setConferences(const std::vector<Conference*>& iconferences) {conferences = iconferences;}
  void addConference();
  void modifyConference(int);
  bool deleteConference(int);
  void sendConference();
  void sendConferenceBatch();
  void checkAllDeadlines();



private:
  void fetchConference(int);
  std::vector<Conference*> conferences;
};
#endif
