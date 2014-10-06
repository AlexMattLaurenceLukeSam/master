#include "Conference.hpp"

Struct ConferenceManager {
  ConferenceManager(std::vector<Conference*> iconferences) : conferences(iconferences) { }
  ~ConferenceManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
}

  addConference()
  modifyConference(int)
  bool deleteConference(int)
  sendConference()
  sendConferenceBatch()
  checkAllDeadlines()

  std::vector<Conference*> conferences;

private:
  fetchConference(int)

};

