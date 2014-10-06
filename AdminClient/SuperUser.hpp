#include <string>

Class SuperUser {
public:
  SuperUser(const std::string& iuserName,
    const std::string& ipassword) :
    userName(iuserName),
    password(ipassword)
    { }


  void view()
  changeDetails()
  void getPassword(return password;)
  setPassword(const std::string& ipassword) {password = ipassword;}

  std::string userName;

private:
  std::string password;
};
