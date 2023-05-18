package backend;
/**
 * Backend class.
 * Reads a daily transaction file and parses data to modify information 
 * about current users and available items. 
 * Then writes that information to the current users file and available items file.
 * 
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 16th, 2020
 * @version 1.0.2
 * @name Backend.java
 */

import java.util.Vector;

public class Backend {

    /* Attributes */
    private Vector<String> users;
    private Vector<String> transactions;
    private Vector<String> items;

    /* Methods */

    /* Setters */

    /**
     * Sets user vector
     * @param users
     */
    public void setUsers(Vector<String> users) {
        this.users = users;
    }

    /**
     * Sets transactions vector
     * @param transactions
     */
    public void setTransactions(Vector<String> transactions) {
        this.transactions = transactions;
    }

    /**
     * Sets items vector
     * @param items
     */
    public void setItems(Vector<String> items) {
        this.items = items;
    }
    
    /* Getters */

    /**
     * Gets the users vector
     * @return a vector with all current user information
     */
    public Vector<String> getUsers() {
        return users;
    }

    /**
     * Gets the transactions vector
     * @return a vector with all current transaction information
     */
    public Vector<String> getTransactions() {
        return transactions;
    }

    /**
     * Gets the items vector 
     * @return a vector with all current item information
     */
    public Vector<String> getItems() {
        return items;
    }

    /**
     * Add a new user. This method will add a string to the users vector
     * to represent adding a new user.
     * @param userDetails The transaction code that indicates creating a user.
     * @return Nothing.
     */
    public void addNewUser(String userDetails) {
        User user = new User(userDetails);

        for(int i = 0; i < users.size(); i++) {
            String username = users.get(i).substring(0, 15);
            if (username.equals(user.getUsername())) {
                System.out.println("User " + user.getUsername() + " already exists");
                return;
            }
        }
        users.add(user.toString());
    }

    /**
     * Update a user. This method modifies a string in the users vector
     * to represent changing the amount of credit the user has.
     * @param userDetails The transaction code that indicates adding credit to a user.
     * @return Nothing.
     */
    public void updateUser(String userDetails) {
        User user = new User(userDetails);
        
        for(int i = 0; i < users.size(); i++) {
            String username = users.get(i).substring(0, 15);
            if (username.equals(user.getUsername())) {
                users.set(i, user.toString());
                break;
            }
        }
    }

    /**
     * Refunds a user. This method updates the users vector by 
     * subtracting money from the specified seller's account 
     * and adding it to the specified buyer's account, thus refunding the buyer.
     * If the new money value exceeds the maximum or goes lower than 0,
     * the value will just be set to the maximum or 0 respectively.
     * @param transaction The transaction code that indicates refunding a user.
     * @return Nothing.
     */
    public void refundUser(String transaction) {
        String buyerName = transaction.substring(3, 18);
        String sellerName = transaction.substring(19, 34);
        String refundCredit = transaction.substring(35, 44);
        double refundValue = Double.valueOf(refundCredit);

        String userToRefund = "";
        String userToDeductFrom = "";
        int buyerIndex = -1;
        int sellerIndex = -1;
        for (int i = 0; i < users.size(); i++) {
            String user = users.get(i).substring(0, 15);
            if (buyerName.equals(user)) {
                userToRefund = users.get(i);
                buyerIndex = i;
            }
            if (sellerName.equals(user)) {
                userToDeductFrom = users.get(i);
                sellerIndex = i;
            }
        }

        if (!userToRefund.isEmpty() && !userToDeductFrom.isEmpty()) {
            double buyerCredit = Double.valueOf(userToRefund.substring(19, 27));
            double sellerCredit = Double.valueOf(userToDeductFrom.substring(19, 27));
            buyerCredit += refundValue;
            sellerCredit -= refundValue;
            if(buyerCredit > Constants.MAX_BALANCE) {
                buyerCredit = Constants.MAX_BALANCE;
            }
            if (sellerCredit < 0) {
                sellerCredit = 0;
            }
            userToRefund = userToRefund.substring(0, 19) + String.format("%09.2f", buyerCredit);
            userToDeductFrom = userToDeductFrom.substring(0, 19) + String.format("%09.2f", sellerCredit);
            users.set(buyerIndex, userToRefund);
            users.set(sellerIndex, userToDeductFrom);
        }
    }

    /**
     * Delete a user. This method removes an entry in the users vector
     * to represent that user being deleted. The user that is deleted matches the given userName.
     * @param userName The username of the user to delete.
     * @return Nothing.
     */
    public void deleteUser(String userName) {
        User user = new User(userName);

        for(int i = 0; i < users.size(); i++) {
            String username = users.get(i).substring(0, 15);
            if (username.equals(user.getUsername())) {
                System.out.println("Deleted user: " + user.getUsername());
                users.remove(i);
                break;
            }
        }
    }

    /**
     * Adds a new item. This method will add a string to the items vector
     * to represent adding a new item.
     * @param itemDetails The transaction code that indicates advertising an item.
     * @return Nothing.
     */
    public void addNewItem(String itemDetails) {
        Item item = new Item(itemDetails);
        Vector<String> items = this.getItems(); // Get a vector of all the current items

        items.add(item.toString());  // Add new item to the list

        this.setItems(items);   // Set the instantiated object to this newly added vector
    }

    /**
     * Updates an item. This method modifies a string in the items vector
     * to represent changing the item's current highest bidder, current highest bid, 
     * and the number of days it has left.
     * @param itemDetails The transaction code that indicates bidding on an item.
     * @return Nothing.
     */
    public void updateItem(String itemDetails) {
        Item item = new Item(itemDetails);

        Vector<String> items = this.getItems();

        for(int i = 0; i < items.size(); i++) {
            Item listItem = new Item(items.get(i));
            // If the names are the same
            if(item.getName().equals(listItem.getName())) {
                // If the sellers are also the same
                // Checking for name incase two people sell an item with same name
                if(item.getSeller().equals(listItem.getSeller()))
                {
                    Item newItem = new Item(items.get(i));
                    // If the value of the passed items price is higher than that of the item in the file
                    // Check for this incase two people bid the same price in the same session
                    // First person will have the bid saved
                    if(Float.valueOf(item.getPrice()).floatValue() > Float.valueOf(newItem.getPrice()).floatValue()) {
                        newItem.setPrice(item.getPrice());
                        newItem.setBidder(item.getBidder());
                        items.set(i, newItem.toString());
                    } 
                }
            }
        }
        this.setItems(items);
    }

    /**
     * Deletes an item. This method removes an entry in the items vector
     * to represent that item being deleted. The item that is deleted matches the given itemName.
     * @param username The username of the user to delete their items.
     * @return Nothing.
     */
    public void deleteItem(String username) {
        Vector<String> items = this.getItems();

        for(int i = 0; i < items.size(); i++) {
            Item item = new Item(items.get(i));
            // If the names are the same
            if(username.equals(item.getSeller())) {
                items.remove(i);
            }
        }

        this.setItems(items);
    }


    /**
     * When the ending of a bid occurs
     * Add the bid's value to the sellers account and subtract from bidders account
     * @param item
     * @return void
     */
    public void endBid(Item item) {
        // If there is no bidder attatched to an ending item
        // Return immediately and don't calculate any prices
        if(item.getBidder().trim().isEmpty()) {
            return;
        }

        
        double itemBid = Double.valueOf(item.getPrice());
        double balance = 0.0;
        Vector<String> users = this.getUsers();
        String usersName = "";

        // Loop through all current users
        // Check if the user is the same as the one in the bid 
        // if they are the same create a new user object to manipulate
        for(int i = 0; i < users.size(); i++) {
            usersName = users.get(i).substring(0, 15);
            if(usersName.equals(item.getSeller())) {
                User seller = new User(users.get(i));
                balance = Double.valueOf(seller.getBalance());
                
                balance += itemBid;
                // If the new balance is over the max balance just cut off the remainder
                if(balance > Constants.MAX_BALANCE) {
                    balance = Constants.MAX_BALANCE;
                }
                seller.setBalance(String.format("%09.2f", balance));    // Formats for 000000.00
                users.set(i, seller.toString());
            }
            if(usersName.equals(item.getBidder())) {
                User buyer = new User(users.get(i));
                balance = Double.valueOf(buyer.getBalance());

                balance -= itemBid;
                buyer.setBalance(String.format("%09.2f", balance));
                users.set(i, buyer.toString());
            }
        }

        // Set the users vector back to the new data
        this.setUsers(users);
    }
}