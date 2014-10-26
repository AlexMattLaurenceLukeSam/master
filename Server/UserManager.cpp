#include "UserManager.hpp"

void UserManager::fetchUser(std::string userName)
{
  *currentUser = db->fetchUser(userName);
}

std::vector UserManager::getAllUsers()
{
  std::vector<std::string> allUsers = db->allUserNames();
  
  std::vector<User> users;
  for(int i = 0; i < allUsers.size(); ++i)
  {
    users.push_back(db->fetchUser(allUsers[i]));
  }
  return users;
}
