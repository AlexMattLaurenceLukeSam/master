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
