#include <string>

Struct UserManager {
  UserManager() {temp = NULL;}
  UserManager(User* itemp) : temp(itemp) { }
  ~UserManager() { delete temp;}
  User* temp;
  addUser()
  modifyUser()
  bool deleteUser(int)
  sendUser()
  sendUserBatch()
  bool fetchUser(std::string, std::string)


private:
  fetchUser(int)
};
