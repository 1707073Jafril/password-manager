#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "Database.h"
#include "User.h"
#include "PasswordManager.h"
#include "Utils.h"

// Function prototypes
void showMainMenu();
void showPasswordMenu(PasswordManager &pm, int userId);

int main() {
    // Initialize the database connection
    Database db("dbname=mydb user=user_name password=user_password hostaddr=127.0.0.1 port=5432");  // Modify database configuration based on database settings and host config

    User user(db);
    PasswordManager pm(db);

    while (true) {
        showMainMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Register a new user
            std::string username, password;
            std::cout << "Register a new user:\n";
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            // Attempt to register the user
            if (user.registerUser(username, password)) {
                std::cout << "Registration successful! Redirecting to login...\n";
            } else {
                std::cout << "Registration failed! Username may already be taken." << std::endl;
                continue;
            }

        } else if (choice == 2) {
            // Log in an existing user
            std::string username, password;
            std::cout << "Log in:\n";
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            // Attempt to log in the user
            if (user.loginUser(username, password)) {
                std::cout << "Login successful! Redirecting to password management...\n";
                int userId = user.getCurrentUserId(); // Get the current user's ID
                showPasswordMenu(pm, userId);  // Pass userId to showPasswordMenu
            } else {
                std::cout << "Login failed! Incorrect username or password." << std::endl;
            }

        } else if (choice == 3) {
            // Exit the program
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}

void showMainMenu() {
    std::cout << "\nMain Menu:\n";
    std::cout << "1. Register\n";
    std::cout << "2. Log in\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}

void showPasswordMenu(PasswordManager &pm, int userId) {
    while (true) {
        std::cout << "\nPassword Management Menu:\n";
        std::cout << "1. List all passwords\n";
        std::cout << "2. Add a new password\n";
        std::cout << "3. Update a password\n";
        std::cout << "4. Delete a password\n";
        std::cout << "5. Log out\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // List all passwords for the logged-in user
            auto passwords = pm.getAllPasswords(userId);
            std::cout << "\nStored Passwords:\n";
            for (const auto &password : passwords) {
                std::cout << "ID: " << std::get<0>(password) << ", Service: " << std::get<1>(password)
                          << ", Username: " << std::get<2>(password) << ", Password: " << std::get<3>(password) << std::endl;
            }
        } else if (choice == 2) {
            // Add a new password
            std::string service, username, password;
            std::cout << "Service: ";
            std::cin >> service;
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;
            pm.addPassword(userId, service, username, password);
            std::cout << "Password added successfully!" << std::endl;
        } else if (choice == 3) {
            // Update an existing password
            int id;
            std::string service, username, password;
            std::cout << "Enter ID of password to update: ";
            std::cin >> id;
            std::cout << "New Service: ";
            std::cin >> service;
            std::cout << "New Username: ";
            std::cin >> username;
            std::cout << "New Password: ";
            std::cin >> password;
            pm.updatePassword(userId, id, service, username, password);
            std::cout << "Password updated successfully!" << std::endl;
        } else if (choice == 4) {
            // Delete a password
            int id;
            std::cout << "Enter ID of password to delete: ";
            std::cin >> id;
            pm.deletePassword(userId, id);
            std::cout << "Password deleted successfully!" << std::endl;
        } else if (choice == 5) {
            // Log out
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice, please try again.\n";
        }
    }
}
