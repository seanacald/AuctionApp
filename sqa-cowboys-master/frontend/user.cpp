/*
Description: Creates a User class that stores all the information from the User file that the
file reader parses.
Input: Parsed information gets sent to the User class and stored here
*/

#include "user.h"
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>

int countDigit(int num){
	int count = 0; 
    while (num != 0) { 
        num = num / 10; 
        ++count; 
    } 
    return count; 
}

/*
Description: An empty constructor for the User Class, required to compile the program
Input: None
Output: User class
*/
User::User() {

}
/*
Description: Refernces the User class from user.h and assigns the attributes to varibles.
*/
User::User(std::string userName, // User username
			std::string userType, // User user type
			float availableCredit) { // User available credit
	this->userName = userName; // User username
	this->userType = userType; // User user type
	this->availableCredit = availableCredit; // User available credit
}
/*
Description: Gets the username attribure from the User class and returns the username so it can
be appended to the daily transaction file.
Input: User Class
Output: Username
*/
std::string User::getUserName() {
	return(userName);
}
/*
Description: Gets the User Type attribute from the User class and returns the user type so it can
be appended to the daily transaction file.
Input: User Class
Output: userType
*/
std::string User::getUserType() {
	return(userType);
}
/*
Description: Gets the Available Credit attribute form the User class and returns the available
credit to be appended to the daily transcaction file.
Input: User Class
Output: Available Credit
*/
float User::getAvailableCredit() {
	return(availableCredit);
}

void User::setAvailableCredit(float credit) {
	this->availableCredit = credit;
}

/*
Description: Prints the values needed to show the user what they are doing in the system
Input: User Class
Output: Any output that this function is used with.
*/
std::string User::toString() {
	std::ostringstream stream;
	int digits = 8 - countDigit(floor(availableCredit));

	stream << std::fixed << std::setprecision(digits);

	stream << userName;
    for(int i = 0; i < 16 - userName.length(); i++){
        stream << " ";
    }
    stream << userType + " ";

    //stream << availableCredit;
    std::string str = std::to_string(availableCredit);
	int dot = str.find_last_of(".");
	dot += 3;
	str = str.substr(0, dot);
	int len = str.length();

	if(len < 9){
		for(int x = 0; x < 9 - len; x++){
			stream << "0";
		}
	}
	stream << str;

	return stream.str();
}
