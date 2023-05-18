#include <iostream>
#include <string.h>
#include <vector>
#include "user.h"
#include "item.h"

/*
Description: This class's purpose is to handle all of the different file io
functions for the program, as well as returning true or false in order to indicate
if the given file read/write was successful
*/

class FileIO {
public:
    /*
    Description: simple constructor class
    */
    FileIO();

    /*
    Description: before a user logs out of the program, this function is called so that we can
    store all of the transactions that the user made during this session
    Input: transaction: the list of trasactions made by the user this session
    Output: true or false based on if the file read was successful
    */
    bool logout(std::vector<std::string> transactions);

    /*
    Description: reads in the users from a given file and stores them in the given list, this allows 
    us to have user storage that we can load into a c++ list whenever we want
    Input: userAccountsFile: name of the account file. users: reference to a list of users
    Output: true or false based on if the file read was successful
    */
    bool parseUsers(std::string userAccountsFile, std::vector<User> &users);

    /*
    Description: read in all stored items from a given file, then parses them and stores them to list given.
    Using this makes it so we can save all of the different items currently being sold between program sessions 
    Input: userAccountsFile: name of the account file. users: reference to a list of users
    Output: true or false based on if the file read was successful
    */
    bool parseItems(std::string itemsFile, std::vector<Item> &items);

    /*
    Description: This function is called whenever a new user is created, so that the user file
    gets updated with the newly created user
    Input: userAccountsFile: name of the users file. user: user to be added to file
    Output: true or false based on if the write to file was successful
    */
    bool addUser(std::string userAccountsFile, User user);

    /*
    Description: This function is called when a user needs to be updated with new informaiton,
    so that the file is up to date with all the users
    Input: userAccountsFile: name of the users file. oldUser: user to be updated
           updatedUser: updated version of 'oldUser'
    Output: true or false based on if the write to file was successful
    */
    bool updateUser(std::string userAccountsFile, User oldUser, User updatedUser);

    /*
    Description: This function is called when a user is deleted, so that they are also deleted on
    file as well
    Input: userAccountsFile: name of the users file. user: user to be deleted
    Output: true or false based on if the write to file was successful
    */
    bool deleteUser(std::string userAccountsFile, User user);

    /*
    Description: This function is called whenever a new item is created, so that the new addition
    is saved to file
    Input: itemsFile: name of the item file. item: item to be added to file
    Output: true or false based on if the write to file was successful
    */
    bool addItem(std::string itemsFile, Item item);

    /*
    Description: This will be called whenever a item is updated so that the file 
    description will match the updates
    Input: itemsFile: name of the item file. oldItem: item to be updated
           updatedItem: the item to replace 'oldItem'
    Output: true or false based on if the write to file was successful
    */
    bool updateItem(std::string itemsFile, Item oldItem, Item updatedItem);

    /*
    Description: This will be called whenever a item is to be deleted, so that the file will
    match the programs view of items
    Input: itemsFile: name of the item file. item: the item to be deleted
    Output: true or false based on if the write to file was successful
    */
    bool deleteItem(std::string itemsFile, Item item);
};
