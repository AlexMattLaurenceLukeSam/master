#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "User.hpp"

Struct UserManager {
  UserManager() {temp = NULL;}
  UserManager(User* itemp) : temp(itemp) { }
  ~UserManager() { delete temp;}
  User* temp;
  createUser()
  removeUser()
  listUsers()
  viewUser()
  editUser()

};
#endif
