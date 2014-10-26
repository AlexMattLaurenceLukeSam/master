#include "UserManager.hpp"

void UserManager::fetchUser(std::string userName)
{
  *currentUser = database->fetchUser(userName);
}

std::vector UserManager::getAllUsers()
{
  std::vector<std::string> allUsers = database->allUserNames();
  
  std::vector<User> users;
  for(int i = 0; i < allUsers.size(); ++i)
  {
    users.push_back(database->fetchUser(allUsers[i]));
  }
  return users;
}

void UserManager::sendUser()
{
 //send *currentUser to the client
}

void UserManager::sendUserBatch()
{
  //std::vector<std::string> userID = db->
}
