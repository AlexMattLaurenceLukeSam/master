#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>

struct UserManager {
  UserManager() {temp = NULL;}
  UserManager(User* itemp) : temp(itemp) { }
  ~UserManager() { if(temp != nullptr)
                     delete temp;}
  User* temp{nullptr};
  void addUser();
  void modifyUser();
  bool deleteUser(int);
  void sendUser();
  void sendUserBatch();
  bool fetchUser(std::string, std::string);


private:
 void fetchUser(int);
};
#endif
