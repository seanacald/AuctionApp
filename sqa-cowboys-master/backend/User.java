package backend;
/**
 * User class.
 * Gets and sets information related to a user.
 * Displays a string of all the users information
 * 
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 26th, 2020
 * @version 1.0.0
 * @name User.java
 */

 public class User {
    
    /**
     * Constructor for User class
     * Checks the userDetails for 3 things
     *      1. If the userDetails is the same length as the Current User List
     *      2. If the userDetails is the same length as Adding or Updating a user transaction
     *      3. If the userDetails is the same length as the Max length a username can be
     * These tests are to see which part of the string we should access to get the desired data
     * Sets the objects variables to the appropriate data.
     */
    public User(String userDetails) {
        if(userDetails.length() == Constants.CURRENT_USER_LENGTH) {
            this.username = userDetails.substring(0, 15);
            this.accountType = userDetails.substring(16, 18);
            this.balance = userDetails.substring(19, 28);
        }
        else if(userDetails.length() == Constants.ADD_UPDATE_USER_LENGTH) {
            this.username = userDetails.substring(3, 18);
            this.accountType = userDetails.substring(19, 21);
            this.balance = userDetails.substring(22, 31);
        } else if(userDetails.length() == Constants.USERNAME_MAX_LENGTH) {
            this.username = userDetails;
            this.accountType = null;
            this.balance = null;
        }
    }

    /* Attributes */
    private String username;

    private String accountType;

    private String balance;

    /* Methods */

    /**
     * Sets the user's username
     * @param username : string of the username
     * @return void
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Sets the user's account type
     * @param accountType : string of the account type
     * @return void
     */
    public void setAccountType(String accountType) {
        this.accountType = accountType;
    }

    /**
     * Sets the user's balence
     * @param balance : string of the balance
     * @return void
     */
    public void setBalance(String balance) {
        this.balance = balance;
    }

    /**
     * Gets the user's username
     * @return a string containing the username
     */
    public String getUsername() {
        return this.username;
    }

    /**
     * Gets the user's account type
     * @return a string containing the account type
     */
    public String getAccountType() {
        return this.accountType;
    }

    /**
     * Gets the user's balance
     * @return a string containing the balance
     */
    public String getBalance() {
        return this.balance;
    }

    /**
     * Overwrites the toString for a User.
     * Displays the users information concatenated, seperated by a space
     * @return a string contatinating the user's information
     */
    public String toString() {
        return this.username + " " + this.accountType + " " + this.balance;
    }
 }

