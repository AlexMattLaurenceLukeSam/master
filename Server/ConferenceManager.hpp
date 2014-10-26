#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H

#include "Conference.hpp"
#include "../Database/Database.hpp"

class ConferenceManager {
public:
  ConferenceManager(std::vector<Conference*> iconferences, 
                    Database* idatabase) :
                    conferences(iconferences), 
                    database(idatabase) 
                    { }
  ~ConferenceManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
}

  std::vector<Conference*> getConferences() {return conferences;}
  void setConferences(const std::vector<Conference*>& iconferences) {conferences = iconferences;}
  Database* getDatabase() {return database;}
  void setDatabase(Database* idatabase) {database = idatabase;}
  void addConference();
  void modifyConference(int);
  bool deleteConference(int);
  void sendConference();
  void sendConferenceBatch();
  void checkAllDeadlines();
  void allocatePapers();



private:
  void checkDeadlines(Conference*);
  void fetchConference(int);
  std::vector<Conference*> conferences;
  Database* database{nullptr};
};
#endif
