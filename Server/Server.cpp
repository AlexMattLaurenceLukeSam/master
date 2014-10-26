//NEW MAIN FOR SERVER

#include "PaperManager.hpp"
#include "ConferenceManager.hpp"




int main()
{
  Database* db;
  PaperManager* pm;
  ConferenceManager* cm;
  
  
  db = new Database(/*CONSTRUCTOR*/);
  pm = new PaperManager(nullptr, db);
  cm = new ConferenceManager(std::vector<Conference*>(), db, nullptr);
  



  return 0;
}
