#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H
#include "Conference.hpp"

struct ConferenceManager {
  ConferenceManager() {temp = NULL;}
  ConferenceManager(Conference* itemp) : temp(itemp) { }
  ~ConferenceManager() {delete temp;}

  void createConference();
  void removeConference();
  void listConferences();
  void viewConference();
  void editConference();
  void addKWords();

  Conference* temp;

};
#endif
