#ifndef CONFERENCE_MANAGER_H
#define CONFERENCE_MANAGER_H

#include "../DataAll/Conference.hpp"
#include "../Database/Database.hpp"

class ConferenceManager {
public:
  ConferenceManager(std::vector<Conference*> iconferences,
                    Conference* icurrentConference,
                    Database* idatabase) :
                    conferences(iconferences), 
                    currentConference(icurrentConference),
                    database(idatabase)
                    { }
  ~ConferenceManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
}

  std::vector<Conference*> getConferences() {return conferences;}
  void setConferences(const std::vector<Conference*>& iconferences) {conferences = iconferences;}
  Conference* getCurrentConference() {return currentConference;}
  void setCurrentConference(Conference* icurrentConference) {currentConference = icurrentConference;}
  Database* getDatabase() {return database;}
  void setDatabase(Database* idatabase) {database = idatabase;}
  void addConference() 
  {
    database->putConf(currentConference->title, currentConference);
  }
  void modifyConference(int confID)
  {
    fetchConference(confID);
    addConference();
  }
  //bool deleteConference(int);
  void sendConference();
  void sendConferenceBatch();
  void checkAllDeadlines();
  void allocatePapers();
  std::vector<Conference> getAllActiveConferences();
  std::vector<Conference> getAllConferences();



private:
  void checkDeadlines(Conference*);
  void fetchConference(int);
  std::vector<Conference*> conferences;
  Conference* currentConference{nullptr};
  Database* database{nullptr};
};
#endif
