#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H

#include "../DataAll/Paper.hpp"
#include "../Database/Database.hpp"

class PaperManager {
public:
  PaperManager() { }
  PaperManager(Paper* icurrentPaper, 
  Database* idatabase) : 
  currentPaper(icurrentPaper),
  database(idatabase)
  { }
  ~PaperManager() { if(currentPaper != nullptr)
                      delete currentPaper;}

  Paper* getCurrentPaper() {return currentPaper;}
  void setCurrentPaper(Paper* icurrentPaper) {currentPaper = icurrentPaper;}
  Database* getDatabase() {return database;}
  void setDatabase(Database* idatabase) {database = idatabase;}
  void addPaper();
  void modifyPaper(int);
  //bool deleteDiscPost(int);
  void modifyDiscPost(int);
  //bool deleteReview(int);
  void modifyReview(int);
  //bool deletePaper(int);
  void sendPaper();
  void sendPaperSummaryBatch(int);
  void sendAuthoredPaper(int);
  void sendPaperSummariesToReview(int);

private:
void fetchPaper(int);
Paper* currentPaper{nullptr};
Database* database{nullptr};
};
#endif
