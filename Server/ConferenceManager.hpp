#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H

#include "Conference.hpp"

struct ConferenceManager {
  ConferenceManager(std::vector<Conference*> iconferences) : conferences(iconferences) { }
  ~ConferenceManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
}

  void addConference();
  void modifyConference(int);
  bool deleteConference(int);
  void sendConference();
  void sendConferenceBatch();
  void checkAllDeadlines();

  std::vector<Conference*> conferences;

private:
  void fetchConference(int);

};
#endif
