#include "PasswordManager.h"
#include <pqxx/pqxx>
#include <iostream>

PasswordManager::PasswordManager(Database &database) : db(database) {}

void PasswordManager::addPassword(int userId, const std::string &service, const std::string &username, const std::string &password) {
    pqxx::work txn(db.getConnection());
    txn.exec0("INSERT INTO passwords (user_id, service, username, password) VALUES (" +
              txn.quote(userId) + ", " + txn.quote(service) + ", " + txn.quote(username) + ", " + txn.quote(password) + ")");
    txn.commit();
}

void PasswordManager::updatePassword(int userId, int id, const std::string &service, const std::string &username, const std::string &password) {
    pqxx::work txn(db.getConnection());
    txn.exec0("UPDATE passwords SET service = " + txn.quote(service) + ", username = " + txn.quote(username) +
              ", password = " + txn.quote(password) + " WHERE id = " + txn.quote(id) + " AND user_id = " + txn.quote(userId));
    txn.commit();
}

void PasswordManager::deletePassword(int userId, int id) {
    pqxx::work txn(db.getConnection());
    txn.exec0("DELETE FROM passwords WHERE id = " + txn.quote(id) + " AND user_id = " + txn.quote(userId));
    txn.commit();
}

std::vector<std::tuple<int, std::string, std::string, std::string>> PasswordManager::getAllPasswords(int userId) {
    pqxx::work txn(db.getConnection());
    pqxx::result res = txn.exec("SELECT id, service, username, password FROM passwords WHERE user_id = " + txn.quote(userId));
    std::vector<std::tuple<int, std::string, std::string, std::string>> passwords;

    for (const auto &row : res) {
        passwords.emplace_back(row[0].as<int>(), row[1].c_str(), row[2].c_str(), row[3].c_str());
    }
    return passwords;
}
