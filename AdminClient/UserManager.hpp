#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "User.hpp"

class UserManager {
public:
  UserManager() { }
  UserManager(User* icurrentUser) : currentUser(icurrentUser) { }
  ~UserManager() { if(currentUser != nullptr)
                     delete currentUser;}
  User* getCurrentUser() {return currentUser;}
  void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}  
  void createUser();
  void removeUser();
  void listUsers();
  void viewUser();
  void editUser();
private:  
  User* currentUser{nullptr};

};
#endif
