#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include "fileIO.h"

/*
Description: A class that holds methods to process each type of user transaction
Input: None, or the current users file name and available items file name both as strings
*/
class MainWindow {
private:
    FileIO fileIO; // An instance of the FileIO class to process files
    bool isLoggedIn; // Tells if the user is logged in
    std::vector<User> users; // A list of current users read in from the current users file
    std::vector<Item> items; // A list of available items read in from the available items file
    User currentUser; // An instance of the User class to store the current user
    std::vector<std::string> transactions; // A list of transactions performed during the session, to be written to the daily transaction file
public:
    bool filesProcessed; // Tells if the current users file and available items file have been processed successfully
    bool programEnded = false;

    /*
    Description: An empty constructor for the MainWindow Class
    Input: None
    Output: MainWindow class
    */
    MainWindow();

    /*
    Description: A constructor for the MainWindow Class that takes in the users file name and items file name,
        then calls the processInputFiles function to process them
    Input: Two string representations of file names, userAccountsFile and itemsFile
    Output: MainWindow class
    */
    MainWindow(std::string userAccountsFile, std::string itemsFile);

    void processTransaction(std::string transaction);

    /*
    Description: the following four functiontions call "addTransaction" are
    all for adding transactions from the program to the "transactions" vector
    to be outputted to the daily transaction file later
    input #1: transacitonType - which transaction happened, User - The user
            affected by this transaction
    input #2: buyer - the user who is going to be refunded, seller - ther user
            the credit is being transferred from, credit - the amount of 
            credit to be transerred
    input #3: seller - the user putting the item up for auction, item - the item
            going p for auction
    input $4: buyer - the user bidding on the item, seller - the user who put the
            item up for auciton, item - the item being bid upon
    */

    //for logout, create, delete, and addCredit
    void addTransaction(std::string transactionType, User user);
    //for refund
    void addTransaction(User buyer, User seller, float credit);
    //for advertise
    void addTransaction(User seller, Item item);
    //for bid
    void addTransaction(User buyer, User seller, Item item);


    /*
    Description: The getter function for isLoggedIn.
    Input: None
    Output: Returns true if isLoggedIn == true, false otherwise
    */
    bool getIsLoggedIn() { return isLoggedIn; }

    /*
    Description: Uses the FileIO member variable stored in this class to process the users file and items file.
        Then the data is stored in a users list and an items list, both of which are member variables,
        so they can be used in other transactions.
    Input: Two string representations of file names, userAccountsFile and itemsFile
    Output: Returns true if both files were successfully processed, false otherwise
    */
    bool processInputFiles(std::string userAccountsFile, std::string itemsFile);

    /*
    Description: The function that is called when the user enters the login transaction.
        It askes the user to enter a username.
        A successful login only occurs if the user is not logged in, and has entered a username
        that exists in the users list.
    Input: None
    Output: Returns true if the login was successful, false otherwise
    */
    bool login();

    /*
    Description: The function that is called when the user enters the logout transaction.
        A successful logout only occurs if the user is logged in.
        It also uses the FileIO class to write to the daily transaction file.
    Input: None
    Output: Returns true if the logout was successful, false otherwise
    */
    bool logout();

    /*
    Description: The function that is called when the user enters the create transaction.
        It asks for the new user's username, the type of user (admin, full-standard, buy-standard, or sell-standard),
        and the user's initial credit.
        A successful create occurs if the user is logged in as an admin,
        and has successfully created a new user.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
        It rejects the creation if the current user is not an admin,
        or the new username matches an existing username,
        or the new username is longer than 15 characters,
        or the initial credit of the new user is higher than 999999.
    Input: None
    Output: Returns true if the new user was successfully created, false otherwise
    */
    bool createUser();

    /*
    Description: The function that is called when the user enters the delete transaction.
        It asks for the username of the user to delete.
        A successful create occurs if the user is logged in as an admin,
        and has successfully created an existing user.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
        The transaction is rejected if the given username is not in the system,
        or if it equals the current user's username.
    Input: None
    Output: Returns true if the new user was successfully deleted, false otherwise
    */
    bool deleteUser();

    /*
    Description: The function that is called when the user enters the advertise transaction.
        It asks for the item name, the minimum bid in dollars, and the number of days the auction lasts.
        The transaction is rejected if the current user has a buy-standard account,
        or the minimum bid given is higher than 999.99,
        or the given item name is longer than 25 characters,
        or the given length of the auction is longer than 100 days.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
    Input: None
    Output: Returns true if the correct new item is successfully entered into the available items, false otherwise
    */
    bool advertise();

    /*
    Description: The function that is called when the user enters the bid transaction.
        It asks for the item name to bid on, and the seller's username.
        It then displays the item's current highest bid and asks for a new bid amount.
        The transaction is rejected if the current user has a sell-standard account,
        or if the new bid amount exceeds 999.99,
        or if the item name given does not match any item in the system,
        or if the new bid amount is less than 5% higher than the current bid amount.
        If the user is an admin, the 5% constraint does not apply.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
        It will also update the information about the item being bid on.
    Input: None
    Output: Returns true if the user successfully bid on the item they specified, false otherwise
    */
    bool bid();

    /*
    Description: The function that is called when the user enters the refund transaction.
        It asks for the buyer's username, the seller's username, and the amount of credit to transfer.
        It then displays the item's current highest bid and asks for a new bid amount.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
        It will also transfer the specified amount of credit from the seller's account to the buyer's account.
    Input: None
    Output: Returns true if the user given is successfully refunded, false otherwise
    */
    bool refund();

    /*
    Description: The function that is called when the user enters the addcredit transaction.
        If the current user is an admin, it asks for the username of the account to add to, and the amount of credit to add.
        If the current user is not an admin, it only asks for the amount of credit to add, which will be added to the current user's account.
        If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
        It will also add the given amount of credit to the given user.
    Input: None
    Output: Returns true if the amount of credit given is successfully added to the given user's account, false otherwise
    */
    bool addCredit();
};

#endif
