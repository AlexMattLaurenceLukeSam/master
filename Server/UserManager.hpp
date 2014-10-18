#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>

Struct UserManager {
  UserManager() {temp = NULL;}
  UserManager(User* itemp) : temp(itemp) { }
  ~UserManager() { delete temp;}
  User* temp;
  void addUser()
  void modifyUser()
  bool deleteUser(int)
  void sendUser()
  void sendUserBatch()
  bool fetchUser(std::string, std::string)


private:
  fetchUser(int)
};
#endif
