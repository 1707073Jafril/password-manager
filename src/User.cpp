#include "User.h"
#include <pqxx/pqxx> 

User::User(Database &database) : db(database), currentUserId(-1) {} // Initialize currentUserId

bool User::registerUser(const std::string &username, const std::string &password) {
    pqxx::work txn(db.getConnection());
    try {
        txn.exec0("INSERT INTO users (username, password) VALUES (" + txn.quote(username) + ", " + txn.quote(password) + ")");
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error during registration: " << e.what() << std::endl;
        return false;
    }
}

bool User::loginUser(const std::string &username, const std::string &password) {
    pqxx::work txn(db.getConnection());
    pqxx::result res = txn.exec("SELECT id FROM users WHERE username = " + txn.quote(username) + " AND password = " + txn.quote(password));
    
    if (res.size() == 1) {
        currentUser = username;
        currentUserId = res[0][0].as<int>(); // Set the currentUserId
        return true;
    }
    return false;
}

void User::logoutUser() {
    currentUser.clear();
    currentUserId = -1; // Reset the currentUserId
}

int User::getCurrentUserId() const {
    return currentUserId; // Return the current user's ID
}
