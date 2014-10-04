#include "User.hpp"

Struct UserManager {
  UserManager() {temp = NULL;}
  UserManager(User* itemp) : temp(itemp) { }
  User* temp;
};
