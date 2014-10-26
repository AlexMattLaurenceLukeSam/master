#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.hpp"
#include "../Database/Database.hpp"

#include <string>
#include <vector>

class UserManager {
public:
  UserManager() { }
  UserManager(User* icurrentUser,
              Database* idatabase) : 
              currentUser(icurrentUser),
              database(idatabase)
              { }
  ~UserManager() { if(currentUser != nullptr)
                     delete currentUser;}

  User* getCurrentUser() {return currentUser;}
  void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}
  Database* getDatabase() {return database;}
  void setDatabase(Database* idatabase) {database = idatabase;}
  void addUser() 
  {
    db->putUser(currentUser->name, currentUser);
  }
  void modifyUser()
  {
    addUser(); 
  }
  
  //bool deleteUser(int);
  void sendUser();
  void sendUserBatch();
  void fetchUser(std::string);
  std:vector<User> getAllUsers();


private:
 User* currentUser{nullptr};
 Database* database{nullptr};
};
#endif
