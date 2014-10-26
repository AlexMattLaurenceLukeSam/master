//NEW MAIN FOR SERVER

#include "PaperManager.hpp"
#include "ConferenceManager.hpp"




int main()
{
  Database* db;
  PaperManager* pm;
  ConferenceManager* cm;
  
  
  db = new Database(/*CONSTRUCTOR*/);
  pm = new PaperManager(/*CONSTRUCTOR*/);
  cm = new ConferenceManager(/*CONSTRUCTOR*/);
  



  return 0;
}
