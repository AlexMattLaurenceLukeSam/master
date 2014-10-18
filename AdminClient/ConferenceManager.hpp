#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H
#include "Conference.hpp"

Struct ConferenceManager {
  ConferenceManager() {temp = NULL;}
  ConferenceManager(Conference* itemp) : temp(itemp) { }
  ~ConferenceManager() {delete temp;}

  createConference()
  removeConference()
  listConferences()
  viewConference()
  editConference()
  addKWords()

  Conference* temp;

};
#endif
