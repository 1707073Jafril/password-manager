#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <vector>
#include <tuple>
#include "Database.h"

class PasswordManager {
public:
    PasswordManager(Database &db);

    // Associate the password entry with a specific user
    void addPassword(int userId, const std::string &service, const std::string &username, const std::string &password);

    // Update the password entry for a specific user
    void updatePassword(int userId, int id, const std::string &service, const std::string &username, const std::string &password);

    // Delete the password entry for a specific user
    void deletePassword(int userId, int id);

    // Retrieve all passwords for the specified user
    std::vector<std::tuple<int, std::string, std::string, std::string>> getAllPasswords(int userId);

private:
    Database &db;
};

#endif
