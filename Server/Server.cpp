//NEW MAIN FOR SERVER

#include "ConferenceManager.hpp"
#include "PaperManager.hpp"
#include "UserManager.hpp"

int main()
{
  Database* db;
  PaperManager* pm;
  ConferenceManager* cm;
  UserManager* um;
  
  
  db = new Database(/*CONSTRUCTOR*/);
  pm = new PaperManager(nullptr, db);
  cm = new ConferenceManager(std::vector<Conference*>(), db, nullptr);
  um = new UserManager(nullptr, db);
  
  delete um;
  delete cm;
  delete pm;
  delete db;

  return 0;
}
