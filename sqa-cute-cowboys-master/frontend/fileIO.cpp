#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "fileIO.h"
#include "user.h"
#include "item.h"


//removes given chars from a string
void removeCharsFromString( std::string &str, char* charsToRemove ) {
    for (int i = 0; i < strlen(charsToRemove); ++i ) {
        int end = str.find_last_not_of(charsToRemove[i]);
        str = str.substr(0, end + 1);

        for(int j = str.find_first_not_of(charsToRemove[i]); j < str.length(); j++){
            if(str[j] == charsToRemove[i]){
                str[j] = ' ';
            }
        }
    }
}


/*
Description: a Simple constructor for the file IO class
*/
FileIO::FileIO() {}


/*
Description: Given a list of transactions, logout writes these transactions
to the daily transactions file
Input: transactions: list of transactions made this session
Output: true or false based on if the file read was successful
*/
bool FileIO::logout(std::vector<std::string> transactions) {
    std::ofstream outfile;
    outfile.open("daily_transaction_file.of.txt");//, std::ios_base::app);
    if (outfile.fail()) {
        std::cerr << "Error! Cannot open the user accounts file: daily_transaction_file.of.txt " << std::endl;
        return false;
    }
    //outfile << "test" << std::endl;
    /*
        write all transactions to file
    */

    if(outfile.is_open()){
        for(int i = 0; i < transactions.size(); i++){
            //outfile << transactions[i] << std::endl;
            outfile << transactions[i] << "\r" << std::endl;
        }
    }


    outfile.close();
    return true;
}

/*
Description: this function reads in the user accounts from the userAccountsFile, parses
the strings read in, and stores them in the given list
Input: userAccountsFile: name of the account file. users: reference to a list of users
Output: true or false based on if the file read was successful
*/
bool FileIO::parseUsers(std::string userAccountsFile, std::vector<User> &users) {
    std::ifstream usersFileReader;
    usersFileReader.open(userAccountsFile);
    if (usersFileReader.fail()) {
        std::cerr << "Error! Cannot open the user accounts file: \"" << userAccountsFile << "\"" << std::endl;
        return false;
    }
    /*
        read in and parse all users
    */
    std::string line;

    while(std::getline(usersFileReader, line)){

        char remove[] = " ";
        std::string name = line.substr(0,15);
        removeCharsFromString(name, remove);
        if(name.compare("END") == 0){
            break;
        }

        std::string type = line.substr(16,2);
        float amount = std::stof(line.substr(19));
        User newUser = User(name, type, amount);
        users.push_back(newUser);
    }

    usersFileReader.close();
    return true;
}

/*
Description: Reads in a list of items stored in the items file, parses them, and stores 
them in the given list
Input: itemsFile: name of the item file. items: reference to a list of items
Output: true or false based on if the file read was successful
*/
bool FileIO::parseItems(std::string itemsFile, std::vector<Item> &items) {
    std::ifstream itemsFileReader;
    itemsFileReader.open(itemsFile);
    if (itemsFileReader.fail()) {
        std::cerr << "Error! Cannot open the items file: \"" << itemsFile << "\"" << std::endl;
        return false;
    }
    /*
        read in and parse all items
    */

    std::string line;

    while(std::getline(itemsFileReader, line)){

        char remove[] = " ";
        std::string itemName = line.substr(0,25);
        removeCharsFromString(itemName, remove);
        if(itemName.compare("END") == 0){
            break;
        }
        
        std::string seller = line.substr(26,15);
        removeCharsFromString(seller, remove);
        std::string buyer = line.substr(42, 15);
        removeCharsFromString(buyer, remove);
        int days = std::stoi(line.substr(58, 3));
        float currentValue = std::stof(line.substr(62));
        Item newItem = Item(itemName, seller, buyer, days, currentValue);

        items.push_back(newItem);
    }

    itemsFileReader.close();
    return true;
}

/*
Description: goes through the userAccounts file given until it finds a blank line.
Then the function writes the user given(in the proper format) to that blank line
Input: userAccountsFile: name of the user file. user: the user that needs to be added to the file
Output: true or false based on if the file read was successful
*/
bool FileIO::addUser(std::string userAccountsFile, User user){
    std::ifstream usersFileReader;
    usersFileReader.open(userAccountsFile);
    if (usersFileReader.fail()) {
        std::cerr << "Error! Cannot open the user accounts file: \"" << userAccountsFile << "\"" << std::endl;
        return false;
    }

    /*
        add user to first blank space
    */

    usersFileReader.close();
    return true;
}

/*
Description: Funciton goes through the file given and looks for a user that matches oldUser. If it finds
that user, it then replaces that user with the updated user given
Input: userAccountsFile: name of the item file. oldUser: the user that needs to be updated
       updatedUser: the user that 'oldUser' will be updated to 
Output: true or false based on if the file read was successful, OR it will return false if 'oldUser'
is not currently within the file
*/
bool FileIO::updateUser(std::string userAccountsFile, User oldUser, User updatedUser){
    std::ifstream usersFileReader;
    usersFileReader.open(userAccountsFile);
    if (usersFileReader.fail()) {
        std::cerr << "Error! Cannot open the user accounts file: \"" << userAccountsFile << "\"" << std::endl;
        return false;
    }
    /*
        update the oldUser in file with the updated user given
    */
    usersFileReader.close();
    return true;
}

/*
Description: Goes through the file given, looking for the user that was passed. If it is found
then it is deleted
Input: userAccountsFile: name of the item file. user: the user to be deleted
Output: true or false based on if the file read was successful, OR if the user is not found within the
given file, the function will also return false
*/
bool FileIO::deleteUser(std::string userAccountsFile, User user){
    std::ifstream usersFileReader;
    usersFileReader.open(userAccountsFile);
    if (usersFileReader.fail()) {
        std::cerr << "Error! Cannot open the user accounts file: \"" << userAccountsFile << "\"" << std::endl;
        return false;
    }
    /*
        delete the user that matches the user description
    */
    usersFileReader.close();
    return true;
}

/*
Description: goes through the item file given until a blank line is encountered. Upon finding
one the program then writes the item passed to that line
Input: itemsFile: name of the item file. item: the item to be added 
Output: true or false based on if the file read was successful
*/
bool FileIO::addItem(std::string itemsFile, Item item) {
    std::ifstream itemsFileReader;
    itemsFileReader.open(itemsFile);
    if (itemsFileReader.fail()) {
        std::cerr << "Error! Cannot open the items file: \"" << itemsFile << "\"" << std::endl;
        return false;
    }
    /*
        add user to first blank space
    */
    itemsFileReader.close();
    return true;
}

/*
Description: This funciton goes through the item file looking for the line storing the 'oldItem' passed
to it. When found, the line is updated to match the updated Item passed 
Input: itemsFile: name of the item file. oldItem: the item that is going to be replaced
       updatedItem: item that is going to update 'oldItem'
Output: true or false based on if the file read was successful, OR if 'oldItem' is not found
then the funciton will return false
*/
bool FileIO::updateItem(std::string itemsFile, Item oldItem, Item updatedItem) {
    std::ifstream itemsFileReader;
    itemsFileReader.open(itemsFile);
    if (itemsFileReader.fail()) {
        std::cerr << "Error! Cannot open the items file: \"" << itemsFile << "\"" << std::endl;
        return false;
    }
    /*
        update old item in file with new updated version
    */
    itemsFileReader.close();
    return true;
}

/*
Description: Function goes through the item file passed, looking for the item description that matches
the item passed. If found, that file is then deleted 
Input: itemsFile: name of the item file. item: the item to be deleted
Output: true or false based on if the file read was successful, OR if the item is not found then
the function will also return false
*/
bool FileIO::deleteItem(std::string itemsFile, Item item) {
    std::ifstream itemsFileReader;
    itemsFileReader.open(itemsFile);
    if (itemsFileReader.fail()) {
        std::cerr << "Error! Cannot open the items file: \"" << itemsFile << "\"" << std::endl;
        return false;
    }
    /*
        finds the item that matches the item given and deletes it in the file
    */
    itemsFileReader.close();
    return true;
}
