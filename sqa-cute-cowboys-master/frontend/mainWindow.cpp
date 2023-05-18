/*
Description: A class that holds methods to process each type of user transaction
Input: None, or the current users file name and available items file name both as strings
*/

#include <iostream>
#include <sstream>      // std::ostringstream
#include <math.h>
#include "item.h"
#include "user.h"
#include "mainWindow.h"

/*
Description: An empty constructor for the MainWindow Class
Input: None
Output: MainWindow class
*/
MainWindow::MainWindow() {
    isLoggedIn = false;
}
/*
Description: A simple function that trims the spaces
off a string
Input: string
output string without spaces surrounding it
*/
std::string trim(const std::string& str){
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first){
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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
//01-create, 02-delete, 06-addcredit, 00-end of session
void MainWindow::addTransaction(std::string transactionType, User user){

    if(transactionType == "00" || transactionType == "01" || transactionType == "02" || transactionType == "06"){
    
        std::string transaction = transactionType + " " + user.toString();

        //std::cout << transaction << "\n"; 
        transactions.push_back(transaction);
    }
    
}

//05-refund
void MainWindow::addTransaction(User buyer, User seller, float credit){
    std::string transaction = "05 ";

    transaction += buyer.getUserName();
    for(int i = 0; i < 16 - buyer.getUserName().length(); i++){
        transaction += " ";
    }

    transaction += seller.getUserName();
    for(int i = 0; i < 16 - seller.getUserName().length(); i++){
        transaction += " ";
    }

    std::string str = std::to_string(credit);
	int dot = str.find_last_of(".");
	dot += 3;
	str = str.substr(0, dot);
	int len = str.length();

	if(len < 9){
		for(int x = 0; x < 9 - len; x++){
			transaction += "0";
		}
	}
	transaction += str;

    transactions.push_back(transaction);
}

//03-advertize
void MainWindow::addTransaction(User seller, Item item){
    std::string transaction = "03 ";

    transaction += seller.getUserName();
    for(int i = 0; i < 16 - seller.getUserName().length(); i++){
        transaction += " ";
    }

    transaction += item.getName();
    for(int i = 0; i < 26 - item.getName().length(); i++){
        transaction += " ";
    }

    //NOTE as advertise is not done yet im not sure if this is the correct value to save to file
    //feel free to change "item.getHighestBid()" if it should be something else
    std::string str = std::to_string(item.getHighestBid());
	int dot = str.find_last_of(".");
	dot += 3;
	str = str.substr(0, dot);
	int len = str.length();

	if(len < 6){
		for(int x = 0; x < 6 - len; x++){
			transaction += "0";
		}
	}
	transaction += str;

    transactions.push_back(transaction);
}

//04-bid
void MainWindow::addTransaction(User buyer, User seller, Item item){
    std::string transaction = "04 ";

    transaction += item.getName();
    for(int i = 0; i < 26 - item.getName().length(); i++){
        transaction += " ";
    }
    
    transaction += seller.getUserName();
    for(int i = 0; i < 16 - seller.getUserName().length(); i++){
        transaction += " ";
    }

    transaction += buyer.getUserName();
    for(int i = 0; i < 16 - buyer.getUserName().length(); i++){
        transaction += " ";
    }

    std::string str = std::to_string(item.getHighestBid());
	int dot = str.find_last_of(".");
	dot += 3;
	str = str.substr(0, dot);
	int len = str.length();

	if(len < 6){
		for(int x = 0; x < 6 - len; x++){
			transaction += "0";
		}
	}
	transaction += str;

    transactions.push_back(transaction);
}


/*
Description: A constructor for the MainWindow Class that takes in the users file name and items file name,
    then calls the processInputFiles function to process them
Input: Two string representations of file names, userAccountsFile and itemsFile
Output: MainWindow class
*/
MainWindow::MainWindow(std::string userAccountsFile, std::string itemsFile) {
    isLoggedIn = false;
    filesProcessed = processInputFiles(userAccountsFile, itemsFile);
}

/*
Description: A function that takes a string input and checks to see 
    if it is a valid transaciton or not based on the current status of
    the program. If valid, it then calls the correct function to be run
    based on the string passed
input: transaction - the transaction to be processed
*/
void MainWindow::processTransaction(std::string transaction) {
    if (transaction == "login") {
        if (!isLoggedIn) {
            login();
        } else {
            std::cout << "You are already logged in. \n";
        }
    } else if(isLoggedIn) {
        if (transaction == "logout") {
            logout();
        } else if (transaction == "create") {
            createUser();
        } else if (transaction == "delete") {
            deleteUser();
        } else if (transaction == "advertise") {
            advertise();
        } else if (transaction == "bid") {
            bid();
        } else if (transaction == "refund") {
            refund();
        } else if (transaction == "addcredit") {
            addCredit();
        } else {
            std::cout << "Sorry! \"" << transaction << "\" is not a valid transaction" << std::endl;
        }
    } else {
        std::cout << "You must be logged in to enter commands \n";
    }
}

/*
Description: Uses the FileIO member variable stored in this class to process the users file and items file.
    Then the data is stored in a users list and an items list, both of which are member variables,
    so they can be used in other transactions.
Input: Two string representations of file names, userAccountsFile and itemsFile
Output: Returns true if both files were successfully processed, false otherwise
*/
bool MainWindow::processInputFiles(std::string userAccountsFile, std::string itemsFile) {
    bool usersProcessed = fileIO.parseUsers(userAccountsFile, users);
    bool itemsProcessed = fileIO.parseItems(itemsFile, items);
    // std::cout << users.size() << "\n";
    // std::cout << "Last User: |" << users[users.size() - 1].getUserName() << "|\n";
    // std::cout << items.size() << "\n";
    // std::cout << "Last Item: |" << items[items.size() - 1].getName() << "|\n";
    if (usersProcessed && itemsProcessed) {
        return true;
    } else {
        return false;
    }
}

/*
Description: The function that is called when the user enters the login transaction.
    It askes the user to enter a username.
    A successful login only occurs if the user is not logged in, and has entered a username
    that exists in the users list.
Input: None
Output: Returns true if the login was successful, false otherwise
*/
bool MainWindow::login() {
    std::string username;
    std::string password;
    std::cout << "Username: \n";
    getline(std::cin, username);
    std::cout << "Password: \n";
    getline(std::cin, password);
    for(int x = 0; x < users.size(); x++){
        if(username.compare(users[x].getUserName()) == 0){
            currentUser = users[x];
            isLoggedIn = true;
            std::cout << "Welcome " << username << "\n";
            return true;
        }
    }
    std::cout << "Not a valid username, please enter a registered username.\n";
    return false;
}

/*
Description: The function that is called when the user enters the logout transaction.
    A successful logout only occurs if the user is logged in.
    It also uses the FileIO class to write to the daily transaction file.
Input: None
Output: Returns true if the logout was successful, false otherwise
*/
bool MainWindow::logout() {
    addTransaction("00", currentUser);

    fileIO.logout(transactions);
    isLoggedIn = false;
    programEnded = true;
    std::cout << "Logout Successful!\n";
    return true;
}

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
bool MainWindow::createUser() {
    if(currentUser.getUserType() == "AA"){
        std::string name;
        std::string type;
        std::string moneyString;
        float money;

        std::cout << "Enter account name: \n";
        //std::cin >> name;
        getline(std::cin, name);
        name = trim(name);
        if(name.length() > 15){
            std::cout << "UserName is longer than 15 characters. Please pick a shorter UserName.\n";
            return false;
        }
        
        if(name.compare("") == 0){
            std::cout << "Error! Account name cannot be empty\n";
            return false;
        }
        for(int i = 0; i < users.size(); i++){
            if(name.compare(users[i].getUserName()) == 0){
                std::cout << "Username already exists. Choose another UserName. \n";
                return false;
            }
        }

        std::cout << "Select Account Type: \nAA (admin)\nFS (Full-Standard)\nBS (Buy-Standard)\nSS (Sell-Standard)\n";
        //std::cin >> type;
        getline(std::cin, type);
        if(type != "AA" && type != "FS" && type != "BS" && type != "SS"){
            std::cout << "Account type not on list, please choose one of the given types.\n";
            return false;
        }

        std::cout << "Enter amount of credit to add: \n";
        //std::cin >> money;
        try{
            getline(std::cin, moneyString);
            money = stof(moneyString);
            if(money > 999999.00){
                std::cout << "Max amount of credit to give users is $999,999.00. Give less credit.\n";
                return false;
            }
        }catch(const std::invalid_argument msg){
            std::cout << "please enter a numeric value\n";
            return false;
        };

        User newUser = User(name, type, money);
        users.push_back(newUser);

        std::cout << "New account created! Welcome " << users.back().getUserName() << "\n";

        addTransaction("01", newUser);

    }else{
        std::cout << "Must be an admin to create an account.\n";
        return false;
    }
    return true;
}

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
bool MainWindow::deleteUser() {
    if (currentUser.getUserType() != "AA") {
        std::cout << "Only Admins can delete users" << std::endl;
        return false;
    }

    std::string username;
    std::cout << "Enter user to delete: " << std::endl;
    getline(std::cin, username);

    if (username == "") {
        std::cout << "Error! You must enter a Username to delete" << std::endl;
        return false;
    }
    if (username == currentUser.getUserName()) {
        std::cout << "Error! You cannot delete yourself" << std::endl;
        return false;
    }

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUserName() == username) {
            std::cout << "user successfully deleted!" << std::endl;
            addTransaction("02", users[i]);
            users.erase(users.begin() + i);

            // Insert the transaction into the transactions list.
            //transactions.push_back("02 " + currentUser.toString());

            return true;
        }
    }
    std::cout << "Error! No user named " << username << " exists." << std::endl;
    return false;
}

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
bool MainWindow::advertise() {
	double minAdvertise;
    int auctionDays;

	if (currentUser.getUserType() == "BS") {
		std::cout << "Sorry! Buy-standard accounts are not allowed to advertise items." << std::endl;
		return false;
	}

	std::string itemInput;
	std::cout << "Enter item name:" << std::endl;
    getline(std::cin, itemInput);
	if (itemInput == "") {
		std::cout << "Error! In order to advertise, you must enter an item name:" << std::endl;
		return false;
	}
	
	if (itemInput.length() > 25) {
		std::cout << "That item name is too long! Please enter a name that is at most 25 characters long." << std::endl;
		return false;
	}

	std::string advertiseString;
	std::cout << "Enter minimum bid amount ($):" << std::endl;
	getline(std::cin, advertiseString);
	minAdvertise = std::stof(advertiseString);

	if (minAdvertise > 999.99) {
		std::cout << "Error! An item can be priced for at most $999.99. Please enter a different bid amount ($):" << std::endl;
		return false;
	}

	if (minAdvertise < 0.00) {
		std::cout << "Error! An item cannot be priced less than $0.00. Please enter a different bid amount ($):" << std::endl;
		return false;
	}

    std::string daysString;
    std::cout << "Enter how long to auction the item for (days):" << std::endl;
    getline(std::cin, daysString);
    auctionDays = std::stof(daysString);

    if(auctionDays < 0) {
        std::cout << "Error! The number of days must be positive. Please enter a different number of days to auction the item for:" << std::endl;
        return false;
    }

    if(auctionDays > 100) {
        std::cout << "Error! An item can be auctioned for at most 100 days. Please enter a different number of days to auction the item for:" << std::endl;
        return false;
    }

    // Add the new item to the current list of items
    Item newItem(itemInput, currentUser.getUserName(), "", auctionDays, minAdvertise);
    items.push_back(newItem);

    // Format the transaction for the daily transaction file
    std::string transaction = "03 " + newItem.getName();
    for (int i = newItem.getName().size(); i < 25; ++i) {
        transaction += " ";
    }
    transaction += " " + currentUser.getUserName();
    for (int i = currentUser.getUserName().size(); i < 15; ++i) {
        transaction += " ";
    }
    transaction += " ";
    for (int i = daysString.size(); i < 3; ++i) {
        transaction += "0";
    }
    transaction += daysString + " ";
    for (int i = advertiseString.size(); i < 6; ++i) {
        transaction += "0";
    }
    transaction += advertiseString;
    transactions.push_back(transaction);

    std::cout << "Item name: " << itemInput << std::endl;
    std::cout << "Seller name: " << currentUser.getUserName() << std::endl;
    std::cout << "Minimum bid: $" << minAdvertise << std::endl;
    std::cout << "Auction length: " << auctionDays << " days" << std::endl;
    std::cout << "Saved!" << std::endl;

    return false;
}

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
bool MainWindow::bid() {
    std::string bidValueInput;
    float bidValue;
    Item currentItem;
    User searchedUser;
    bool searchedUserExists = false;

    if(currentUser.getUserType() == "SS") {
        std::cout << "Sorry! Sell-Standard accounts are not allowed to bid on items." << std::endl;
        return false;
    }

    
    std::string bidItemInput;
    std::cout << "Please enter the item you'd like to bid on: " << std::endl;
    getline(std::cin, bidItemInput);

    bool itemExists = false;
    for (int i = 0; i < items.size(); ++i) {
        if (items[i].getName() == bidItemInput) {
            currentItem = items[i];
            itemExists = true;
            break;
        }
    }
    if (!itemExists) {
        std::cout << "Sorry, no one is selling items named \"" << bidItemInput << "\". Please try a different item name. " << std::endl;
        return false;
    }

    std::string itemSellerInput;
    std::cout << "Please enter the seller's username: " << std::endl;
    getline(std::cin, itemSellerInput);

 
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUserName() == itemSellerInput) {
            searchedUser = users[i];
            searchedUserExists = true;
            break;
        }
    }
    if(!searchedUserExists) {
            std::cout<< "No user named \""<<itemSellerInput<< "\" found! Please enter an existing seller's username: " << std::endl;
            return false;
        }
   
   
     if (currentItem.getName() == bidItemInput && currentItem.getSeller() != itemSellerInput) {
            std::cout << "Seller \"" << itemSellerInput <<"\" is not selling any item named \"" << bidItemInput << "\". Please enter a seller who is selling the item you want: " << std::endl;

            return false;
        }

    std::string cents = "";
        if (currentItem.getHighestBid()-(int)currentItem.getHighestBid() == 0) {
            cents = ".00";
        }
    
    std::cout << "Item name: \"" << bidItemInput << "\"    Seller name: \"" << itemSellerInput << "\"    Current highest bid: " << currentItem.getHighestBid() << cents <<std::endl;
    std::cout << "Please enter your bid amount: " << std::endl;
    getline(std::cin, bidValueInput);
    bidValue = stof(bidValueInput);
    
    if (currentUser.getUserType() == "AA" && bidValue <= currentItem.getHighestBid()) {
        std::cout << "Bid rejected! The new bid value must be higher than the previous bid. Please enter a larger bid amount: " << std::endl;
       return false;
   }
    else if (currentUser.getUserType() == "AA" && bidValue > currentItem.getHighestBid()) {
        std::cout << "Success! You have successfully bid on the item \"" <<bidItemInput<< "\"" <<std::endl;
        std::cout << "Item name: \"" << currentItem.getName() << "\"    Seller name: \"" << itemSellerInput<< "\"    Current highest bid: " << bidValue  << std::endl;
        currentItem.setHighestBid(bidValue);
        currentItem.setCurrentWinningBidder(currentUser.getUserName());
        addTransaction(currentUser, searchedUser, currentItem);
        return true;
   }

    if (bidValue < (currentItem.getHighestBid()*1.05) || bidValue > currentUser.getAvailableCredit()) {
        std::cout << "Bid rejected! The new bid value is too low. It must be higher than the previous bid by at least 5%. Please enter a larger bid amount: " << std::endl;
        std::cout << "Bid rejected! The new bid value must be numeric. Please enter a valid bid amount: " << std::endl;
        std::cout << "Bid rejected! You have less than $15.00 in your account. Please enter a valid bid amount: " << std::endl;

        return false;

    }
  
    else {
        std::cout << "Success! You have successfully bid on the item \"" <<bidItemInput<< "\"" <<std::endl;
        std::cout << "Item name: \"" << currentItem.getName() << "\"    Seller name: \"" << itemSellerInput<< "\"    Current highest bid: " << bidValue << cents <<std::endl;
        currentItem.setHighestBid(bidValue);
        currentItem.setCurrentWinningBidder(currentUser.getUserName());
        addTransaction(currentUser, searchedUser, currentItem);
        return true;
    }

    return false;
}

/*
Description: The function that is called when the user enters the refund transaction.
    It asks for the buyer's username, the seller's username, and the amount of credit to transfer.
    It then displays the item's current highest bid and asks for a new bid amount.
    If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
    It will also transfer the specified amount of credit from the seller's account to the buyer's account.
    The transaction will fail if the current user is not an admin.
Input: None
Output: Returns true if the user given is successfully refunded, false otherwise
*/
bool MainWindow::refund() {
    if (currentUser.getUserType() != "AA") {
        std::cout << "Transaction rejected! Only admins can perform the \"refund\" transaction." << std::endl;
        return false;
    }

    User buyer;
    bool buyerExists = false;
    std::cout << "Enter buyer's username: " << std::endl;
    std::string username;
    getline(std::cin, username);
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUserName() == username) {
            buyer = users[i];
            buyerExists = true;
        }
    }
    if (!buyerExists) {
        std::cout << "\"" << username << "\" is not a current user. The account does not exist or is not in use." << std::endl;
        return false;
    }

    User seller;
    bool sellerExists = false;
    std::cout << "Enter seller's username: " << std::endl;
    getline(std::cin, username);
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUserName() == username) {
            seller = users[i];
            sellerExists = true;
        }
    }
    if (!sellerExists) {
        std::cout << "\"" << username << "\" is not a current user. The account does not exist or is not in use." << std::endl;
        return false;
    }

    std::string amountString;
    std::cout << "Enter the amount of credit to transfer: " << std::endl;
    getline(std::cin, amountString);
    float amount = stof(amountString);

    buyer.setAvailableCredit(buyer.getAvailableCredit() + amount);
    seller.setAvailableCredit(seller.getAvailableCredit() - amount);
    std::string cents = "";
    if (amount-(int)amount == 0) {
        cents = ".00";
    }
    std::cout << "Successfully refunded " << buyer.getUserName() 
              << ". $" << amount << cents << " has be transfered from " 
              << seller.getUserName() << "'s account to " << buyer.getUserName() << "'s account" << std::endl;
    
    // Add to the daily transaction list
    addTransaction(buyer, seller, amount);
    /*std::ostringstream stringStream;
    stringStream << "05 " << buyer.getUserName() << " " << seller.getUserName() << " " << amount << cents;
    std::string transaction = stringStream.str();
    transactions.push_back(transaction);*/

    return true;
}

/*
Description: The function that is called when the user enters the addcredit transaction.
    If the current user is an admin, it asks for the username of the account to add to, and the amount of credit to add.
    If the current user is not an admin, it only asks for the amount of credit to add, which will be added to the current user's account.
    If successful, this transaction is appended to the list of transactions to save in the daily transaction file.
    It will also add the given amount of credit to the given user.
Input: None
Output: Returns true if the amount of credit given is successfully added to the given user's account, false otherwise
*/
bool MainWindow::addCredit() {
    User userToAddTo;
    bool userExists = false;
    if (currentUser.getUserType() == "AA") {
        std::string username;
        std::cout << "Enter the user to add to: " << std::endl;
        getline(std::cin, username);
        for (int i = 0; i < users.size(); ++i) {
            if (users[i].getUserName() == username) {
                userToAddTo = users[i];
                userExists = true;
                break;
            }
        }
        if (!userExists) {
            std::cout << "User does not exist. Try someone else." << std::endl;
            return false;
        }
    }
    else {
        userToAddTo = currentUser;
        userExists = true;
    }

    float amount;
    std::cout << "Enter the amount to add: " << std::endl;
    std::string amountString;
    getline(std::cin, amountString);
    amount = stof(amountString);

    if (0 <= amount && amount <= 1000) {
        // Add the credit to the user
        userToAddTo.setAvailableCredit(userToAddTo.getAvailableCredit() + amount);
        addTransaction("06", userToAddTo);
        // Insert the transaction into the transactions list.
        //transactions.push_back("06 " + currentUser.toString());

        std::string cents = "";
        if (amount-(int)amount == 0) {
            cents = ".00";
        }
        std::cout << "$" << amount << cents << " has been given to " << userToAddTo.getUserName() << std::endl;
        
        return true;
    }
    else {
        std::cout << "You cannot add more than $1000 in credit. Lower the amount." << std::endl;
    }
    
    return false;
}
