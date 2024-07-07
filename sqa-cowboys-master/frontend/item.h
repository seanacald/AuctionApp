#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

/*
Description: Creates an item class that contains all the information that the file reader parses
when reading the Available Items File 
Input: Parsed information from the file reader that reads Available Items 
*/
class Item {
private:
    std::string itemName; // The item name 
    std::string sellerName; // The seller name 
    std::string currentWinningBidder; // The current winning bidder
    int numberOfDaysLeft; // The number of days left before bidding closes
    float highestBid; // The hightest bid
public:

    Item();
    /*
    Description: Takes the input attributes and outs them in an Item class 
    Input: itemName, sellerName, currentWinningBidder, numberOfDaysLeft, highestBid
    Output: Item Class 
    */
    Item(std::string itemName, // The item name 
         std::string sellerName, // The seller name 
         std::string currentWinningBidder, // The current winning bidder 
         int numberOfDaysLeft, // The number of days left on the item 
         float highestBid); // The highest bid amount
    /*
    Description: Executes the Item deconstructor to free memory after they program terminates
    Input: Item Class 
    Output: Print verification that deconstruction is complete
    */ 
    ~Item(){
        //std::cout << "deconstructor called for item " << itemName << "\n";
    };
    /*
    Description: Gets the name of the item that is on bid. Allows us to print the information on
    the daily transaciton file. 
    Input: Item Class 
    Output: itemName
    */
    std::string getName();
    /*
    Description: gets the seller name of the item that is on bid. Allows us to print the information
    on the daily transaction file. 
    Input: Item Class 
    Output: sellerName 
    */
    std::string getSeller();
    /*
    Description: Gets the name of the current hightst bidder that is attatched to the item. Allows us 
    to print to the daily transaction file
    Input: Item Class 
    Output: currentWinningBidder
    */
    std::string getCurrentBidder();
    /*
    Description: Gets the number of days left on the item's bid life. This allows us to print the 
    information on the daily transaction file. 
    Input: Item Class 
    Output: numberOfDaysLeft
    */
    int getDaysLeft();
    /*
    Description: Gets the highest bid value. 
    Input: Item Class 
    Output: highestBid
    */
    float getHighestBid();
    /*
    Description: Convets any attribute to a stringo it can be appended to the daily transaction
    file 
    Input: Item Class Attribute
    Output: String version of the attribute
    */
    std::string toString();

    float setHighestBid(float newHighestBid);

    std::string setCurrentWinningBidder(std::string newWinningBidder);
};

#endif 
