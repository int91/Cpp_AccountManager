#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include "Account.h"

void mainMenu();
void createAccount();
void deleteAccount();
void findAccount();
void saveAccount(Account account);
void loadAccounts();
void saveAccounts();
void listAllAccounts();
void loadAccount(std::string fileName);

std::vector <std::string> accountPaths;
std::string accDetails[5];
std::string typed;

int itemProcess = 0;

int main()
{
    loadAccounts();
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    std::cout << "What would you like to do?\n";
    std::cout << "[1] Create Account\n";
    std::cout << "[2] Delete Account (Does not work)\n";
    std::cout << "[3] Find Account\n";
    std::cout << "[4] Exit\n";
    std::cout << "-> ";
    std::cin >> choice;
    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            //deleteAccount();
            mainMenu();
            break;
        case 3:
            findAccount();
            break;
        case 4:
            exit(0);
            break;
        default:
            mainMenu();
            break;
    }
}

void createAccount() {
    std::cout << "Account Name: " << accDetails[0] << "\n";
    std::cout << "Account Password: " << accDetails[1] << "\n";
    std::cout << "Account Email: " << accDetails[2] << "\n";
    std::cout << "Account Application: " << accDetails[3] << "\n";
    std::cout << "Account Description: " << accDetails[4] << "\n\n\n";

    switch (itemProcess) {
        case 0:
            std::cout << "Enter the account name: ";
            std::cin >> typed;
            if (typed != "/back") {
                accDetails[0] = typed;
                itemProcess++;
            } else {
                mainMenu();
            }
            break;
        case 1:
            std::cout << "Enter the account password: ";
            std::cin >> typed;
            if (typed != "/back") {
                accDetails[1] = typed;
                itemProcess++;
            } else {
                itemProcess--;
            }
            break;
        case 2:
            std::cout << "Enter the account email: ";
            std::cin >> typed;
            if (typed != "/back") {
                accDetails[2] = typed;
                itemProcess++;
            } else {
                itemProcess--;
            }
            break;
        case 3:
            std::cout << "Enter the application: ";
            std::cin >> typed;
            if (typed != "/back") {
                accDetails[3] = typed;
                itemProcess++;
            } else {
                itemProcess--;
            }
            break;
        case 4:
            std::cout << "Enter the description: ";
            std::getline(std::cin >> std::ws, typed);
            if (typed != "/back") {
                accDetails[4] = typed;
                itemProcess++;
            } else {
                itemProcess--;
            }
            break;
    }

    if (itemProcess == 5) {
        Account acc(accDetails[0], accDetails[1], accDetails[2], accDetails[3], accDetails[4]);
        std::cout << acc.getName() << "\n";
        std::cout << acc.getPassword() << "\n";
        std::cout << acc.getEmail() << "\n";
        std::cout << acc.getApplication() << "\n";
        std::cout << acc.getDescription() << "\n";
        saveAccount(acc);
        itemProcess = 0;
    }
    else {
        createAccount();
    }
}

void deleteAccount () {
    int arrayIndex;
    listAllAccounts();
    std::cin >> arrayIndex;
    if (accountPaths.size() >= arrayIndex) {
        accountPaths.erase(accountPaths.begin() + arrayIndex);
        for (int i = 0; i < accountPaths.size(); i++) {
            std::cout << accountPaths[i];
        }
    }
}

void removeIndex(std::string &array, int arrayIndex) {
    if (array.size() >= arrayIndex) {
        array.erase(array.begin() + arrayIndex);
    }
}

void findAccount() {
    int choice;
    std::cout << "Select an account:" << "\n";
    listAllAccounts();
    std::cout << "Type 401940 to go back" << "\n" << "-> ";
    std::cin >> choice;
    if (choice == 401940) {
        mainMenu();
    }
    loadAccount(accountPaths[choice]);
    std::cout << "Name: " << accDetails[0] << "\n";
    std::cout << "Password: " << accDetails[1] << "\n";
    std::cout << "Email: " << accDetails[2] << "\n";
    std::cout << "Application: " << accDetails[3] << "\n";
    std::cout << "Description: " << accDetails[4] << "\n";
    std::cout << "Press 1 to continue" << "\n";
    std::cin >> choice;
    mainMenu();
}

void listAllAccounts() {
    loadAccounts();
    for (int i = 0; i < accountPaths.size(); i++) {
        std::cout << "[" << i << "]" << " " << accountPaths[i] << "\n";
    }
}

void saveAccount(Account account) {
    std::ofstream accFile;
    std::string fileName = "Accounts/" + account.getName() + "_" + account.getApplication() + ".account";
    bool hasFound = false;
    int index = 0;
    accFile.open(fileName);
    accFile << account.getName() + "\n";
    accFile << account.getPassword() + "\n";
    accFile << account.getEmail() + "\n";
    accFile << account.getApplication() + "\n";
    accFile << account.getDescription();
    accFile.close();
    if (accountPaths.size() == 0) {
        accountPaths.push_back(fileName);
    }
    else {
        for (int i = 0; i < accountPaths.size(); i++) {
            if (accountPaths[i] == fileName) {
                hasFound = true;
                index = i;
                break;
            }
        }
        if (!hasFound) {
            accountPaths.push_back(fileName);
        }
    }
    saveAccounts();
}

void saveAccounts() {
    std::ofstream accFile;
    std::string fileName = "Accounts/accounts.bak";
    accFile.open(fileName);
    for (int i = 0; i < accountPaths.size(); i++) {
        accFile << accountPaths[i] + "\n";
    }
    accFile.close();
}

void loadAccounts() {
    std::string line;
    std::ifstream accFile;
    accFile.open("Accounts/accounts.bak");
    if (accFile.is_open())
    {
        accountPaths.clear();
        while (std::getline(accFile, line))
        {
            accountPaths.push_back(line);
            //std::cout << line << "\n";
        }
        accFile.close();
    }
    else {
        //std::cout << "Unable to find / open file";
        accFile.close();
    }
}

void loadAccount(std::string fileName) {
    std::string line;
    std::ifstream accFile;
    int i = 0;
    accFile.open(fileName);
    if (accFile.is_open()) 
    {
        while (std::getline(accFile, line) && i < 5) 
        {
            accDetails[i] = line;
            //std::cout << returnData[i] << "\n";
            //std::cout << line << '\n';
            i++;
        }
    }
    else {
        std::cout << "Unable to find / open file";
        accFile.close();
    }
}