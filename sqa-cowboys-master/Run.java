/**
 * Run class.
 * Instantiates a Backend object to be manipulated.
 * Parses through the various files and extracts data from them
 * to be saved into the Backend's object.
 * Backend object manipulates the data as it needs
 * then write back out to the files with new data.
 * 
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 29th, 2020
 * @version 1.0.3
 * @name Run.java
 */
import backend.Backend;
import backend.Constants;
import io.FileParser;
import java.util.*;
import backend.Item;

class Run {

    /**
     * Main Function. This will loop through the transactions vector
     * and call the appropriate method based on what kind of transaction it is.
     * 01 calls addNewUser. 
     * 02 calls deleteUser and deleteItem.
     * 06 calls updateUser.
     * 05 calls refundUser.
     * 03 calls addNewItem.
     * 04 calls updateItem.
     * @param args Unused.
     * @return Nothing.
     */
    public static void main(String[] args) {
        Backend backend = new Backend();
        String transCode = "";
        Vector<String> users = new Vector<String>();
        Vector<String> transactions = new Vector<String>();
        Vector<String> items = new Vector<String>();

        // Set the vectors in the backend object
        backend.setUsers(FileParser.getFileInfo(Constants.CURRENT_USER_ACCOUNTS_FILE));
        backend.setTransactions(FileParser.getFileInfo(Constants.DAILY_TRANSACTION_FILE));
        backend.setItems(FileParser.getFileInfo(Constants.AVAILABLE_ITEMS_FILE));

        transactions = backend.getTransactions();

        for(int i = 0; i < transactions.size(); i++) {
            transCode = transactions.get(i).substring(0, 2);    // get the trans code
            switch(transCode) {
                case Constants.ADD_NEW_USER:
                    backend.addNewUser(transactions.get(i));
                    break;
                case Constants.DELETE:
                    backend.deleteItem(transactions.get(i).substring(3, 18));
                    backend.deleteUser(transactions.get(i));
                    break;
                case Constants.ADD_NEW_ITEM: 
                    backend.addNewItem(transactions.get(i));
                    break;
                case Constants.BID: 
                    backend.updateItem(transactions.get(i));
                    break;
                case Constants.REFUND: 
                    backend.refundUser(transactions.get(i));
                    break;
                case Constants.ADD_CREDIT:
                    backend.updateUser(transactions.get(i));
                    break;
                case Constants.END_OF_SESSION: 
                    break;
                default:
                    break;
            }
        }

        
        items = backend.getItems();
        users = backend.getUsers();

        // Decrement the items days 
        for(int i = 0; i < items.size(); i++) {
            Item item = new Item(items.get(i));
            // Check if the auction date has come to an end or not
            if(item.isEndAuctionDate()) {
                item.updateDaysRemaining(); // Update the remaining days left for the item
                items.set(i, item.toString());    // Set the current positon to the updated item
            } else {
                // If the auction date HAS come to an end
                // Remove the current item
                backend.endBid(item);
                items.remove(i);
                --i;
            }
        }

        // Set the files to the new data
        FileParser.writeFile(Constants.AVAILABLE_ITEMS_FILE, items);
        FileParser.writeFile(Constants.CURRENT_USER_ACCOUNTS_FILE, users);
    }
}