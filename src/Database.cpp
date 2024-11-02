#include "Database.h"

Database::Database(const std::string &connStr) {
    conn = new pqxx::connection(connStr);
}

Database::~Database() {
    conn->disconnect();
    delete conn;
}

pqxx::connection &Database::getConnection() {
    return *conn;
}
