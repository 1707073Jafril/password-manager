# Password Manager: A Simple C++ Password Manager Using OOP, Database, CRUD Operations, and Hashing

## Features  
- Authentication  
      - Login  
      - Register  
      - Logout  
- Security  
      - Hashing  
- Database Operation  
      - Create & Store Password  
      - Update Password  
      - Show List of Password  
      - Delete Password  

## Technologies 
- Langugae : C++
- Database : PostgreSQL

## Project File Structure
```text
├── include
│   ├── Database.h
│   ├── PasswordManager.h
│   ├── User.h
│   └── Utils.h
├── PasswordManager
├── README.md
└── src
    ├── Database.cpp
    ├── main.cpp
    ├── PasswordManager.cpp
    ├── User.cpp
    └── Utils.cpp

2 directories, 11 files
```
## Run the Password Manager in Local Machine  
1. Download or clone source code from the repo.
   ```text
         https://github.com/1707073Jafril/password-manager
   ```
2. Unzip the project and go to the directory of the project  
3. Set the database, create database user.
4. Create tables using following commands.
   ```sql
    CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
```
```sql
    CREATE TABLE IF NOT EXISTS passwords (
    id SERIAL PRIMARY KEY,
    user_id INTEGER REFERENCES users(id) ON DELETE CASCADE,
    service VARCHAR(100) NOT NULL,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
```
   
6. Run the following commands
