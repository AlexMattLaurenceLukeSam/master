#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>

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
  void addUser();
  void modifyUser();
  bool deleteUser(int);
  void sendUser();
  void sendUserBatch();
  bool fetchUser(std::string, std::string);


private:
 void fetchUser(int);
 User* currentUser{nullptr};
 Database* database{nullptr};
};
#endif
