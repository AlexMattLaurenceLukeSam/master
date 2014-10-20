#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "User.hpp"

struct UserManager {
  UserManager() { }
  UserManager(User* itemp) : temp(itemp) { }
  ~UserManager() { if(temp != nullptr)
                     delete temp;}
  User* temp{nullptr};
  void createUser();
  void removeUser();
  void listUsers();
  void viewUser();
  void editUser();

};
#endif
