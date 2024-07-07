/*
Purpose: This program is an auction-style sales service run from the command line.
    It allows users to put up items for auction, and bid on the items that are up.
    Admins of the system can create new users, as well as delete them.
    They can also add credit to accounts they choose, and refund any purchases.
    Non-admins can also add credit, but only to their own account.
    The program also keeps track of the transactions performed in a session by saving it in a daily transaction file.
Input files: Current user accunts file (current_user_accounts.if.txt) and available items file (available_items.if.txt).
    These store data for the list of users in the system, and the list of currently available items for auction.
Output files: Daily transaction file (daily_transaction_file.of.txt).
    This saves information about the transactions the users have performed during the session.
How to run: To compile, use g++ on all of the cpp files in the program at the same time.
    To run, run the executable file from the command line while passing in both
    the current user accunts file and the available items file as command line arguments.
    Compiling example: g++ fileIO.cpp item.cpp main.cpp mainWindow.cpp user.cpp
    Running example: ./a.out current_user_accounts.if.txt available_items.if.txt
*/

#include <iostream>
#include "mainWindow.h"

int main(int argc, char *argv[]) {
    // Make sure the user has passed in the current user accunts file and available items file as command line arguments
    if (argc != 3) {
        std::cerr << "Error! Number of arguments should be 3, but " << argc << "  was given" << std::endl;
        std::cerr << "Please run like this: <executable> <user accounts file> <items file>" << std::endl;
        return -1;
    }

    std::string userAccountsFile = argv[1];
    std::string itemsFile = argv[2];

    MainWindow mainWindow(userAccountsFile, itemsFile);

    // Make sure the input files are successfully processed
    if (!mainWindow.filesProcessed) {
        return -2;
    }

    // Have the user enter the login transaction
    std::string transaction;
    //std::cout << "Please enter \"login\" to start: ";
    //std::cin >> transaction;

    //while (!mainWindow.programEnded) {
    while (true) {
        if (!mainWindow.getIsLoggedIn()) {
            std::cout << "Please enter \"login\" to start: " << std::endl;
        }
        //std::cin >> transaction;
        getline(std::cin, transaction);
        if (transaction == "quit") {
            break;
        }
        mainWindow.processTransaction(transaction);
    }

    return 0;
}
