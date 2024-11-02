#ifndef USER_H
#define USER_H

#include <string>
#include "Database.h"

class User {
public:
    User(Database &db);
    bool registerUser(const std::string &username, const std::string &password);
    bool loginUser(const std::string &username, const std::string &password);
    void logoutUser();
    int getCurrentUserId() const; 

private:
    Database &db;
    std::string currentUser;
    int currentUserId;
};

#endif
