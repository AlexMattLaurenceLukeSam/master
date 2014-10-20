#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H
#include "Conference.hpp"

struct ConferenceManager {
  ConferenceManager() { }
  ConferenceManager(Conference* itemp) : temp(itemp) { }
  ~ConferenceManager() { if(temp != nullptr)
                     delete temp;}

  void createConference();
  void removeConference();
  void listConferences();
  void viewConference();
  void editConference();
  void addKWords();

  Conference* temp{nullptr};

};
#endif
