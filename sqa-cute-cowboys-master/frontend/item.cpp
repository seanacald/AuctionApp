#include "item.h"
#include <string>

/*
    this should check for the correct input to make sure
    any of the input types are not too long
*/

Item::Item() {
  
}

Item::Item(std::string itemName, // Item name 
           std::string sellerName, // Seller name 
           std::string currentWinningBidder, // Current highest bidder name 
           int numberOfDaysLeft, // number of days left on the item 
           float highestBid){ // highest bid value 
    this->itemName = itemName; // item name 
    this->sellerName = sellerName; // seller name 
    this->currentWinningBidder = currentWinningBidder; // highest bidder name 
    this->numberOfDaysLeft = numberOfDaysLeft; // numer of days left on the bid 
    this->highestBid = highestBid; // highest bid value 
}
/*
Description: Gets the name of the item from the Item class 
Input: Item Class 
Output: itemName 
*/
std::string Item::getName() {
    return(itemName);
}
/*
Description: Gets the name of the seller that is assiciated with the item 
Input: Item Class
Output: sellerName 
*/
std::string Item::getSeller() {
    return(sellerName);
}
/*
Description: Gets the name of the current winning bidder 
Input: Item Class 
Output: currentWinningBidder 
*/
std::string Item::getCurrentBidder() {
    return(currentWinningBidder);
}
/*
Description: Gets the number of days left on the bid 
Input: Item Class 
Output: numberOfDaysLeft 
*/
int Item::getDaysLeft() {
    return(numberOfDaysLeft);
}
/*
Description: Gets the highest bid value on the item 
Input: Item Class 
Output: highestBid
*/
float Item::getHighestBid() {
    return(highestBid);
}
/*
Description: Primts the values needed to show the user what thye are doing in the system 
Input: Item Class 
Output: Any output that this function is used with. 
*/
std::string Item::toString(){
    return("output string");
}

float Item::setHighestBid(float newHighestBid) {
  this->highestBid = newHighestBid;
}

std::string Item::setCurrentWinningBidder(std::string newWinningBidder) {
  this->currentWinningBidder = newWinningBidder;
}
