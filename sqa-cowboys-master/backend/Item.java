package backend;
/**
 * Item class.
 * Gets and sets information related to an item.
 * Displays a string of all the item information
 * 
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 16th, 2020
 * @version 1.0.0
 * @name Item.java
 */


public class Item {

    /**
     * Constructor for the Item class
     * Depending on which transaction is passed (determined by the transcode)
     * allocate the items information appropriately.
     * If it came from the Add New Item transaction, then extract different substrings to data
     * Same for transaciton code Bid
     * If the code was neither then assume it came from available items file.
     * @param itemDetails
     */
    public Item(String itemDetails) {
        // If the Trans code and the length of each record matches then distribute data appropriately 
        // Check for Trans code AND length because an item in the avail items file can start with "03" or "02"
        if(itemDetails.substring(0, 2).equals(Constants.ADD_NEW_ITEM) && itemDetails.length() == Constants.NEW_ITEM_ENTRY_LENGTH) {
            this.name = itemDetails.substring(3, 28);
            this.seller = itemDetails.substring(29, 44);
            this.bidder = new String(new char[15]).replace('\0', ' ' ); // Fill 15 empty spaces for blank bidder
            this.days = itemDetails.substring(45, 48);
            this.price = itemDetails.substring(49, 55);
        }  else if(itemDetails.substring(0, 2).equals(Constants.BID) && itemDetails.length() == Constants.BID_ITEM_ENTRY_LENGTH) {
            this.name = itemDetails.substring(3, 28);
            this.seller = itemDetails.substring(29, 44);
            this.bidder = itemDetails.substring(45, 60);
            this.days = new String(new char[3]).replace('\0', ' ' ); // Fill 15 empty spaces for blank bidder
            this.price = itemDetails.substring(61, 67);
        }
        else {
            this.name = itemDetails.substring(0, 25);
            this.seller = itemDetails.substring(26, 41);
            this.bidder = itemDetails.substring(42, 57);
            this.days = itemDetails.substring(58, 61);
            this.price = itemDetails.substring(62, 68);
        }
    }

    /* Attributes */
    private String name;

    private String seller;

    private String bidder;

    private String days;

    private String price;

    /* Methods */

    /* Setters*/

    /**
     * Sets the name for the item
     * @param the item's name
     * @return void
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Sets the seller's name for the item
     * @param the sellers's name
     * @return void
     */
    public void setSeller(String seller) {
        this.seller = seller;
    }

    /**
     * Sets the bidder's name for the item
     * @param the bidders's name
     * @return void
     */
    public void setBidder(String bidder) {
        this.bidder = bidder;
    }

    /**
     * Sets the remaining days to auction for the item
     * @param the item's days
     * @return void
     */
    public void setDays(String days) {
        this.days = days;
    }

    /**
     * Sets the price for the item
     * @param the item's price
     * @return void
     */
    public void setPrice(String price) {
        this.price = price;
    }

    /* Getters */

    /**
     * Get the item's name
     * @return the item's name
     */
    public String getName() {
        return this.name;
    }

    /**
     * Get the item's seller's name
     * @return the item's seller's name
     */
    public String getSeller() {
        return this.seller;
    }

    /**
     * Get the item's bidder's name
     * @return the item's bidder's name
     */
    public String getBidder() {
        return this.bidder;
    }

    /**
     * Get the item's remaining auction days
     * @return the item's remaining auction days
     */
    public String getDays() {
        return this.days;
    }

    /**
     * Get the item's price
     * @return the item's price
     */
    public String getPrice() {
        return this.price;
    }

    /**
     * Checks if the item's auction has come to an end via end date
     * @return false if days are negative
     * @return true if days are positive (zero inclusive)
     */
    public boolean isEndAuctionDate() {
        int days = Integer.parseInt(this.days);
        if((days - 1) < 0) {
            return false;
        }
        return true;
    }

    /**
     * Decrements the days remaining of an item.
     * Formats the new days with leading zeros
     * @return void
     */
    public void updateDaysRemaining() {
        int days = Integer.parseInt(this.days);
        --days;

        this.days = String.format("%03d", days);
    }


    /**
     * Concatenates item information seperated by spaces to be displayed
     * @return A string of the item details to be placed in the available items file
     */
    public String toString() {
        return this.getName() + " " + this.getSeller() + " " + this.getBidder() + " " + this.getDays() + " " + this.getPrice();
    }
}