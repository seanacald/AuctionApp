#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

/*
Description: Creates a User class that stores all the information from the User file that the
file reader parses.
Input: Parsed information gets sent to the User class and stored here
*/
class User {
private:
	std::string userName; // User Username
	std::string userType; // User User Type (admin, seller, buyer, full standard)
	float availableCredit; // User available credit

public:
	/*
	Description: An empty constructor for the User Class, required to compile the program
	Input: None
	Output: User class
	*/
	User();

	/*
	Description: Takes the input attributes and puts them into the User Class
	Input: UserName, UserType, Available Credit
	Output: User class
	*/
	User(std::string userName, // User username
		std::string userType, // User user typr
		float availableCredit); // User available credit

	/*
	Description: Executes the User Deconstructor to free up memeory after the program terminates
	Input: User Class
	Output: Print verifictaion that deconstruction is complete
	*/
	~User() {
		//std::cout << "deconstructor called for user: " << userName << "\n";
	};

	/*
	Description: Gets the username from the User class. Allows us to use the username in other areas of the system
	Input: User Class
	Output: username
	*/
	std::string getUserName();

	/*
	Description: Gets the user type from the User class. This allows us to make the necessary checks later on when needed.
	Input: User Class
	Output: User Type
	*/
	std::string getUserType();

	/*
	Description: Gets the available credit from the User class.
	Input: User Class
	Output: available credit
	*/
	float getAvailableCredit();

	void setAvailableCredit(float credit);

	/*
	Description: A function that prints any information from the User Class and display it to the user.
	Input: User Class attributes
	Ouput: The attribute that this function is used for.
	*/
	std::string toString();
};

#endif
