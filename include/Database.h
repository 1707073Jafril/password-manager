#ifndef DATABASE_H
#define DATABASE_H

#include<pqxx/pqxx> // PostgreSQL C++ library
#include<string>
#include<bits/stdc++.h>

using namespace std;


class Database {
public:
    Database(const string &connStr);
    ~Database();

    pqxx::connection &getConnection();

private:
    pqxx::connection *conn;
};

#endif
