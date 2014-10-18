#ifndef SUPER_USER_H
#define SUPER_USER_H
#include <string>

Class SuperUser {
public:
  SuperUser(const std::string& iuserName,
    const std::string& ipassword) :
    userName(iuserName),
    password(ipassword)
    { }


  void view()
  void changeDetails()
  void getPassword(return password;)
  void setPassword(const std::string& ipassword) {password = ipassword;}

  std::string userName;

private:
  std::string password;
};
#endif
