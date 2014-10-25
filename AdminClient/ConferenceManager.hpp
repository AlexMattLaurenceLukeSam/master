#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H
#include "Conference.hpp"

class ConferenceManager {
public:
  ConferenceManager() { }
  ConferenceManager(Conference* icurrentConference) : currentConference(icurrentConference) { }
  ~ConferenceManager() { if(currentConference != nullptr)
                     delete currentConference;}

  Conference* getcurrentConference(return currentConference;)
  void setConference(Conference* icurrentConference) {currentConference = icurrentConference;}
  void createConference();
  void removeConference();
  void listConferences();
  void viewConference();
  void editConference();
  void addKWords();
  
  
private:
  Conference* currentConference{nullptr};

};
#endif
